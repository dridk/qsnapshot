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

 QPixmap SnapshotWidget::pixmap() const
{
    return mPixmap.copy(mArea);
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
        painter.drawPixmap(rect(),mPixmap);

        painter.setBrush(QBrush(QColor(0,0,0,100)));
        painter.drawRect(rect());

    }


    drawAreaBox(painter);

}

void SnapshotWidget::mousePressEvent(QMouseEvent *event)
{




    // Test all corners

    if (cornerToRect(mArea.topLeft()).contains(event->pos())){
        mCurrentCorner = Qt::TopLeftCorner;
        return;
    }

    if (cornerToRect(mArea.topRight()).contains(event->pos())){
        mCurrentCorner = Qt::TopRightCorner;
        return;
    }

    if (cornerToRect(mArea.bottomRight()).contains(event->pos())){
        mCurrentCorner = Qt::BottomRightCorner;
        return;
    }

    if (cornerToRect(mArea.bottomLeft()).contains(event->pos())){
        mCurrentCorner = Qt::BottomLeftCorner;
        return;
    }



    if (mArea.contains(event->pos()))
    {
        mDiff = event->pos() - mArea.topLeft();;
        mMode = "move";
    }







}

void SnapshotWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

    emit shootted();
    close();


}

void SnapshotWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mMode = "";
    mCurrentCorner = -1;

}

void SnapshotWidget::mouseMoveEvent(QMouseEvent *event)
{


    if (mMode == "move") {


        mArea.moveTo(event->pos()- mDiff);

    }

    if (mCurrentCorner == Qt::BottomRightCorner)
        mArea.setBottomRight(event->pos());

    if (mCurrentCorner == Qt::TopRightCorner)
        mArea.setTopRight(event->pos());

    if (mCurrentCorner == Qt::TopLeftCorner)
        mArea.setTopLeft(event->pos());

    if (mCurrentCorner == Qt::BottomLeftCorner)
        mArea.setBottomLeft(event->pos());

    update();


}

void SnapshotWidget::drawAreaBox(QPainter &painter)
{

    painter.setOpacity(1);
    painter.drawPixmap(mArea, mPixmap, mArea);

    QFont font = QFont();
    font.setPixelSize(11);
    painter.setFont(font);

    QRect textRect = QRect(0,0,60,14);
    textRect.moveCenter(mArea.center());
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(textRect);
    painter.drawText(textRect, Qt::AlignCenter,QString("%1x%2").arg(mArea.width()).arg(mArea.height()));


    QList<QPoint> points;
    points<<mArea.topLeft()<<mArea.topRight()<<mArea.bottomLeft()<<mArea.bottomRight();

    painter.setBrush(QBrush("#ecf2f9"));
    painter.setPen(QPen("#3465a4"));

    foreach (const QPoint p, points)
        painter.drawRect(cornerToRect(p));





}

QRect SnapshotWidget::cornerToRect(const QPoint &p, int size)
{
    int dx = p.x() == mArea.x() ? -size : size;
    int dy = p.y() == mArea.y() ? -size : size;


    QRect rect = QRect(0,0, size*2, size*2);
    QPoint pos(p - rect.center());
    pos -= QPoint(dx+1,dy+1);
    rect.moveTo(pos);
    return rect;
}
