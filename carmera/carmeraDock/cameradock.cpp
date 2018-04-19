#include "cameradock.h"
#include "ui_cameradock.h"
#include <QTextEdit>

CameraDock::CameraDock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CameraDock)
{
    ui->setupUi(this);
    setMainWindget();
    initCamera();
}

void CameraDock::setMainWindget()
{
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    toolBar = new QToolBar(tr("工具栏"), this);
    toolBar->setBaseSize(50, 80);
    this->addToolBar(toolBar);
}

void CameraDock::initCamera()
{
    camera = new QCamera();
    cameraViewFinder = new QCameraViewfinder();
    cameraImageCapture = new QCameraImageCapture(camera);

    cameraWidget = new QDockWidget("camera", this);
    addDockWidget(Qt::RightDockWidgetArea, cameraWidget);
    cameraWidget->setWidget(cameraViewFinder);

    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(cameraViewFinder);
    camera->start();//启动摄像头
}
void CameraDock::createDockWidget()
{}

CameraDock::~CameraDock()
{
    delete ui;
}
