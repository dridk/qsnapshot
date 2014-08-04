#ifndef SNAPSHOTWIDGET_H
#define SNAPSHOTWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

class SnapshotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SnapshotWidget(QWidget *parent = 0);

public slots:
    void snapshot();

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

    void drawAreaBox(QPainter& painter);
    QRect cornerToRect(const QPoint& p, int size=10);


private:
    QPixmap mPixmap;
    QRect mArea;
    QString mMode;
    QPoint mDiff;


};

#endif // SNAPSHOTWIDGET_H
