#ifndef SPLITTERWIDGET_H
#define SPLITTERWIDGET_H

#include <QMainWindow>

class SplitterWidget : public QMainWindow
{
    Q_OBJECT

public:
    SplitterWidget(QWidget *parent = 0);
    ~SplitterWidget();
};

#endif // SPLITTERWIDGET_H
