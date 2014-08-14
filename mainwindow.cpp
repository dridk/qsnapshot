#include "mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QClipboard>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

    mPreview      = new PreviewWidget();
    mShotButton   = new QPushButton(QIcon(":icons/slr_camera.png"),tr("Take a new screenshot"));
    mSaveButton   = new QPushButton(QIcon(":icons/save_as.png"),tr("Save as ..."));
    mCopyButton   = new QPushButton(QIcon(":icons/copy.png"),tr("Copy"));
    mSendButton   = new QPushButton(QIcon(":icons/send_file-26.png"),tr("Send to .."));
    mAboutButton  = new QPushButton(QIcon(":icons/slr_camera.png"),tr("About"));
    mModeComboBox = new QComboBox();
    mDelaySpinBox = new QSpinBox();


    addSnapMode(new AreaSnapeShotWidget());
    addSnapMode(new FullSnapShotWidget());


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


    connect(mShotButton,SIGNAL(clicked()),this,SLOT(waitAndTakeScreen()));
    connect(mSaveButton,SIGNAL(clicked()),this,SLOT(saveAs()));
    connect(mCopyButton,SIGNAL(clicked()),this,SLOT(copy()));


}

MainWindow::~MainWindow()
{

    delete mPreview;
    delete mShotButton;
    delete mSaveButton;
    delete mCopyButton;
    delete mSendButton;
    delete mAboutButton;
    delete mModeComboBox;
    delete mDelaySpinBox;
}

void MainWindow::waitAndTakeScreen()
{

    QTimer::singleShot(mDelaySpinBox->value()*1000,this,SLOT(takeScreen()));
}

void MainWindow::takeScreen()
{


    int index = mModeComboBox->currentIndex();
    AbstractSnapshotWidget * snapWidget = mSnapWidgets.at(index);


    snapWidget->showFullScreen();
    snapWidget->takeScreen();


}

void MainWindow::saveAs()
{

    QString filename = QFileDialog::getSaveFileName(this,tr("Save Screenshot"),"", tr("Image (*.png)"));
    QFile file(filename);
    mPreview->originalPixmap().save(&file,"PNG");
    file.close();



}

void MainWindow::copy()
{

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setPixmap(mPreview->originalPixmap());
}

void MainWindow::addSnapMode(AbstractSnapshotWidget *widget)
{

    mSnapWidgets.append(widget);
    mModeComboBox->addItem(widget->objectName());
    connect(widget,SIGNAL(subscreenTaken()),this,SLOT(setPreview()));




}

void MainWindow::setPreview()
{

    AbstractSnapshotWidget * snapWidget = qobject_cast<AbstractSnapshotWidget*>(sender());
    mPreview->setOriginalPixmap(snapWidget->subscreen());
    mPreview->setFocus();


}
