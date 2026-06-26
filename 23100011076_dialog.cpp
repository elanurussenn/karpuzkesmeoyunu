//ELANUR USŞEN 23100011076
//OYUN TANITIMI
/*AYSE HOCA DERSTE YENI BUTON SINIFI TANIMLAYARAK YAPMISTI ONDAN BENDE OYLE YAPTIM DAHA SONRA OYUNDA SIZIN ISTEDIKLERINIZE
 EK OLARAK BEN GIRIS EKRANI YAPTIM VE CAN HAKKI TANIMLADIM. BOMBALARA HER BASISTA CAN AZALIYO VE BUDA UI DE TANIMLANAN CAN LABELINDA GUNCELLENIYOR.*/

#include "dialog.h"
#include "ui_dialog.h"
QDialog *dialog;

int sayac=0;
int ctrl=0;
int kontrol=4;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    dialog = new QDialog();//bunu giris ekranı için tanımladım...
    dialog->setStyleSheet("QDialog { background-image: url(:/tumresimler/images2/son.jpg); ""background-position: center; " "background-size: cover; }");
    dialog->setGeometry(0, 0, 1920, 1080);

    QLabel *hosgeldinizLabel = new QLabel(dialog);
    hosgeldinizLabel->setStyleSheet("color: black	;font-size: 36px; font-weight: bold; font-family: 'Arial', New Roman;");
    hosgeldinizLabel->setText("🍉OYUNUMA HOŞGELDİNİZ🍉");
    hosgeldinizLabel->setGeometry(475,45, 600, 50);

    QPushButton *baslaButton = new QPushButton("BAŞLA", dialog);
    baslaButton->setStyleSheet(
        "QPushButton {"
        "background-color: #228B22; color: black; font-size: 24px; font-weight: bold; border-radius: 15px; padding: 15px 32px; border: none;}"
        "QPushButton:hover {"
        "background-color: #228B22;}");
    baslaButton->setGeometry(640, 400, 250, 60);

    connect(baslaButton, &QPushButton::clicked, this, &Dialog::oyun_baslangic);
    dialog->exec();

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::sure_fonks()
{
    kesilen_yazitipi();
    sure_yazitipi();
    kacirilan_yazitipi();
    if (zaman > 0) {
        zaman--;
        ui->lbl_sure->setText(QString::number(zaman));
    } else
    {
       oyun_bitis();
    }
}

void Dialog::kesilen_yazitipi()
{
    QFont myfont;
    myfont.setBold(true);
    myfont.setPointSize(12);
    ui->lbl_kesilen->setFont(myfont);
    QString str = QString::number(kesilen_karpuz_sayisi);
    ui->lbl_kesilen->setText(str);
    QPalette mypalette;
    mypalette.setColor(QPalette::WindowText, QColor(Qt::green));
    ui->lbl_kesilen->setPalette(mypalette);
    ui->lbl_kesilen->setFont(myfont);
}

void Dialog::sure_yazitipi()
{
    QFont myfont;
    myfont.setBold(true);
    myfont.setPointSize(12);
    QPalette mypalette;
    mypalette.setColor(QPalette::WindowText, QColor(Qt::blue));
    ui->lbl_sure->setPalette(mypalette);
    ui->lbl_sure->setFont(myfont);
}

void Dialog::kacirilan_yazitipi()
{
    QFont myfont;
    myfont.setBold(true);
    myfont.setPointSize(12);
    ui->lbl_kacirilan->setFont(myfont);
    QString str = QString::number(kacirilan_karpuz_sayisi);
    ui->lbl_kacirilan->setText(str);
    QPalette mypalette;
    mypalette.setColor(QPalette::WindowText, QColor(Qt::red));
    ui->lbl_kacirilan->setPalette(mypalette);
    ui->lbl_kacirilan->setFont(myfont);
}

void Dialog::karpuz_olustur( )
{

    if(ctrl==0)
    {
        int rndm=QRandomGenerator::global()->bounded(0,sayac);
        QString string = karpuzKonumlari[rndm];
        QStringList liste = string.split(" ");
        int x_krdnt = liste[0].toInt();
        int y_krdnt = liste[1].toInt();
        yeniButton* karpuz_btn=new yeniButton(this);
        karpuz_btn->setStyleSheet("background: transparent; border: none;");
        karpuz_btn->setGeometry(x_krdnt,y_krdnt,50,100);
        karpuz_btn->setIcon(QIcon(":/resim/images/1.png"));
        karpuz_btn->setIconSize(QSize(50,80));
        karpuz_btn->show();
        yeniButton* button= qobject_cast<yeniButton*>(karpuz_btn);
        buttonlar.append( button);
        connect(karpuz_btn, &yeniButton::clicked, this, &Dialog::karpuz_tiklandimi);
    }
    else
    {
       karpuz_zamanlayici->stop();
    }
}

void Dialog::karpuz_kaydir()
{
    for (int i = 0; i < buttonlar.size(); i++)
    {
        if (buttonlar[i]->tiklandimi==false)
        {
            buttonlar[i]->setGeometry(buttonlar[i]->x(), buttonlar[i]->y() + 5, buttonlar[i]->width(), buttonlar[i]->height());
            if (buttonlar[i]->y() > this->height())
            {
                buttonlar[i]->hide();
                buttonlar.removeAt(i);
                kacirilan_karpuz_sayisi++;
                ui->lbl_kacirilan->setText(QString::number(kacirilan_karpuz_sayisi));
            }
        }
    }
}

void Dialog::karpuz_tiklandimi()
{
    int sayi=buttonlar.size();
     for (int i = sayi - 1; i >= 0; --i)
    {
        yeniButton* silinecekButon;
        if (buttonlar[i]->tiklandimi)
        {
            int x,y;
            x=buttonlar[i]->x();
            y=buttonlar[i]->y();
            buttonlar[i]->setStyleSheet("background: transparent; border: none;");
            buttonlar[i]->setIcon(QIcon(":/resim/images/2.png"));
            buttonlar[i]->setIconSize(QSize(50,80));
            buttonlar[i]->setGeometry(x,y,50,100);
            kesilen_karpuz_sayisi++;
            QString str = QString::number(kesilen_karpuz_sayisi);
            ui->lbl_kesilen->setText(str);
            silinecekButon = buttonlar[i];

            QTimer::singleShot(1500, this, [silinecekButon]() {//burada basılan karpuzları gızlemeye calsıyıorum...
                silinecekButon->hide();
            });
            buttonlar.removeOne(silinecekButon);//hocam sınglehot fonksıyonundan baska hıcbır yol ıse yaramadı...
            break;
        }

    }
}

void Dialog::oyun_bitis()
{
    zamanlayici->stop();
    karpuz_zamanlayici->stop();
    karpuz_hareket_zamanlayici->stop();
    bomba_hareket_zamanlayici->stop();
    bomba_zamanlayici->stop();
    QFile myfile("C:/Users/Elanur/Desktop/skorlar.txt");
    if (!myfile.open(QIODevice::ReadOnly))
    {
        return;
    }
    QTextStream mystream(&myfile);
    while(!mystream.atEnd())
    {
        QString satir = mystream.readLine();
        int skor= satir.toInt();
        skorlar.append(skor);
    }
    myfile.close();
    int max=0;
    for (int x:skorlar)
    {
        if (x>max)
        {
            max=x;
        }
    }
    if (max>ui->lbl_kesilen->text().toInt())
    {
         QMessageBox::information(this, "OYUN BİTTİ", "OYUN BİTTİ,MAXIMUM SKORU GECEMEDINIZ\nKESİLEN KARPUZ SAYISI: "+ui->lbl_kesilen->text()+"\nKACIRILAN KARPUZ SAYISI: "+ui->lbl_kacirilan->text()+"\nMAXIMUM SKOR: "+QString::number(max));
    }
    else
    {
        QMessageBox::information(this, "OYUN BİTTİ", "OYUN BİTTİ,MAXIMUM SKOR SIZDE\nKESİLEN KARPUZ SAYISI: "+ui->lbl_kesilen->text()+"\nKACIRILAN KARPUZ SAYISI: "+ui->lbl_kacirilan->text()+"\nMAXIMUM SKOR: "+QString::number(max));

    }
    skorlar.append(ui->lbl_kesilen->text().toInt());
    QFile myfile2("C:/Users/Elanur/Desktop/skorlar.txt");
    if (myfile2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&myfile2);
        for (int skor : skorlar)
        {
            stream << QString::number(skor) << "\n";
        }
        myfile2.close();
    }
    this->close();
}

void Dialog::oyun_baslangic()
{
        dialog->accept();
        ui->widget->setGeometry(0, 0, 1920,this->height());
        ui->widget_2->setGeometry(0, 100,1920,this->height());//burada da arka planı 100 konumundan baslattım hocam...
        zaman=30;
        zamanlayici=new QTimer(this);
        karpuz_zamanlayici = new QTimer(this);
        ui->lbl_sure->setText(QString::number(zaman));
        ui->lbl_kacirilan->setText("0");
        ui->lbl_kesilen->setText("0");
        ui->lbl_can->setText("❤️ ❤️ ❤️ ❤️");
        connect(zamanlayici, SIGNAL(timeout()), this, SLOT(sure_fonks()));
        connect(karpuz_zamanlayici, SIGNAL(timeout()), this, SLOT(karpuz_olustur()));
        karpuz_hareket_zamanlayici = new QTimer(this);
        connect(karpuz_hareket_zamanlayici, SIGNAL(timeout()), this, SLOT(karpuz_kaydir()));
        karpuz_hareket_zamanlayici->start(50);
        zamanlayici->start(1000);
        karpuz_zamanlayici->start(500);
        bomba_zamanlayici = new QTimer(this);
        bomba_hareket_zamanlayici = new QTimer(this);
        connect(bomba_zamanlayici, SIGNAL(timeout()), this, SLOT(bomba_olustur()));
        connect(bomba_hareket_zamanlayici, SIGNAL(timeout()), this, SLOT(bomba_kaydir()));
        bomba_zamanlayici->start(2500);
        bomba_hareket_zamanlayici->start(50);


        QFile myfile("C:/Users/Elanur/Desktop/konumlar.txt");
        if (!myfile.open(QIODevice::ReadOnly))
        {
            return;
        }
        QTextStream mystream(&myfile);
        while(!mystream.atEnd())
        {
            karpuzKonumlari.append(mystream.readLine());
            sayac++;
        }
        myfile.close();
}

void Dialog::cikis()
{
    this->close();
    dialog->close();
}

void Dialog::bomba_olustur()
{
    if (kontrol != 0)
    {

        int rndm = QRandomGenerator::global()->bounded(0, sayac);
        QString string = karpuzKonumlari[rndm];
        QStringList liste = string.split(" ");
        int x_krdnt = liste[0].toInt();
        int y_krdnt = liste[1].toInt();
        yeniButton* bomba_btn = new yeniButton(this);
        bomba_btn->setStyleSheet("background: transparent; border: none;");
        bomba_btn->setGeometry(x_krdnt, y_krdnt, 50, 100);
        bomba_btn->setIcon(QIcon(":/tumresimler/images2/bombatikla.png"));
        bomba_btn->setIconSize(QSize(55, 80));
        bomba_btn->show();
        yeniButton* button = qobject_cast<yeniButton*>(bomba_btn);
        bombalar.append(button);
        connect(bomba_btn, &yeniButton::clicked, this, &Dialog::bomba_tiklandimi);
    }
    else
    {
        zamanlayici->stop();
        karpuz_zamanlayici->stop();
        karpuz_hareket_zamanlayici->stop();
        bomba_hareket_zamanlayici->stop();
        bomba_zamanlayici->stop();
        oyun_bitis();
    }
}

void Dialog::bomba_kaydir()
{
    for (int i = 0; i < bombalar.size(); i++)
    {
        if (!bombalar[i]->tiklandimi)
        {
            bombalar[i]->setGeometry(bombalar[i]->x(), bombalar[i]->y() + 5, bombalar[i]->width(), bombalar[i]->height());
            if (bombalar[i]->y() > this->height())
            {
                bombalar[i]->hide();
                bombalar.removeAt(i);
            }
        }
    }
}

void Dialog::bomba_tiklandimi()
{
    for (int i = bombalar.size() - 1; i >= 0; --i)
    {
        if (bombalar[i]->tiklandimi)
        {
             kontrol--;
            if (kontrol==3)
            {
                ui->lbl_can->setText("❤️ ❤️ ❤️ ❌");
            }
            else if(kontrol==2)
            {
                ui->lbl_can->setText("❤️ ❤️ ❌ ❌");
            }
            else if(kontrol==1)
            {
                ui->lbl_can->setText("❤️ ❌ ❌ ❌");
            }
            else if (kontrol==0)
            {
                ui->lbl_can->setText("❌ ❌ ❌ ❌");
            }
            bombalar[i]->tiklandimi = true;
            bombalar[i]->setStyleSheet("background: transparent; border: none;");
            bombalar[i]->setIcon(QIcon(":/tumresimler/images2/bomba.png"));
            bombalar[i]->setIconSize(QSize(55,80));

            yeniButton* silinecekBomba = bombalar[i];
            QTimer::singleShot(1000, this, [silinecekBomba]() {
                silinecekBomba->hide();
            });

            bombalar.removeAt(i);
            break;
        }
    }
}
//DIGER SINIFIN CPP DOSYASI BURADA
//ELANUR USŞEN 23100011076
#include "yenibutton.h"

yeniButton::yeniButton(QWidget *parent)
    : QPushButton{parent}
{
    tiklandimi=false;
    connect(this,SIGNAL(clicked()),this,SLOT(tikla()));

}

void yeniButton::tikla()
{
    tiklandimi=true;
}

