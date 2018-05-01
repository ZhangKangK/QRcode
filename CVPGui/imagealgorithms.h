#ifndef IMAGEALGORITHMS_H
#define IMAGEALGORITHMS_H

#include <QImage>
#include <QPainter>
#include "cvpgui.h"

#define BIN_THRESHOLD 150

class imageAlgorithms : public QImage
{
public:
    imageAlgorithms();
    imageAlgorithms(QImage *srcImage);

    void image2uchar();

    void testImageProc(QImage &srcImage);
    QImage *rgb2gray(QImage *rgbImage);
    QImage *rgb2bin(QImage * rgbImage);
    QImage *medianFilter(QImage *srcImage);
    QImage *gray2binary(QImage *srcImage, int threshold);
    unsigned char *bit32tobit8(QImage *srcImage);

    void painterShowImage(unsigned char *src);

private:
    int d_width;
    int d_height;
    uchar *srcImagePtr;
    QPainter *painter;
};

#endif // IMAGEALGORITHMS_H
