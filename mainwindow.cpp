#include "mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

    mPreview      = new QLabel();
    mShotButton   = new QPushButton(tr("Take a new screenshot"));
    mSaveButton   = new QPushButton(tr("Save as ..."));
    mCopyButton   = new QPushButton(tr("Copy"));
    mSendButton   = new QPushButton(tr("Send to .."));
    mAboutButton  = new QPushButton(tr("About"));
    mModeComboBox = new QComboBox();
    mDelaySpinBox = new QSpinBox();
    mSnapWidget   = new SnapshotWidget();

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


    connect(mShotButton,SIGNAL(clicked()),
            this,SLOT(shot()));


}

MainWindow::~MainWindow()
{
}

void MainWindow::shot()
{


    mSnapWidget->showFullScreen();
    mSnapWidget->snapshot();


}
