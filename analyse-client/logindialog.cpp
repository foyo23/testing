/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现登录界面和功能
 */
#include "logindialog.h"
#include "ui_logindialog.h"
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>

//#include "zlib/zlib.h"

LoginDialog::LoginDialog(QWidget *parent, CurllibPort *pCurl) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    this->setWindowFlags( flags );
#define CTL_HEIGHT 30
#define BTN_WIDTH 70
    QGridLayout *pgLayout = new QGridLayout( this );
    QLabel *pEmailLab = new QLabel( tr("Email:"), this );   
    mpUserEmailEdit = new QLineEdit( this );
    mpUserEmailEdit->setFixedHeight( CTL_HEIGHT );
    QLabel *pPassLab = new QLabel( tr("Password:"), this );
    mpPasswordEdit = new QLineEdit( this );
    mpPasswordEdit->setFixedHeight( CTL_HEIGHT );
    mpPasswordEdit->setEchoMode( QLineEdit::Password );
    //mpAutoLoginCheckBox = new QCheckBox( tr("Next Auto Login") );
    //mpAutoLoginCheckBox->setFixedHeight( CTL_HEIGHT );
    mpLoginBtn = new QPushButton( tr("Login"), this );
    mpLoginBtn->setFixedSize( BTN_WIDTH, CTL_HEIGHT );
    mpLoginBtn->setDefault( true );
    QPushButton *pCancelBtn = new QPushButton( tr("Cancel"), this );
    pCancelBtn->setFixedSize( BTN_WIDTH, CTL_HEIGHT );
    QLabel *pTmpLab = new QLabel( "", this );
    pTmpLab->setFixedHeight( CTL_HEIGHT );

    int nRow = 0;
    pgLayout->addWidget( pEmailLab, nRow, 0 );
    pgLayout->addWidget( mpUserEmailEdit, nRow, 1 );
    //pgLayout->setRowStretch( nRow, 1 );
    nRow++;
    pgLayout->addWidget( pPassLab, nRow, 0 );
    pgLayout->addWidget( mpPasswordEdit, nRow, 1 );

    nRow++;
    pgLayout->addWidget( pTmpLab, nRow, 1 );

    nRow++;
    QHBoxLayout *phLayout = new QHBoxLayout( );
    phLayout->addWidget( mpLoginBtn );
    phLayout->addSpacing( 100 );
    phLayout->addWidget( pCancelBtn );
    pgLayout->addLayout( phLayout, nRow, 1, 1, 1, Qt::AlignLeft );

    this->setLayout( pgLayout );
    setWindowTitle(tr("analyse-api-client"));

    mpUserEmailEdit->setText( "linq.lin@qq.com" );
    mpPasswordEdit->setText( "123456" );
    mpCurl = pCurl;
    connect( mpLoginBtn, SIGNAL(clicked()), this, SLOT(loginBtnSlot()) );
    connect( pCancelBtn, SIGNAL(clicked()), this, SLOT(reject()) );

    /*gzFile file;
    file = gzdopen("e:/zjw/test.zip", "rb");
    if (file == NULL) error("can't gzdopen stdin");
    gz_uncompress(file, stdout);*/
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::loginBtnSlot()
{
    qDebug()<<"loginSlot()";
    accept();
    return ;
    if( mpCurl ) {
        bool bLogin = mpCurl->login( mpUserEmailEdit->text(), mpPasswordEdit->text(), 0 );//mpAutoLoginCheckBox->isChecked()?1:0
        qDebug() << "Login sussess:" << bLogin;
        if( bLogin ) {
            /*bool bRet = mpCurl->sendRequest( "/api/users", REQUEST_METHOD_GET, "" );
            if( bRet ) {
                MemoryStruct mem = mpCurl->getResponseContent();
                mpCurl->freeResponseContent( mem );
            }*/
            accept();
        } else {
            QMessageBox::warning(0, tr("Login fail"),
                tr("Maybe email or password is error."));
        }
    }
}



