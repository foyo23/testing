/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现导入拍摄界面和功能
 */
#include "impshootresultdlg.h"
#include "ui_impshootresultdlg.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QStandardPaths>

ImpShootResultDlg::ImpShootResultDlg(  DIALOG_FLAG_E flag, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::ImpShootResultDlg)
{
    ui->setupUi(this);    
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    this->setWindowFlags( flags );
    m_dlg_flag = flag;

#define BACK_BTN_WIDTH 80
#define BACK_BTN_HEIGHT 30
#define DESKTOP_BTN_WIDTH 70
#define DESKTOP_BTN_HEIGHT 65

    QGridLayout *pgLayout = new QGridLayout( this );
    QPushButton *pBackBtn = new QPushButton( tr("Back"), this );
    pBackBtn->setFixedSize( BACK_BTN_WIDTH, BACK_BTN_HEIGHT );
    QFont font = pBackBtn->font();
    font.setPointSize( 10 );
    pBackBtn->setFont( font );

    QPushButton *pDesktopBtn = new QPushButton( tr("Desktop"), this );
    pDesktopBtn->setFixedSize( DESKTOP_BTN_WIDTH, DESKTOP_BTN_HEIGHT );
    QPushButton *pMyDocBtn = new QPushButton( tr("My Document"), this );
    pMyDocBtn->setFixedSize( DESKTOP_BTN_WIDTH, DESKTOP_BTN_HEIGHT );
    QPushButton *pMyComputerBtn = new QPushButton( tr("My Computer"), this );
    pMyComputerBtn->setFixedSize( DESKTOP_BTN_WIDTH, DESKTOP_BTN_HEIGHT );
    mpListWid = new QListWidget( this );
    mpListWid->setFixedHeight( DESKTOP_BTN_HEIGHT*3 + 2*20 );
    QLabel *pFileNameLab = new QLabel( tr("File Name:"), this );
    mpFileNameEdit = new QLineEdit( this );
    QPushButton *pOkBtn = new QPushButton( tr("Ok"), this );
    pOkBtn->setDefault(true);
    QPushButton *pCancelBtn = new QPushButton( tr("Cancel"), this );

    int nRow = 0;
    pgLayout->addWidget( pBackBtn, nRow, 3 );
    nRow++;
    pgLayout->addWidget( pDesktopBtn, nRow, 0 );
    pgLayout->addWidget( mpListWid, nRow, 1, 3, 3 );
    nRow++;
    pgLayout->addWidget( pMyDocBtn, nRow, 0 );
    nRow++;
    pgLayout->addWidget( pMyComputerBtn, nRow, 0 );

    nRow++;
    pgLayout->addWidget( pFileNameLab, nRow, 1 );
    pgLayout->addWidget( mpFileNameEdit, nRow, 2 );
    pgLayout->addWidget( pOkBtn, nRow, 3 );
    nRow++;
    pgLayout->addWidget( pCancelBtn, nRow, 3 );

    /*connect( pBackBtn, SIGNAL(pressed()), this, SLOT(backBtnSlot()) );
    connect( pDesktopBtn, SIGNAL(pressed()), this, SLOT(desktopBtnSlot()) );
    connect( pMyDocBtn, SIGNAL(pressed()), this, SLOT(mydocBtnSlot()) );
    connect( pMyComputerBtn, SIGNAL(pressed()), this, SLOT(mycomputerBtnSlot()) );
    connect( pOkBtn, SIGNAL(pressed()), this, SLOT(okBtnSlot()) );
    connect( pCancelBtn, SIGNAL(pressed()), this, SLOT(cancelBtnSlot()) );*/
    if( m_dlg_flag == DIALOG_FLAG_IMPORT ) {
        this->setWindowTitle( tr("Select directory or files") );
        //mpFileNameEdit->setReadOnly( true );
    } else {
        this->setWindowTitle( tr("Select target files") );
    }
}

ImpShootResultDlg::~ImpShootResultDlg()
{
    delete ui;
}

void ImpShootResultDlg::loadListData(BTN_EVENT_E )
{
    /*QStandardPaths::DesktopLocation
    DESKBTN_CLICK,
    MYDOCBTN_CLICK,
    MYCOMPUTERBTN_CLICK,
    BACKBTN_CLICK
    */
}
