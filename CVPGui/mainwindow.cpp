#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagealgorithms.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageProc();
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    QRect deskRect = QApplication::desktop()->availableGeometry();
    int desk_width = deskRect.width() * 1 / 5;
    int desk_height = deskRect.height() * 1 / 5;

    qDebug() << desk_width << ":::" << desk_height;

    //main windows 布局
    m_widget = new QWidget();
    this->setCentralWidget(m_widget);

    m_widget->resize(desk_width, desk_height);

    imageBox = new QGridLayout;

    imageBox->addWidget(grayImageLabel, 0, 0);
    imageBox->addWidget(filterImageLabel, 0, 1);
    imageBox->addWidget(binImageLabel, 1, 0);

    m_widget->setLayout(imageBox);
}

void MainWindow::imageProc()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "F:/QT/QRcoding/image",
                                                    tr("Images (*.png *.xpm *.jpg)"));
    //QFile *file = new QFile("F:/QT/QRcoding/image/pigxi.png");
    //QString nameFile = file->fileName();
    //qDebug() << "nameFile:" << nameFile;
    qDebug() << fileName;

    //QImage::Format_RGB32
    image = new QImage(fileName);
    int img_width = image->width();
    int img_height = image->height();

    qDebug() << image->byteCount();

    //rgb转灰度图
    imageAlgorithms *plugin = new imageAlgorithms();
    grayImage = new QImage();
    grayImage = plugin->rgb2gray(image);
    qDebug() << grayImage->byteCount() << "..." << grayImage->bitPlaneCount();
    if(!grayImage)
    {
        qDebug() << "rgb2gray error";
        return;
    }

    //中值滤波
    filterImage = new QImage();
    filterImage = plugin->medianFilter(grayImage);
    qDebug() << filterImage->byteCount();
    if(!filterImage)
    {
        qDebug() << "filterImage error";
        return;
    }

    //二值化
    binImage = new QImage();
    binImage = plugin->rgb2bin(filterImage);
    qDebug() << binImage->byteCount();
    if(!binImage)
    {
        qDebug() << "binImage error";
        return;
    }

    grayImageLabel = new QLabel(tr("灰度图像"));
    grayImageLabel->setPixmap(QPixmap::fromImage(*grayImage));

    qDebug() << "grayBItCount:" << grayImage->bitPlaneCount();

    filterImageLabel = new QLabel(tr("中值滤波"));
    filterImageLabel->setPixmap(QPixmap::fromImage(*filterImage));

    binImageLabel = new QLabel(tr("二值化图像"));
    binImageLabel->setPixmap(QPixmap::fromImage(*binImage));
}

void MainWindow::test()
{
    QPixmap *pixmap = new QPixmap();
}
