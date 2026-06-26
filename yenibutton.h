//ELANUR USŞEN 23100011076
#ifndef YENIBUTTON_H
#define YENIBUTTON_H

#include <QWidget>
#include <QPushButton>

class yeniButton : public QPushButton
{
    Q_OBJECT
public:
    explicit yeniButton(QWidget *parent = nullptr);
    bool tiklandimi;

signals:
public slots:
    void tikla();
};

#endif // YENIBUTTON_H
