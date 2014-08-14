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

    connect(this,SIGNAL(screenTaken()),this,SLOT(addAreaItem()));


}

QPixmap AreaSnapeShotWidget::subscreen() const
{

    QRect zone = mRectItem->mapToScene(mRectItem->rect()).boundingRect().toRect();
  return screen().copy(zone);

}

void AreaSnapeShotWidget::addAreaItem()
{

    qDebug()<<"area added" <<rect();
    mRectItem->setScreen(screen());
    mRectItem->setRect(rect().adjusted(100,100,-100,-100));
    scene()->addItem(mRectItem);

}

