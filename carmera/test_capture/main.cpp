#include "test_capture.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test_capture w;
    w.show();

    return a.exec();
}
