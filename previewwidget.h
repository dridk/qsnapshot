#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QLabel>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

class PreviewWidget : public QLabel
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = 0);
    ~PreviewWidget();
    void resizeEvent(QResizeEvent *);
    void setOriginalPixmap(const QPixmap& pix);
    const QPixmap& originalPixmap() const;

    void mousePressEvent(QMouseEvent * event);

signals:

public slots:


private:
    QPixmap mOriginalPixmap;
    QDrag *mDrag;
    QMimeData * mMimeData;
};

#endif // PREVIEWWIDGET_H
