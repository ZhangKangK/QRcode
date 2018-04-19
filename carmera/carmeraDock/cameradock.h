#ifndef CAMERADOCK_H
#define CAMERADOCK_H

#include <QMainWindow>
#include <QDockWidget>
#include <QToolBar>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>

namespace Ui {
class CameraDock;
}

class CameraDock : public QMainWindow
{
    Q_OBJECT

public:
    explicit CameraDock(QWidget *parent = 0);
    ~CameraDock();
    void setMainWindget();
    void initCamera();
    void createDockWidget();

private:
    Ui::CameraDock *ui;

    QDockWidget *cameraWidget;

    QToolBar *toolBar;

    QCamera *camera;//系统摄像头设备
    QCameraViewfinder *cameraViewFinder;//摄像头取景器部件
    QCameraImageCapture *cameraImageCapture;//截图部件
};

#endif // CAMERADOCK_H
