#include "abstractsnapshotwidget.h"

AbstractSnapshotWidget::AbstractSnapshotWidget(QWidget *parent) :
    QGraphicsView(parent)
{


//    setCursor(Qt::CrossCursor);
    mScene = new QGraphicsScene;
    setScene(mScene);

    mBackground = new QGraphicsPixmapItem;

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    resize(1000,800);
    setSceneRect(rect());


}

const QPixmap &AbstractSnapshotWidget::screen() const
{
    return mScreen;
}

void AbstractSnapshotWidget::drawHeader(const QString &message, QPainter &painter)
{

    QRect header(0,0,width(), 20);
    painter.setBrush(QColor("#2ca8c2"));
    painter.setPen(Qt::NoPen);
    painter.drawRect(header);
    int mg = 3;
    painter.setPen(Qt::white);
    painter.drawText(header.adjusted(mg,mg,-mg,-mg),Qt::AlignLeft|Qt::AlignVCenter,message);


}


QPixmap AbstractSnapshotWidget::screenshot() const
{
    return mScreen;
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

void AbstractSnapshotWidget::take()
{
    qDebug()<<"take";

    foreach (QScreen * s, qGuiApp->screens())
    {

        if (s->geometry().contains(QCursor::pos())){
            mScreen = s->grabWindow(0);
            mScreen = mScreen.copy(s->geometry());
        }

    }



    mBackground->setPixmap(mScreen);

    mScene->addItem(mBackground);


}
