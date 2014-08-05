#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "areasnapshotwidget.h"
#include "fullsnapshotwidget.h"
#include "previewwidget.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void takeScreenshot();


protected :
    void addSnapMode(AbstractSnapshotWidget * widget);

protected slots:
    void setPreview();

private:
    PreviewWidget * mPreview;
    QPushButton * mShotButton;
    QPushButton * mSaveButton;
    QPushButton * mCopyButton;
    QPushButton * mSendButton;
    QPushButton * mAboutButton;
    QComboBox * mModeComboBox;
    QSpinBox * mDelaySpinBox;

    QList<AbstractSnapshotWidget*> mSnapWidgets;


};

#endif // MAINWINDOW_H
