#ifndef IMAGEPROC_H
#define IMAGEPROC_H

#include <QLabel>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QWidget>
#include <QMainWindow>

class ImageProc : public QMainWindow
{
    Q_OBJECT

public:
    ImageProc(QWidget *parent = 0);
    ~ImageProc();
private:
    QImage *image;
    QLabel *imageLabel;
    QWidget *m_widget;
};

#endif // IMAGEPROC_H
