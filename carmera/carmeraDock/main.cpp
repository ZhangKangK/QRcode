#include "cameradock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CameraDock w;
    w.show();

    return a.exec();
}
