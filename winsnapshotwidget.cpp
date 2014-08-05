#include "winsnapshotwidget.h"
#include <QGuiApplication>
#include <QDebug>
#include <QWindow>
WinSnapshotWidget::WinSnapshotWidget(QWidget *parent) :
    AbstractSnapshotWidget(parent)
{

    mPix = QPixmap(50,50);
    mPix.fill(Qt::red);
    setObjectName("Windows under cursor");
}

QPixmap WinSnapshotWidget::screenshot() const
{
   return mPix;
}



void WinSnapshotWidget::take()
{

    qDebug()<<qGuiApp->allWindows();


    foreach (QWindow * w, qGuiApp->allWindows())
        qDebug()<<w->position();

    QWindow * window = qGuiApp->allWindows()[3];



    if (window == NULL)
        return;

    mPix = qGuiApp->primaryScreen()->grabWindow(window->winId());

    emit taken();

}
