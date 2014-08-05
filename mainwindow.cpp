#include "mainwindow.h"
#include <QDebug>

#include <QtX11Extras/QX11Info>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

    mPreview      = new PreviewWidget();
    mShotButton   = new QPushButton(tr("Take a new screenshot"));
    mSaveButton   = new QPushButton(tr("Save as ..."));
    mCopyButton   = new QPushButton(tr("Copy"));
    mSendButton   = new QPushButton(tr("Send to .."));
    mAboutButton  = new QPushButton(tr("About"));
    mModeComboBox = new QComboBox();
    mDelaySpinBox = new QSpinBox();


    addSnapMode(new AreaSnapeShotWidget());
    addSnapMode(new FullSnapShotWidget());
    addSnapMode(new WinSnapshotWidget());


    QFormLayout * formLayout = new QFormLayout();
    QHBoxLayout * barLayout  = new QHBoxLayout();
    QVBoxLayout * mainLayout = new QVBoxLayout();

    mPreview->setFrameShape(QFrame::Box	);
    mPreview->setFrameShadow(QFrame::Sunken);
    mModeComboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    mDelaySpinBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    formLayout->addRow(tr("Capture mode:"), mModeComboBox);
    formLayout->addRow(tr("Delay before capture"), mDelaySpinBox);
    formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    formLayout->setFormAlignment(Qt::AlignHCenter);
    mShotButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);
    mPreview->setMinimumSize(400,300);

    barLayout->addWidget(mAboutButton);
    barLayout->addStretch();
    barLayout->addWidget(mSendButton);
    barLayout->addWidget(mCopyButton);
    barLayout->addWidget(mSaveButton);

    mainLayout->addWidget(mPreview);
    mainLayout->addWidget(mShotButton,0,Qt::AlignHCenter);
    mainLayout->addStretch();
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(barLayout);


    setLayout(mainLayout);


    connect(mShotButton,SIGNAL(clicked()),this,SLOT(takeScreenshot()));




}

MainWindow::~MainWindow()
{
}

void MainWindow::takeScreenshot()
{


    QDesktopWidget * desktop = new QDesktopWidget;

    Window root;
    Window parent;
    Window *children;
    Window *child;
    Window current = desktop->winId();
    unsigned int i;
    unsigned int nchildren;


    XQueryTree(QX11Info::display(),current,&root,&parent,&children,&nchildren);


    qDebug()<<children[10];




    int index = mModeComboBox->currentIndex();
    AbstractSnapshotWidget * snapWidget = mSnapWidgets.at(index);

    //    snapWidget->showFullScreen();

    snapWidget->take();

 mPreview->setOriginalPixmap(qGuiApp->primaryScreen()->grabWindow(WId(children[30])));


}

void MainWindow::addSnapMode(AbstractSnapshotWidget *widget)
{

    mSnapWidgets.append(widget);
    mModeComboBox->addItem(widget->objectName());
    connect(widget,SIGNAL(taken()),this,SLOT(setPreview()));




}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Return)
        takeScreenshot();


}

void MainWindow::setPreview()
{

    AbstractSnapshotWidget * snapWidget = qobject_cast<AbstractSnapshotWidget*>(sender());


    mPreview->setOriginalPixmap(snapWidget->screenshot());
    mPreview->setFocus();


}

void MainWindow::test(QWindow *w)
{


    Window ** list;
    unsigned int total =0;
    XQueryTree(QX11Info::display(),0,NULL,NULL,list,&total);










}
