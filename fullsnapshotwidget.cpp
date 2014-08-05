#include "fullsnapshotwidget.h"

FullSnapShotWidget::FullSnapShotWidget(QWidget *parent) :
    AbstractSnapshotWidget(parent)
{


setObjectName("Fullscreen");



}

QPixmap FullSnapShotWidget::screenshot() const
{


    return screen();

}
