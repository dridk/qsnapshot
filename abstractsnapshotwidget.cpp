#include "abstractsnapshotwidget.h"

AbstractSnapshotWidget::AbstractSnapshotWidget(QWidget *parent) :
    QWidget(parent)
{


    setCursor(Qt::CrossCursor);


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

void AbstractSnapshotWidget::mouseDoubleClickEvent(QMouseEvent *)
{
        emit taken();
        close();
}

QPixmap AbstractSnapshotWidget::screenshot() const
{
    return mScreen;
}

void AbstractSnapshotWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter;
    painter.begin(this);

    if (!mScreen.isNull())
    {
        painter.drawPixmap(rect(),mScreen);

    }




    painter.end();

}

void AbstractSnapshotWidget::take()
{

    foreach (QScreen * s, qGuiApp->screens())
    {

        if (s->geometry().contains(QCursor::pos())){
            mScreen = s->grabWindow(0);
            mScreen = mScreen.copy(s->geometry());
        }

    }

    update();

}
