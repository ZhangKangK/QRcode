#ifndef TEST_CAPTURE_H
#define TEST_CAPTURE_H

#include <QDialog>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class test_capture;
}

class test_capture : public QDialog
{
    Q_OBJECT

public:
    explicit test_capture(QWidget *parent = 0);
    ~test_capture();

private:
    Ui::test_capture *ui;

private:
    QCamera *camera;//系统摄像头设备
    QCameraViewfinder *cameraViewFinder;//摄像头取景器部件
    QCameraImageCapture *cameraImageCapture;//截图部件

    QPushButton *captureBtn;
    QPushButton *saveBtn;
    QPushButton *exitBtn;
    QLabel *displayLabel;

    void translateLanguage();

private slots:
    void captureBtnResponded();
    void saveBtnResponded();
    void exitBtnResponded();
    void cameraImageCaptured(int id, QImage image);
};

#endif // TEST_CAPTURE_H
