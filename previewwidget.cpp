#include "previewwidget.h"
#include <QDrag>
#include <QMimeData>
#include <QTemporaryDir>
#include <QTemporaryFile>
#include <QFileInfo>
#include <QDebug>

PreviewWidget::PreviewWidget(QWidget *parent) :
    QLabel(parent)
{

    setAlignment(Qt::AlignCenter);
    setFocus();

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

void PreviewWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton){

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        QFile file("screenshot.png");
        QFileInfo info(file);

        qDebug()<<info.absoluteFilePath();

        qDebug()<<mOriginalPixmap.save(&file);
        file.close();
        QList<QUrl> urls;
        qDebug()<<info.absoluteFilePath();
        urls.append(QUrl::fromLocalFile(info.absoluteFilePath()));
        mimeData->setUrls(urls);
        drag->setMimeData(mimeData);
        drag->setPixmap(mOriginalPixmap);


        Qt::DropAction dropAction = drag->exec();

    }





}

