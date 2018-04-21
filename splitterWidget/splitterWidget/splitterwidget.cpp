#include "splitterwidget.h"
#include <QSplitter>
#include <QTextEdit>

SplitterWidget::SplitterWidget(QWidget *parent)
    : QMainWindow(parent)
{
    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal);
    QTextEdit *leftEdit = new QTextEdit(QObject::tr("左窗口"), mainSplitter);
    leftEdit->setAlignment(Qt::AlignCenter);

    QSplitter *rightSplitter = new QSplitter(Qt::Vertical, mainSplitter);
    rightSplitter->setOpaqueResize(false);

    QTextEdit *upEdit = new QTextEdit(QObject::tr("上窗口", rightSplitter));
    upEdit->setAlignment(Qt::AlignCenter);

    QTextEdit *bottomEdit = new QTextEdit(QObject::tr("下窗口", rightSplitter));
    bottomEdit->setAlignment(Qt::AlignCenter);

    mainSplitter->setStretchFactor(1, 1);
    mainSplitter->setWindowTitle(QObject::tr("分割窗口"));

    setCentralWidget(mainSplitter);
    mainSplitter->show();
}

SplitterWidget::~SplitterWidget()
{

}
