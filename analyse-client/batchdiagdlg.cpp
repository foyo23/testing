#include "batchdiagdlg.h"
#include "ui_batchdiagdlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <QSizePolicy>
#include <QLabel>

BatchDiagDlg::BatchDiagDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatchDiagDlg)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    this->setWindowFlags( flags );

    QVBoxLayout *pvLayout = new QVBoxLayout(this);
    mpDiagProgBar = new QProgressBar(this);
    //QSizePolicy policy = QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );//QSizePolicy::Maximum Fixed
    //mpDiagProgBar->setSizePolicy( policy );
    //mpDiagProgBar->setRange( 0, 100 );
    //mpDiagProgBar->setValue( 0 );
    mpDiagProgBar->setTextVisible( false );

    mpMsgListWid = new QListWidget(this);
    pvLayout->addWidget( mpDiagProgBar );
    pvLayout->addWidget( mpMsgListWid );

    QHBoxLayout *phLayout = new QHBoxLayout();
    mpFinishBtn = new QPushButton( tr("Finish"), this );
    QPushButton *pCancelBtn = new QPushButton( tr("Cancel"), this );
    QLabel *pLab = new QLabel(this);
    phLayout->addWidget( pLab, 1);
    phLayout->addWidget( mpFinishBtn, 0, Qt::AlignRight );
    phLayout->addWidget( pCancelBtn, 0, Qt::AlignRight );

    pvLayout->addLayout( phLayout );

    this->setLayout( pvLayout );
    this->setWindowTitle(tr("Diagnose"));
}

BatchDiagDlg::~BatchDiagDlg()
{
    delete ui;
}
