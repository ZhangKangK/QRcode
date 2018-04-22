#ifndef SPLITTERWIDGET_H
#define SPLITTERWIDGET_H

#include <QMainWindow>
#include <QDockWidget>
#include <QGroupBox>
#include <QLabel>
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

    void layoutWidget();
    void createCameraWidget();
    void createConfigWidget();

private:
    QDockWidget *cameraWidget;  //相机窗口
    QDockWidget *configWidget;  //配置界面

    QLabel *configLabel;
    QGroupBox *configGroupBox;

    QCamera *camera;//系统摄像头设备
    QCameraViewfinder *cameraViewFinder;//摄像头取景器部件
    QCameraImageCapture *cameraImageCapture;//截图部件
};

#endif // SPLITTERWIDGET_H
