#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QLabel>
#include <QResizeEvent>
#include <QMouseEvent>

class PreviewWidget : public QLabel
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *);
    void setOriginalPixmap(const QPixmap& pix);

    void mousePressEvent(QMouseEvent * event);

signals:

public slots:


private:
    QPixmap mOriginalPixmap;
};

#endif // PREVIEWWIDGET_H
