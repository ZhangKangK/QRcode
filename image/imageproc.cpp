#include "imageproc.h"
#include <QFile>
#include <QImageReader>
#include <QFileDialog>
#include <QHBoxLayout>

ImageProc::ImageProc(QWidget *parent)
    : QMainWindow(parent)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "F:/QT/QRcoding/image",
                                                    tr("Images (*.png *.xpm *.jpg)"));
    //QFile *file = new QFile("F:/QT/QRcoding/image/pigxi.png");
    //QString nameFile = file->fileName();
    //qDebug() << "nameFile:" << nameFile;
    qDebug() << fileName;
    image = new QImage(fileName);

    qDebug() << "width:" << image->width() << "height:" << image->height();

    imageLabel = new QLabel(tr("图像"));
    imageLabel->setPixmap(QPixmap::fromImage(*image));

    m_widget = new QWidget();
    this->setCentralWidget(m_widget);

    QHBoxLayout *hBox = new QHBoxLayout;
    hBox->addWidget(imageLabel);

    m_widget->setLayout(hBox);
}

ImageProc::~ImageProc()
{

}
