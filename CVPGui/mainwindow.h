#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QRect>
#include <QLabel>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void Init();
    void imageProc();
    void test();

private:
    Ui::MainWindow *ui;
private:
    QImage *image;
    QImage *grayImage;
    QImage *filterImage;
    QImage *binImage;

    QLabel *grayImageLabel;
    QLabel *filterImageLabel;
    QLabel *binImageLabel;

    QGridLayout *imageBox;

    QWidget *m_widget;

};

#endif // MAINWINDOW_H
