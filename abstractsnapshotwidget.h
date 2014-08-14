#ifndef ABSTRACTSNAPSHOTWIDGET_H
#define ABSTRACTSNAPSHOTWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QPainter>
#include <QGraphicsView>
#include <QtWidgets>

class AbstractSnapshotWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AbstractSnapshotWidget(QWidget *parent = 0);
    virtual QPixmap subscreen() const = 0;
    const QPixmap &screen() const;

    void drawBackground(QPainter * p, const QRectF& rect);
    void resizeEvent(QResizeEvent * event);


protected:
    void mouseDoubleClickEvent(QMouseEvent *);

public slots:
    virtual void takeScreen();



signals:
    void capture();
    void screenTaken();
    void subscreenTaken();


private:
    QPixmap mScreen;
    QGraphicsScene * mScene;
    QGraphicsPixmapItem * mBackground;


};

#endif // ABSTRACTSNAPSHOTWIDGET_H
