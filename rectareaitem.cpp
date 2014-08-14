#include "rectareaitem.h"
#include <QPainter>
#include <QDebug>
RectAreaItem::RectAreaItem(QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setBrush(QBrush(Qt::white));
    setSelected(true);
    mIsMoving = false;
    mCurrentCorner = -1;

    setRect(0,0, 200, 200);
    mCornerSize = 10;





}

void RectAreaItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    //    QGraphicsRectItem::paint(painter,option,widget);

    painter->setPen(QPen(Qt::white));
    painter->setOpacity(1);

    QRectF zone = mapToScene(rect()).boundingRect();

    painter->drawPixmap(rect(), mScreen, zone);

    if (!mIsMoving) {
        painter->setPen(QPen(Qt::white));
        painter->setBrush(QColor(128,128,128,200));

        foreach (QRectF corner, corners())
            painter->drawRect(corner);
    }



}

QRectF RectAreaItem::boundingRect() const
{

    return QGraphicsRectItem::boundingRect();

}

void RectAreaItem::setScreen(const QPixmap &pix)
{
    mScreen = pix;
}

void RectAreaItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QPointF mouse = mapFromScene(event->scenePos());

    if (event->button() == Qt::LeftButton){
        mCurrentCorner = 0;
        foreach (QRectF corner, corners())
        {
            if (corner.contains(mouse))
            {
                qDebug()<<"Touch";
                mIsMoving = true;
                mOldRect = rect();
                return;
            }

            ++mCurrentCorner;
        }
    }

    mIsMoving = false;
    mCurrentCorner = -1;

    QGraphicsRectItem::mousePressEvent(event);
}

void RectAreaItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{


    if (mIsMoving)
    {
        QPointF mouse = mapFromScene(event->scenePos());
        QRectF r = mOldRect;

        switch (mCurrentCorner)
        {

        case 0: r.setTopLeft(mouse);break;
        case 1: r.setTop(mouse.y());break;
        case 2: r.setTopRight(mouse);break;
        case 3: r.setLeft(mouse.x());break;
        case 4: r.setRight(mouse.x());break;
        case 5: r.setBottomLeft(mouse);break;
        case 6: r.setBottomRight(mouse);break;
        case 7: r.setBottom(mouse.y());break;


        }




        setRect(r.normalized());

    }

    else
        QGraphicsRectItem::mouseMoveEvent(event);

}

void RectAreaItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{


    mIsMoving = false;
    update();

    QGraphicsRectItem::mouseReleaseEvent(event);

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
    r.moveTo(rect().topRight() - QPoint(mCornerSize+1,0));
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
    r.moveTo(rect().right() - mCornerSize-1, rect().center().y()- mCornerSize/2);
    return r;
}

QRectF RectAreaItem::bottomLeftCorner()
{
    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveTo(rect().left(), rect().bottom() - mCornerSize-1);
    return r;
}

QRectF RectAreaItem::bottomMiddleCorner()
{
    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveCenter(QPointF(rect().center().x(), rect().bottom()-mCornerSize/2 -1));

    return r;
}

QRectF RectAreaItem::bottomRightCorner()
{
    QRectF r = QRectF(0,0, mCornerSize, mCornerSize);
    r.moveTo(rect().right()-mCornerSize-1, rect().bottom() - mCornerSize -1);
    return r;
}

