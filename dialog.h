//ELANUR USŞEN 23100011076
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QFile>
#include <QPushButton>
#include <QList>
#include "yenibutton.h"
#include <QRandomGenerator>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
//kullandıgım tum fonksıyonlar burada
private slots:
    void sure_fonks();
    void kesilen_yazitipi();
    void sure_yazitipi();
    void kacirilan_yazitipi();
    void karpuz_olustur();
    void karpuz_kaydir();
    void karpuz_tiklandimi();
    void oyun_bitis();
    void oyun_baslangic();
    void cikis();
    void bomba_olustur();
    void bomba_kaydir();
    void bomba_tiklandimi();

private:
    Ui::Dialog *ui;
    QList<yeniButton*> buttonlar;
    QTimer *bomba_zamanlayici;
    QTimer *bomba_hareket_zamanlayici;
    QList<yeniButton*> bombalar;
    int zaman;
    QTimer *zamanlayici;
    QTimer *karpuz_zamanlayici;
    QStringList karpuzKonumlari;
    QTimer* karpuz_hareket_zamanlayici;
    int kesilen_karpuz_sayisi=0;
    int kacirilan_karpuz_sayisi=0;
     QList<int> skorlar;
};
#endif // DIALOG_H
