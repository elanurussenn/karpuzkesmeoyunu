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

