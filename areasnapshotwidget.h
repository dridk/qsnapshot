#ifndef SNAPSHOTWIDGET_H
#define SNAPSHOTWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include "rectareaitem.h"
#include "abstractsnapshotwidget.h"

class AreaSnapeShotWidget : public AbstractSnapshotWidget
{
    Q_OBJECT
public:
    explicit AreaSnapeShotWidget(QWidget *parent = 0);
     virtual QPixmap subscreen() const;


protected slots:
    void addAreaItem();

protected:
//    void paintEvent(QPaintEvent * event);

//    void mouseReleaseEvent(QMouseEvent * event);
//    void mouseMoveEvent(QMouseEvent * event);

//    void drawAreaBox(QPainter& painter);
//    QRect cornerToRect(const QPoint& p, int size=4);



private:
    QRect mArea;
    QString mMode;
    QPoint mDiff;
    int mCurrentCorner;
    RectAreaItem * mRectItem;


};

#endif // SNAPSHOTWIDGET_H
