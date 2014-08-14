#include "areasnapshotwidget.h"
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QCursor>

AreaSnapeShotWidget::AreaSnapeShotWidget(QWidget *parent) :
    AbstractSnapshotWidget(parent)
{

    setObjectName("Area mode");
    setMouseTracking(true);
    mRectItem = new RectAreaItem;

    mIsAreaEnable = false;



}

QPixmap AreaSnapeShotWidget::subscreen() const
{

    QRect zone = mRectItem->mapToScene(mRectItem->rect()).boundingRect().toRect();
    return screen().copy(zone);

}

void AreaSnapeShotWidget::mousePressEvent(QMouseEvent *event)
{


    if (!mIsAreaEnable) {
    mRectItem->setScreen(screen());
    mRectItem->setRect(0,0,2,2);
    scene()->addItem(mRectItem);
    mRectItem->setPos(event->pos());

    mIsAreaEnable = true;

    }

    AbstractSnapshotWidget::mousePressEvent(event);


}

void AreaSnapeShotWidget::closeEvent(QCloseEvent *event)
{

    mIsAreaEnable = false;
    scene()->removeItem(mRectItem);
    AbstractSnapshotWidget::closeEvent(event);
}

void AreaSnapeShotWidget::setAreaEnable(bool active)
{

mIsAreaEnable = active;

}


