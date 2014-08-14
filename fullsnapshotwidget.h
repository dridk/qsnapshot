#ifndef FULLSNAPSHOTWIDGET_H
#define FULLSNAPSHOTWIDGET_H

#include "abstractsnapshotwidget.h"

class FullSnapShotWidget : public AbstractSnapshotWidget
{
    Q_OBJECT
public:
    explicit FullSnapShotWidget(QWidget *parent = 0);

    virtual QPixmap subscreen() const;
signals:

public slots:

};

#endif // FULLSNAPSHOTWIDGET_H
