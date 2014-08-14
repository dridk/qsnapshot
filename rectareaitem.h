#ifndef RECTAREAITEM_H
#define RECTAREAITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMoveEvent>

class RectAreaItem : public QGraphicsRectItem
{

public:
    explicit RectAreaItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRect cornerToRect(const QPoint &p, int size = 4);


    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

protected:

    QList<QRectF> corners();

    QRectF topLeftCorner();
    QRectF topMiddleCorner();
    QRectF topRightCorner();
    QRectF middleRightCorner();
    QRectF middleLeftCorner();
    QRectF bottomLeftCorner();
    QRectF bottomMiddleCorner();
    QRectF bottomRightCorner();




private:
    int mCornerSize;
    bool mIsMoving;
    int mCurrentCorner;
    QRectF mOldRect;



};

#endif // RECTAREAITEM_H
