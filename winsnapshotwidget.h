#ifndef WINSNAPSHOTWIDGET_H
#define WINSNAPSHOTWIDGET_H
#include "abstractsnapshotwidget.h"

class WinSnapshotWidget : public AbstractSnapshotWidget
{
    Q_OBJECT
public:
    explicit WinSnapshotWidget(QWidget *parent = 0);
      virtual QPixmap screenshot() const;

protected:
virtual void take();

private:
    QPixmap mPix;

};

#endif // WINSNAPSHOTWIDGET_H
