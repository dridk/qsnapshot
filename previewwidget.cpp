#include "previewwidget.h"
#include <QDrag>
#include <QTemporaryDir>
#include <QTemporaryFile>
#include <QFileInfo>
#include <QDebug>
#include <QStandardPaths>

PreviewWidget::PreviewWidget(QWidget *parent) :
    QLabel(parent)
{


    mDrag = new QDrag(this);
    mMimeData = new QMimeData;
    setAlignment(Qt::AlignCenter);
    setFocus();

}

PreviewWidget::~PreviewWidget()
{
    delete mDrag;
    delete mMimeData;
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

const QPixmap &PreviewWidget::originalPixmap() const
{
    return mOriginalPixmap;
}

void PreviewWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton){


        QString path = QStandardPaths::writableLocation(QStandardPaths::TempLocation);

        QFile file(path + QDir::separator()+ "screenshot.png");


        qDebug()<<mOriginalPixmap.save(&file,"PNG");

        qDebug()<<file.fileName();


        qDebug()<<QFile::exists(file.fileName());

        QList<QUrl> urls;
        urls.append(QUrl::fromLocalFile(file.fileName()));

        file.close();

        mMimeData->setUrls(urls);
        mDrag->setMimeData(mMimeData);
        mDrag->setPixmap(mOriginalPixmap);


        mDrag->exec();


    }





}

