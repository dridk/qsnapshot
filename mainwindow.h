#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "snapshotwidget.h"
#include "previewwidget.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void shot();

protected slots:
    void setPixmap();

private:
    PreviewWidget * mPreview;
    QPushButton * mShotButton;
    QPushButton * mSaveButton;
    QPushButton * mCopyButton;
    QPushButton * mSendButton;
    QPushButton * mAboutButton;
    QComboBox * mModeComboBox;
    QSpinBox * mDelaySpinBox;
    SnapshotWidget * mSnapWidget;


};

#endif // MAINWINDOW_H
