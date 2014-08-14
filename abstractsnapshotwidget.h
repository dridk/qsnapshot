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
    virtual QPixmap screenshot() const = 0;
    const QPixmap &screen() const;

    void drawHeader(const QString& message, QPainter& painter);

public slots:
    virtual void take();



protected slots:
//    void paintEvent(QPaintEvent * event);



signals:
    void taken();


private:
    QPixmap mScreen;
    QGraphicsScene * mScene;
    QGraphicsPixmapItem * mBackground;


};

#endif // ABSTRACTSNAPSHOTWIDGET_H
