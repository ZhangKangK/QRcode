#include "splitterwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SplitterWidget w;
    w.show();

    return a.exec();
}
