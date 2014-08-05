#include "areasnapshotwidget.h"
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QCursor>

AreaSnapeShotWidget::AreaSnapeShotWidget(QWidget *parent) :
    AbstractSnapshotWidget(parent)
{

    mArea = QRect(0,0,100,100);

    setObjectName("Area mode");

    setMouseTracking(true);



}

QPixmap AreaSnapeShotWidget::screenshot() const
{
    return screen().copy(mArea);

}

void AreaSnapeShotWidget::paintEvent(QPaintEvent *event)
{
    AbstractSnapshotWidget::paintEvent(event);


    QPainter painter;
    painter.begin(this);

    // draw overlay
    painter.setBrush(QBrush(QColor(0,0,0,100)));
    painter.drawRect(rect());
    drawAreaBox(painter);
    painter.end();

}

void AreaSnapeShotWidget::mousePressEvent(QMouseEvent *event)
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



void AreaSnapeShotWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mMode = "";
    mCurrentCorner = -1;
    if (mArea.contains(event->pos()))
        setCursor(Qt::OpenHandCursor);
    else
        setCursor(Qt::CrossCursor);


}

void AreaSnapeShotWidget::mouseMoveEvent(QMouseEvent *event)
{


    if (mArea.contains(event->pos() ))
        setCursor(Qt::OpenHandCursor);

    else
        setCursor(Qt::CrossCursor);

    if (mMode == "move") {

        setCursor(	Qt::ClosedHandCursor	);
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

void AreaSnapeShotWidget::drawAreaBox(QPainter &painter)
{

    painter.setOpacity(1);
    painter.drawPixmap(mArea, screen(), mArea);

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

QRect AreaSnapeShotWidget::cornerToRect(const QPoint &p, int size)
{
    int dx = p.x() == mArea.x() ? -size : size;
    int dy = p.y() == mArea.y() ? -size : size;


    QRect rect = QRect(0,0, size*2, size*2);
    QPoint pos(p - rect.center());
    pos -= QPoint(dx+1,dy+1);
    rect.moveTo(pos);
    return rect;
}
