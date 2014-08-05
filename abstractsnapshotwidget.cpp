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
