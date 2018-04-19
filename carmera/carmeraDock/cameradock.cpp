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

    newAct = new QAction(QIcon(":/icon/exe.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    //connect(newAct, SIGNAL(triggered()), this, SLOT(test()));

    open = new QAction(QIcon(":/icon/text.pngg"), tr("&Open"), this);
    open->setShortcuts(QKeySequence::Open);
    open->setStatusTip(tr("open a new file"));
    //connect(open, SIGNAL(triggered()), this, SLOT(test()));

    Save = new QAction(QIcon(":/icon/code.png"), tr("&Save"), this);
    Save->setShortcuts(QKeySequence::Save);
    Save->setStatusTip(tr("Save a new file"));
    //connect(Save, SIGNAL(triggered()), this, SLOT(test()));

    fileToolBar = new QToolBar(tr("工具栏"), this);
    fileToolBar = addToolBar(tr("file"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(open);
    fileToolBar->addAction(Save);
    fileToolBar->setBaseSize(50, 80);
    this->addToolBar(fileToolBar);
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
