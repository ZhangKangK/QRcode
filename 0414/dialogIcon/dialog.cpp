#include "dialog.h"
#include <QDebug>
#include <QPushButton>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    QPushButton *pushButton = new QPushButton(this);

    QIcon icon1(":/icon/pigxi.png");
    this->setWindowIcon(icon1);

    pushButton->setGeometry(100, 100, 300, 300);
    pushButton->setIcon(icon1);

}

Dialog::~Dialog()
{

}
