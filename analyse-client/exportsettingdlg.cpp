#include "exportsettingdlg.h"
#include "ui_exportsettingdlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSizePolicy>
#include "exportprogressdlg.h"

ExportSettingDlg::ExportSettingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportSettingDlg)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    this->setWindowFlags( flags );

#define BTN_SPACING 70
    QVBoxLayout *pvLayout = new QVBoxLayout( this );

    QGroupBox *pFilterBox = new QGroupBox( tr("Filter condition"), this );
    mpFilterDataCheck = new QCheckBox( tr("Only export filter datas"), this );
    mpFilterDataLab = new QLabel(this);
    mpFilterDataLab->setFixedHeight( 80 );
    QSizePolicy policy = QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );//QSizePolicy::Maximum Fixed
    mpFilterDataLab->setSizePolicy( policy );
    mpFilterDataLab->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mpFilterDataLab->setScaledContents( true );
    QVBoxLayout *pvLayout2 = new QVBoxLayout();
    pvLayout2->addWidget( mpFilterDataCheck );
    pvLayout2->addWidget( mpFilterDataLab );
    pFilterBox->setLayout( pvLayout2 );

    QGroupBox *pSubsBox = new QGroupBox( tr("Please select substations"), this );
    mpListWid = new QListWidget( this );
    QPushButton *pSelectAllBtn = new QPushButton( tr("Select All"), this );
    QPushButton *pSelectNoneBtn = new QPushButton( tr("Select None"), this );
    QHBoxLayout *phLayout = new QHBoxLayout();
    phLayout->addSpacing( BTN_SPACING );
    phLayout->addWidget( pSelectAllBtn );
    phLayout->addSpacing( BTN_SPACING );
    phLayout->addWidget( pSelectNoneBtn );
    phLayout->addSpacing( BTN_SPACING );
    QVBoxLayout *pvLayout3 = new QVBoxLayout();
    pvLayout3->addWidget( mpListWid );
    pvLayout3->addLayout( phLayout );
    pSubsBox->setLayout( pvLayout3 );

    QGroupBox *pExportContBox = new QGroupBox( tr("Export Content"), this );
    mpBaseCheck = new QCheckBox( tr("Base resource"), this );
    mpRuleCheck = new QCheckBox( tr("Diagnose rule, base image, parse unit"), this );
    mpRecCheck = new QCheckBox( tr("Detect records"), this );
    mpImgCheck = new QCheckBox( tr("Image(Need much time)"), this );
    QVBoxLayout *pvLayout4 = new QVBoxLayout();
    pvLayout4->addWidget( mpBaseCheck );
    pvLayout4->addWidget( mpRuleCheck );
    pvLayout4->addWidget( mpRecCheck );
    pvLayout4->addWidget( mpImgCheck );
    pExportContBox->setLayout( pvLayout4 );

    pvLayout->addWidget( pFilterBox );
    pvLayout->addWidget( pSubsBox );
    pvLayout->addWidget( pExportContBox );

    QPushButton *pOkBtn = new QPushButton( tr("Ok"), this );
    pOkBtn->setDefault( true );
    QPushButton *pCancelBtn = new QPushButton( tr("Cancel"), this );
    QHBoxLayout *phLayout2 = new QHBoxLayout();
    phLayout2->addSpacing( BTN_SPACING );
    phLayout2->addWidget( pOkBtn );
    phLayout2->addSpacing( BTN_SPACING );
    phLayout2->addWidget( pCancelBtn );
    phLayout2->addSpacing( BTN_SPACING );
    pvLayout->addLayout( phLayout2 );

    this->setLayout( pvLayout );
    this->setWindowTitle(tr("Export substation datas"));
    connect( pOkBtn, SIGNAL(clicked()), this, SLOT(okBtnSlot()) );
}

ExportSettingDlg::~ExportSettingDlg()
{
    delete ui;
}

void ExportSettingDlg::okBtnSlot()
{
    this->hide();
    ExportProgressDlg dlg;
    int ret = dlg.exec();
    done(ret);
}
