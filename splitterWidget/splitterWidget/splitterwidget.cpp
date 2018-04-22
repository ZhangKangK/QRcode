#include "splitterwidget.h"
#include <QSplitter>
#include <QTextEdit>

SplitterWidget::SplitterWidget(QWidget *parent)
    : QMainWindow(parent)
{
    layoutWidget();
    createCameraWidget();
    createConfigWidget();
}

void SplitterWidget::layoutWidget()
{
    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal);
    QTextEdit *leftEdit = new QTextEdit(QObject::tr("左窗口"), mainSplitter);
    leftEdit->setAlignment(Qt::AlignCenter);

    QSplitter *rightSplitter = new QSplitter(Qt::Vertical, mainSplitter);
    rightSplitter->setOpaqueResize(false);



    //QTextEdit *upEdit = new QTextEdit(QObject::tr("上窗口"), rightSplitter);
    //cameraWidget->setAlignment(Qt::AlignCenter);

    QTextEdit *bottomEdit = new QTextEdit(QObject::tr("下窗口"), rightSplitter);
    bottomEdit->setAlignment(Qt::AlignCenter);

    mainSplitter->setStretchFactor(1, 1);
    mainSplitter->setWindowTitle(QObject::tr("分割窗口"));

    setCentralWidget(mainSplitter);
    mainSplitter->show();
}

void SplitterWidget::createCameraWidget()
{
    camera = new QCamera();
    cameraViewFinder = new QCameraViewfinder();
    cameraImageCapture = new QCameraImageCapture(camera);

    cameraWidget = new QDockWidget(tr("camera"), this);
    //cameraWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    addDockWidget(Qt::RightDockWidgetArea, cameraWidget);
    cameraWidget->setWidget(cameraViewFinder);
    cameraWidget->setMaximumSize(WIDGET_MAX_SIZE);
    cameraWidget->setMinimumSize(WIDGET_MIN_SIZE);

    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(cameraViewFinder);
    camera->start();//启动摄像头
}
void SplitterWidget::createConfigWidget()
{
    configWidget = new QDockWidget(tr("config"), this);
    configGroupBox = new QGroupBox(configWidget);
    //configWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    configLabel = new QLabel(tr("save"));
    addDockWidget(Qt::RightDockWidgetArea, configWidget);
    configWidget->setWidget(configGroupBox);
    configWidget->setMaximumSize(WIDGET_MAX_SIZE);
    configWidget->setMinimumSize(WIDGET_MIN_SIZE);



}

SplitterWidget::~SplitterWidget()
{

}
