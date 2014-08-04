#include "snapshotwidget.h"
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QCursor>
SnapshotWidget::SnapshotWidget(QWidget *parent) :
    QWidget(parent)
{

    mArea = QRect(0,0,100,100);
}

void SnapshotWidget::snapshot()
{


    foreach (QScreen * s, qGuiApp->screens())
    {

        if (s->geometry().contains(QCursor::pos())){
            mPixmap = s->grabWindow(0);
            mPixmap = mPixmap.copy(s->geometry());
        }

    }


    // mPixmap = qGuiApp->screens().first()->grabWindow(0);

    //    qDebug()<<qGuiApp->screens();

    //    foreach (QScreen * s, qGuiApp->screens())
    //        qDebug()<< s->geometry();




    update();

}

void SnapshotWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);





    if (!mPixmap.isNull())
    {
        painter.setOpacity(0.4);
        painter.drawPixmap(rect(),mPixmap);

    }


    drawAreaBox(painter);

}

void SnapshotWidget::mousePressEvent(QMouseEvent *event)
{

    if (mArea.contains(event->pos()))
    {
        mDiff = event->pos() - mArea.topLeft();;
        mMode = "move";
    }









}

void SnapshotWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mMode = "";

}

void SnapshotWidget::mouseMoveEvent(QMouseEvent *event)
{


    if (mMode == "move") {


        mArea.moveTo(event->pos()- mDiff);


    }

    update();


}

void SnapshotWidget::drawAreaBox(QPainter &painter)
{


    painter.drawRect(mArea);


    QList<QPoint> points;
    points<<mArea.topLeft()<<mArea.topRight()<<mArea.bottomLeft()<<mArea.bottomRight();


    foreach (const QPoint p, points){


        painter.drawRect(cornerToRect(p));


    }



}

QRect SnapshotWidget::cornerToRect(const QPoint &p, int size)
{


    QRect rect = QRect(0,0, size, size);

    rect.moveTo(p - rect.center());

    return rect;



}
