#include "abstractsnapshotwidget.h"

AbstractSnapshotWidget::AbstractSnapshotWidget(QWidget *parent) :
    QGraphicsView(parent)
{


    //    setCursor(Qt::CrossCursor);
    mScene = new QGraphicsScene;
    setScene(mScene);


    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


   connect(this,SIGNAL(subscreenTaken()),this,SLOT(close()));


}

const QPixmap &AbstractSnapshotWidget::screen() const
{
    return mScreen;
}




void AbstractSnapshotWidget::drawBackground(QPainter *p, const QRectF &rect)
{
    p->setBrush(Qt::black);
    p->setPen(Qt::NoPen);
    p->drawRect(rect);

    p->setOpacity(0.4);

    p->drawPixmap(0,0, mScreen);



}

void AbstractSnapshotWidget::resizeEvent(QResizeEvent *event)
{

    scene()->setSceneRect(QRect(0,0,event->size().width(), event->size().height()));


    QGraphicsView::resizeEvent(event);

}

void AbstractSnapshotWidget::mouseDoubleClickEvent(QMouseEvent * event)
{

    emit subscreenTaken();

}




//void AbstractSnapshotWidget::paintEvent(QPaintEvent *event)
//{

//    QPainter painter;
//    painter.begin(this);

//    if (!mScreen.isNull())
//    {
//        painter.drawPixmap(rect(),mScreen);

//    }




//    painter.end();

//}

void AbstractSnapshotWidget::takeScreen()
{
    qDebug()<<"take";

    foreach (QScreen * s, qGuiApp->screens())
    {

        if (s->geometry().contains(QCursor::pos())){
            mScreen = s->grabWindow(0);
            mScreen = mScreen.copy(s->geometry());
        }

    }


    resize(mScreen.size());
    update();
    emit screenTaken();


}
