#include "imagealgorithms.h"
#include <QRgb>
#include <QSize>

imageAlgorithms::imageAlgorithms() : d_width(0), d_height(0)
{
}

imageAlgorithms::imageAlgorithms(QImage *srcImage)
{
//    srcImagePtr = srcImage->bits();

//    int height = srcImage->height();
//    int width = srcImage->width();
//    QImage ret(width, height, QImage::Format_Indexed8);
//    ret.setColorCount(256);
//    for(int i = 0; i < 256; i++)
//    {
//        ret.setColor(i, qRgb(i, i, i));
//    }

//    switch(srcImage->format())
//    {
//    case QImage::Format_Indexed8:
//        for(int i = 0; i < height; i ++)
//        {
//            const uchar *pSrc = (uchar *)image.constScanLine(i);
//            uchar *pDest = (uchar *)ret.scanLine(i);
//            memcpy(pDest, pSrc, width);
//        }
//        break;
//    case QImage::Format_RGB32:
//    case QImage::Format_ARGB32:
//    case QImage::Format_ARGB32_Premultiplied:
//        for(int i = 0; i < height; i ++)
//        {
//            const QRgb *pSrc = (QRgb *)image.constScanLine(i);
//            uchar *pDest = (uchar *)ret.scanLine(i);

//            for( int j = 0; j < width; j ++)
//            {
//                 pDest[j] = qGray(pSrc[j]);
//            }
//        }
//        break;
//    }
}

void imageAlgorithms::image2uchar()
{

}

void imageAlgorithms::testImageProc(QImage &srcImage)
{
}

QImage *imageAlgorithms::rgb2gray(QImage *srcImage)
{
/*
    QSize size = rgbImage->size();//获得图像小
    QImage *grayImage = new QImage(size,QImage::Format_Indexed8);//创建同样大小深度为8(即每个像素占8位)的空白图
    int width=size.width();
    int height=size.height();
    uchar * rgbImageData=rgbImage->bits();//获得图像像素的首地址，因为存储顺序是BGRA,所以首地址指向B
    uchar * grayImageData=grayImage->bits();
    //若width不是4的倍数，会自动添加字节，使之对齐到4的倍数
    int realWidth1=rgbImage->bytesPerLine();//一行有多少个byte
    int realWidth2=grayImage->bytesPerLine();
    uchar * backup1=rgbImageData;
    uchar * backup2=grayImageData;
    for(int i=0;i<height;
    i++,
    rgbImageData=backup1+realWidth1*i,
    grayImageData=backup2+realWidth2*i){
    for(int j=0;j<width;j++){
    uchar r = (*(rgbImageData+2))*0.3;
    uchar g = (*(rgbImageData+1))*0.59;
    uchar b = (*rgbImageData)*0.11;//使用标准灰度化公式
    *grayImageData=r + g + b;
    rgbImageData+=4;//跳到下一个B,以为BGRA,原图是4个uchar作为一个像素
    grayImageData++;
    //因为灰色本身rgb值就必须相等，这里只用1个uchar存储颜色作为一个像素，所以需要用到color table
    //因此这里存的1个uchar只是color table的索引值，通过这个uchar在color table中找到真正的颜色
    }
    }
    //要注意color table用qvector实现，是一个顺序的连续的链表，里面存的是qrgb,qrgb的颜色顺序是0xAARRGGBB
    //灰度图的color table 很简单，就是从第一个是0x00000000,开始，到下一个0x00010101，不断加1，加到00ffffff
    QVector<QRgb> grayColorTable;
    uint rgb=0;
    for(int i=0;i<256;i++){
    grayColorTable.append(rgb);
    rgb+=0x00010101;//r,g,b值分别加1，a值不变,见QRgb说明
    }
    grayImage->setColorTable(grayColorTable);
    //grayImage->save("F:/QT/QRcoding/CVPGui/grayhahaR.jpg");
    //grayImage->load("F:/QT/QRcoding/CVPGui/grayhahaR.jpg");
    //可能是因为灰度图使用了colortable的原因，直接调用fromImage方法转成qpixmap会显示不出来，
    //只能先把灰度图保存,再重新load一遍,才能在qlabel中显示
    //ui->picLabel->setPixmap(QPixmap::fromImage(grayImage));
    return grayImage;
    */
    if(!srcImage)
    {
        return NULL;
    }
    QImage *destImage = new QImage(srcImage->width(), srcImage->height(), QImage::Format_RGB32);

    for (int y = 2; y < destImage->height(); y++)
    {
        QRgb *line = (QRgb *)srcImage->scanLine(y);

        for (int x = 2; x < destImage->width(); x++)
        {
            int average = qRed(line[x]) * 0.30 + qGreen(line[x]) * 0.59 + qBlue(line[x]) * 0.11;
            destImage->setPixel(x, y, qRgb(average, average, average));
        }
    }

    //ERROR_LOG("TEST OK");

    return destImage;

}

QImage *imageAlgorithms::rgb2bin(QImage *rgbImage)
{
    int threshold = 128;
    QSize size = rgbImage->size();
    QImage *binaryImage = new QImage(size, QImage::Format_RGB32);
    int width = size.width();
    int height = size.width();
    for(int i = 0; i < size.width(); i++)
    for(int j = 0; j < size.height(); j++)
    {
        QRgb pixel = rgbImage->pixel(i, j);
        int r = qRed(pixel) * 0.3;
        int g = qGreen(pixel) * 0.59;
        int b = qBlue(pixel) * 0.11;
        int rgb = r + g + b;//先把图像灰度化，转化为灰度图像

        if (rgb > threshold)//然后按某一阀值进行二值化
        {
            rgb = 255;
        }
        else
        {
            rgb = 0;
        }
        QRgb newPixel = qRgb(rgb, rgb, rgb);
        binaryImage->setPixel(i, j, newPixel);
    }
    //binaryImage.save(binaryFile);
    //ui.grayLabel->setPixmap(QPixmap(binaryFile));

    return binaryImage;
}

//中值滤波
QImage *imageAlgorithms::medianFilter(QImage *srcImage)
{
    if(!srcImage)
    {
        return NULL;
    }
    QImage *destImage = new QImage(srcImage->width(),
                                   srcImage->height(), QImage::Format_Grayscale8);

    int srcImage_height = srcImage->height();
    int srcImage_width = srcImage->width();
    for (int y = 0; y < srcImage_height; y++)
    {
        for (int x = 0; x < srcImage_width; x++)
        {
            QRgb *line = (QRgb *)srcImage->scanLine(y);
            if(y == 0 || x == 0 || (y == srcImage_height - 1) || (srcImage_width - 1 == x))
            {
                destImage->setPixel(x, y, qRgb(qRed(line[x]), qGreen(line[x]), qRed(line[x])));
            }
            else
            {
                QRgb *lineBefore = (QRgb *)srcImage->scanLine(y - 1);

                QRgb *lineLater = (QRgb *)srcImage->scanLine(y + 1);

                int pixel = (qRed(lineBefore[x - 1]) + qRed(lineBefore[x]) + qRed(lineBefore[x + 1])
                                + qRed(line[x - 1]) + qRed(line[x]) + qRed(line[x + 1])
                                + qRed(lineLater[x - 1]) + qRed(lineLater[x]) + qRed(lineLater[x + 1])) / 9;
                destImage->setPixel(x, y, qRgb(pixel, pixel, pixel));
            }
        }
    }

    return destImage;
}

QImage *imageAlgorithms::gray2binary(QImage *srcImage, int threshold)
{
    if(!srcImage)
    {
        return NULL;
    }
    QImage *destImage = new QImage(srcImage->width(), srcImage->height(), QImage::Format_Grayscale8);

    for (int y = 0; y < srcImage->height(); y++)
    {
        QRgb *line = (QRgb *)srcImage->scanLine(y);

        for (int x = 0; x < srcImage->width(); x++)
        {
            int average = qRed(line[x]) * 0.30 + qGreen(line[x]) * 0.59 + qRed(line[x]) * 0.11;
            if(average >= threshold)
            {
                destImage->setPixel(x, y, qRgb(255, 255, 255));
            }
            else
            {
                destImage->setPixel(x, y, qRgb(0, 0, 0));
            }
        }
    }

    return destImage;

//    QImage *destImage = new QImage(srcImage->width(), srcImage->height(), QImage::Format_Indexed8);

//    int width = destImage->width();
//    int height = destImage->height();
//    int bytePerLine = destImage->bytesPerLine();
//    unsigned char *data = destImage->bits();
//    unsigned char *binarydata = new unsigned char[bytePerLine * height];

//    unsigned char g;
//    for (int i = 0; i < height; i++)
//    {
//        for (int j = 0; j < width; j++)
//        {
//            g = *(data + i * bytePerLine + j * 3);
//            if(g >= THRESHOLD)
//            {
//                binarydata[i * bytePerLine + j * 3] = 0xFF;
//                binarydata[i * bytePerLine + j * 3 + 1] = 0xFF;
//                binarydata[i * bytePerLine + j * 3 + 2] = 0xFF;
//            }
//            else
//            {
//                binarydata[i * bytePerLine + j * 3] = 0x00;
//                binarydata[i * bytePerLine + j * 3 + 1] = 0x00;
//                binarydata[i * bytePerLine + j * 3 + 2] = 0x00;
//            }
//        }
//    }
//    QImage *outImage = new QImage(binarydata, width, height, bytePerLine, QImage::Format_RGB888);
    //    return outImage;
}

unsigned char *imageAlgorithms::bit32tobit8(QImage *srcImage)
{
//    QImage *destImage = new QImage(srcImage->width(), srcImage->height(), QImage::Format_RGB32);
//    unsigned char *dest = destImage->bits();

//    d_width = destImage->width() / 4 * 4;
//    d_height = destImage->height() / 4 * 4;

//    unsigned char pp_dest[d_width * d_height / 4];

//    for (int y = 0; y < d_height; y++)
//    {
//        for (int x = 0; x < d_width; x++)
//        {
//            (*pp_dest)++ = ((*dest) * 0.30 + (*(dest + 1)) * 0.59 + (*(dest + 2)) * 0.11);
//            dest = dest + 4;
//        }
//    }

//    return pp_dest;
}

void imageAlgorithms::painterShowImage(unsigned char *src)
{

}
