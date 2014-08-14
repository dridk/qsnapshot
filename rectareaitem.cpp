#include "rectareaitem.h"
#include <QPainter>
#include <QDebug>
RectAreaItem::RectAreaItem(QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setBrush(QBrush(Qt::red));
    setSelected(true);
    mIsMoving = false;
    mCurrentCorner = -1;

    setRect(0,0, 200, 200);

    mCornerSize = 30;
}

void RectAreaItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QGraphicsRectItem::paint(painter,option,widget);

    painter->setBrush(QBrush(Qt::blue));

    foreach (QRectF corner, corners())
        painter->drawRect(corner);



}

void RectAreaItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QPointF mouse = mapFromScene(event->scenePos());


    foreach (QRectF corner, corners())
    {
        if (corner.contains(mouse))
        {
            qDebug()<<"touch";
            break;
        }

        ++mCurrentCorner;
    }



    mCurrentCorner = -1;

    QGraphicsRectItem::mousePressEvent(event);
}

void RectAreaItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{




    QGraphicsRectItem::mouseMoveEvent(event);

}

QList<QRectF> RectAreaItem::corners()
{

    QList<QRectF> list;
    list.append(topLeftCorner());
    list.append(topMiddleCorner());
    list.append(topRightCorner());
    list.append(middleRightCorner());
    list.append(middleLeftCorner());
    list.append(bottomLeftCorner());
    list.append(bottomRightCorner());
    list.append(bottomMiddleCorner());

    return list;

}

QRectF RectAreaItem::topLeftCorner()
{

    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveTo(rect().topLeft());
    return r;

}

QRectF RectAreaItem::topMiddleCorner()
{
    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveCenter(QPoint(rect().center().x(), rect().y() + mCornerSize/2));
    return r;

}

QRectF RectAreaItem::topRightCorner()
{
    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveTo(rect().topRight() - QPoint(mCornerSize,0));
    return r;

}

QRectF RectAreaItem::middleRightCorner()
{
    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveTo(rect().x(), rect().center().y() - mCornerSize/2);
    return r;

}

QRectF RectAreaItem::middleLeftCorner()
{
    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveTo(rect().right() - mCornerSize, rect().center().y()- mCornerSize/2);
    return r;
}

QRectF RectAreaItem::bottomLeftCorner()
{
    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveTo(rect().left(), rect().bottom() - mCornerSize);
    return r;
}

QRectF RectAreaItem::bottomMiddleCorner()
{
    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveCenter(QPointF(rect().center().x(), rect().bottom()-mCornerSize/2));

    return r;
}

QRectF RectAreaItem::bottomRightCorner()
{
    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveTo(rect().right()-mCornerSize, rect().bottom() - mCornerSize);
    return r;
}

