#include "splitterwidget.h"


SplitterWidget::SplitterWidget(QWidget *parent)
    : QMainWindow(parent)
{
    initParm();
    layoutWidget();

    createCameraWidget();
    createConfigWidget();

    connect(captureBnt, SIGNAL(clicked()), this, SLOT(captureBtnResponded()));
    connect(autoButton, SIGNAL(clicked()), this, SLOT(saveBtnResponded()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitBtnResponded()));
    connect(cameraImageCapture, SIGNAL(imageCaptured(int,QImage)), this,
            SLOT(cameraImageCaptured(int,QImage)));
}

void SplitterWidget::initParm()
{
    if(!imageLabel)
    {
        imageLabel = new QLabel(tr("image"));
    }
}

void SplitterWidget::test()
{}

void SplitterWidget::layoutWidget()
{
    mainSplitter = new QSplitter(Qt::Horizontal);
    leftSplitter = new QSplitter(Qt::Vertical, mainSplitter);
    listview = new QListView;
    treeview = new QTreeView;
    if(listview && treeview)
    {
        leftSplitter->addWidget(listview);
        leftSplitter->addWidget(treeview);
    }

    splitter = new QSplitter(Qt::Vertical, mainSplitter);

    mainGroupBox = new QGroupBox(tr("main window"));
    captureBnt = new QPushButton(tr("capture"));
    autoButton = new QPushButton(tr("continue"));
    exitButton = new QPushButton(tr("exit"));
    mainGroupHboxLayout = new QHBoxLayout;
    mainGroupHboxLayout->addWidget(captureBnt);
    mainGroupHboxLayout->addWidget(autoButton);
    mainGroupHboxLayout->addWidget(exitButton);
    mainGroupHboxLayout->addStretch(1);
    mainGroupBox->setLayout(mainGroupHboxLayout);

    resultDisplay = new QTextBrowser();

    if(resultDisplay && mainGroupBox)
    {
        splitter->addWidget(resultDisplay);
        splitter->addWidget(mainGroupBox);
    }

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
    //QCameraImageCapture::CaptureToBuffer
    //QCameraImageCapture::CaptureToFile
    //isCaptureDestinationSupported(QCameraImageCapture :: CaptureToBuffer);
    if(cameraImageCapture->isCaptureDestinationSupported(QCameraImageCapture :: CaptureToFile))
    {
        qDebug() << "supported";
    }
    else
    {
        qDebug() << "no supported";
        return;
    }

    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(cameraViewFinder);
    camera->start();//启动摄像头
}

void SplitterWidget::createConfigWidget()
{
    configWidget = new QDockWidget(tr("config"), this);
    //configWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    configGroupBox = new QGroupBox(tr("choose code"), configWidget);
    checkQR = new QCheckBox(tr("&QRcode"));
    checkDM = new QCheckBox(tr("&DMcode"));
    checkQR->setChecked(true);
    checkDM->setChecked(false);

    configGroutVboxLayout = new QVBoxLayout;
    configGroutVboxLayout->addWidget(checkQR);
    configGroutVboxLayout->addWidget(checkDM);
    configGroutVboxLayout->addStretch(1);
    configGroupBox->setLayout(configGroutVboxLayout);

    configLabel = new QLabel(tr("save"));
    addDockWidget(Qt::RightDockWidgetArea, configWidget);
    configWidget->setWidget(configGroupBox);
    configWidget->setMaximumSize(WIDGET_MAX_SIZE);
    configWidget->setMinimumSize(WIDGET_MIN_SIZE);
}

void SplitterWidget::captureBtnResponded()
{
    if(cameraImageCapture)
    {
        cameraImageCapture->capture();
    }

}
void SplitterWidget::saveBtnResponded()
{
    const QPixmap *pixmap = imageLabel->pixmap();
    if(pixmap) {pixmap->save("D:\\a.jpg");}
}
void SplitterWidget::exitBtnResponded()
{
    camera->stop();
    this->close();
}
void SplitterWidget::cameraImageCaptured(int id, QImage image)
{
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void SplitterWidget::createActions()
{
    newAct = new QAction(QIcon(":/image/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(test()));

    open = new QAction(QIcon(":/image/open.png"), tr("&Open"), this);
    open->setShortcuts(QKeySequence::Open);
    open->setStatusTip(tr("open a new file"));
    connect(open, SIGNAL(triggered()), this, SLOT(test()));
    Save = new QAction(QIcon(":/image/save.png"), tr("&Save"), this);
    Save->setShortcuts(QKeySequence::Save);
    Save->setStatusTip(tr("Save a new file"));
    connect(Save, SIGNAL(triggered()), this, SLOT(test()));

    saveAs = new QAction( tr("&SaveAs"), this);
    saveAs->setShortcuts(QKeySequence::SaveAs);
    newAct->setStatusTip(tr("SaveAs a new file"));
    connect(saveAs, SIGNAL(triggered()), this, SLOT(test()));
    exit = new QAction( tr("&exit"), this);
    exit->setShortcuts(QKeySequence::Close);
    exit->setStatusTip(tr("exit a new file"));
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    cut = new QAction(QIcon(":/image/cut.png"), tr("&Cut"), this);
    cut->setShortcuts(QKeySequence::Cut);
    cut->setStatusTip(tr("Save a new file"));
    connect(cut, SIGNAL(triggered()), this, SLOT(test()));

    copy = new QAction(QIcon(":/image/copy.png"), tr("&Copy"), this);
    saveAs->setShortcuts(QKeySequence::Copy);
    copy->setStatusTip(tr("SaveAs a new file"));
    connect(copy, SIGNAL(triggered()), this, SLOT(test()));

    past = new QAction(QIcon(":/image/paste.png"), tr("&Paste"),this);
    past->setShortcuts(QKeySequence::Paste);
    past->setStatusTip(tr("exit a new file"));
    connect(past, SIGNAL(triggered()), this, SLOT(close()));
    about = new QAction(tr("&about"), this);
    about->setStatusTip(tr("SaveAs a new file"));
    connect(about, SIGNAL(triggered()), this, SLOT(test()));
    aboutQt = new QAction(tr("&aboutQt"),this);
    aboutQt->setStatusTip(tr("exit a new file"));
    connect(aboutQt, SIGNAL(triggered()), this, SLOT(close()));
}

void SplitterWidget::createMenus()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(open);
    fileToolBar->addAction(Save);
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cut);
    editToolBar->addAction(copy);
    editToolBar->addAction(past);
}

void SplitterWidget::createToolBars()
{
    //创建一个name为file的菜单栏
    //fileMenu = new QMenuBar();
    fileMenu = menuBar()->addMenu(tr("&File"));
    //在这个菜单栏添加action即下拉菜单
    fileMenu->addAction(newAct);
    fileMenu->addAction(open);
    fileMenu->addAction(Save);
    fileMenu->addAction(saveAs);
    //添加一个分割器
    fileMenu->addSeparator();
    //推出下拉菜单
    fileMenu->addAction(exit);
    //创建一个name为edit的菜单栏
    //editMenu = new QMenuBar();
    editMenu = menuBar()->addMenu(tr("&Edit"));
    //在这个菜单栏添加action即下拉菜单
    editMenu->addAction(cut);
    editMenu->addAction(copy);
    editMenu->addAction(past);
    //创建一个name为help的菜单栏\
    helpMenu = menuBar()->addMenu(tr("&Help"));
    //在这个菜单栏添加action即下拉菜单
    helpMenu->addAction(about);
    helpMenu->addAction(aboutQt);
}

SplitterWidget::~SplitterWidget()
{

}
