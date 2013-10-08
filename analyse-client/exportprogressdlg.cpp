#include "exportprogressdlg.h"
#include "ui_exportprogressdlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <QSizePolicy>

ExportProgressDlg::ExportProgressDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportProgressDlg)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    this->setWindowFlags( flags );

    QVBoxLayout *pvLayout = new QVBoxLayout(this);
    //QSizePolicy policy = QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );//QSizePolicy::Maximum Fixed
    mpTabProgBar = new QProgressBar(this);
    mpTabProgBar->setTextVisible( false );
    //mpTabProgBar->setSizePolicy( policy );
    mpZipProgBar = new QProgressBar(this);
    mpZipProgBar->setTextVisible( false );
    //mpZipProgBar->setSizePolicy( policy );
    mpMsgListWid = new QListWidget(this);
    mpMsgListWid->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    mpMsgListWid->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    pvLayout->addWidget( mpTabProgBar );
    pvLayout->addWidget( mpZipProgBar );
    pvLayout->addWidget( mpMsgListWid );

    QHBoxLayout *phLayout = new QHBoxLayout();
    mpFinishBtn = new QPushButton( tr("Finish"), this );
    mpCancelBtn = new QPushButton( tr("Cancel"), this );
    phLayout->addSpacing( 110 );
    phLayout->addWidget( mpFinishBtn );
    phLayout->addSpacing( 80 );
    phLayout->addWidget( mpCancelBtn );
    phLayout->addSpacing( 110 );
    pvLayout->addLayout( phLayout );

    this->setLayout( pvLayout );
    this->setWindowTitle(tr("Export substation datas"));
}

ExportProgressDlg::~ExportProgressDlg()
{
    delete ui;
}
