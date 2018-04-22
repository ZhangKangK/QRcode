#ifndef SPLITTERWIDGET_H
#define SPLITTERWIDGET_H

#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QImage>
#include <QToolBar>
#include <QAction>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QDockWidget>
#include <QSplitter>
#include <QTextBrowser>
#include <QPushButton>
#include <QTextEdit>
#include <QListView>
#include <QTreeView>
#include <QDebug>
#include <QPixmap>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>

#define WIDGET_MAX_SIZE QSize(500, 500) //窗口最大尺寸
#define WIDGET_MIN_SIZE QSize(100, 100) //窗口最小尺寸

class SplitterWidget : public QMainWindow
{
    Q_OBJECT

public:
    SplitterWidget(QWidget *parent = 0);
    ~SplitterWidget();
    void initParm();
    void layoutWidget();
    void createCameraWidget();
    void createConfigWidget();
private slots:
    void test();
    void captureBtnResponded();
    void saveBtnResponded();
    void exitBtnResponded();
    void cameraImageCaptured(int id, QImage image);
private:
    void createActions();
    void createMenus();
    void createToolBars();

private:
    //file菜单
    QMenu * fileMenu;
    QMenu * editMenu;
    QMenu * helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    //定义了file的下拉菜单为 new open save saveAS exit
    QAction *newAct;
    QAction *open;
    QAction *Save;
    QAction *saveAs;
    QAction *exit;
    //定义edit的下拉菜单cut copy past
    QAction *cut;
    QAction *copy;
    QAction *past;
    //定义help的下拉菜单about aboutQt
    QAction *about;
    QAction *aboutQt;

    //显示
    QCheckBox *checkQR;
    QCheckBox *checkDM;

    //QPixmap *pixmap;
    QLabel *configLabel;
    QLabel *imageLabel;

    QGroupBox *mainGroupBox;
    QGroupBox *configGroupBox;
    QHBoxLayout *mainGroupHboxLayout;
    QVBoxLayout *configGroutVboxLayout;
    QTextBrowser *resultDisplay;

    QListView *listview;
    QTreeView *treeview;

    QSplitter *splitter;
    QSplitter *mainSplitter;
    QSplitter *leftSplitter;

    QPushButton *captureBnt;
    QPushButton *autoButton;
    QPushButton *exitButton;

    //配置界面
    QDockWidget *configWidget;

    //相机
    QDockWidget *cameraWidget;
    QCamera *camera;//系统摄像头设备
    QCameraViewfinder *cameraViewFinder;//摄像头取景器部件
    QCameraImageCapture *cameraImageCapture;//截图部件
};

#endif // SPLITTERWIDGET_H
