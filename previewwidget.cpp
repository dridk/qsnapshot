#include "previewwidget.h"

PreviewWidget::PreviewWidget(QWidget *parent) :
    QLabel(parent)
{

    setAlignment(Qt::AlignCenter);
}

void PreviewWidget::resizeEvent(QResizeEvent * event)
{

    if (mOriginalPixmap.isNull())
        return;

    QPixmap test = mOriginalPixmap.scaled(size(), Qt::KeepAspectRatio);

    setPixmap(test);




}

void PreviewWidget::setOriginalPixmap(const QPixmap &pix)
{

   mOriginalPixmap = pix;
   QPixmap test = mOriginalPixmap.scaled(size(), Qt::KeepAspectRatio,Qt::SmoothTransformation);

   setPixmap(test);


//void PreviewWidget::setPixmap(const QPixmap &pix)
//{

//    QLabel::setPixmap(pix.scaledToHeight(height()));


}
