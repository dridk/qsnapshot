#ifndef ABSTRACTSNAPSHOTWIDGET_H
#define ABSTRACTSNAPSHOTWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QPainter>

class AbstractSnapshotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractSnapshotWidget(QWidget *parent = 0);
    virtual QPixmap screenshot() const = 0;
    const QPixmap &screen() const;

public slots:
    virtual void take();

protected:
    void mouseDoubleClickEvent(QMouseEvent*);


protected slots:
    void paintEvent(QPaintEvent * event);



signals:
    void taken();


private:
    QPixmap mScreen;


};

#endif // ABSTRACTSNAPSHOTWIDGET_H
