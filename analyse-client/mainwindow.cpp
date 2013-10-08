/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现主界面的配置和展示
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeySequence>
#include <QDebug>
#include <QMessageBox>
#include "devtreeview.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "filterview.h"
#include <QSplitter>
#include <QFont>
#include <QSplitterHandle>
#include <QStackedWidget>
#include <QToolButton>
//#include <QPixmap>
//#include <QBitmap>
#include "impshootresultdlg.h"
#include "exportsettingdlg.h"
#include "batchdiagdlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)//Dialog
{
    ui->setupUi(this);

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint;
    this->setWindowFlags( flags );

    createToolbar();    
    setWindowTitle(tr("analyse-api-client"));    
    QSplitter *phSplitter = new QSplitter( Qt::Horizontal, this );

    //Search edit, button, devtree
    QWidget* pWidget = new QWidget(this);
    QHBoxLayout *phLayout = new QHBoxLayout();    
    QLineEdit *psearchEdit = new QLineEdit();
    QPushButton *psearchBtn = new QPushButton( tr("Search") );
    psearchBtn->setFixedWidth( 45 );
    phLayout->addWidget( psearchEdit );
    phLayout->addWidget( psearchBtn );
    DevTreeView *pview= new DevTreeView(this);
    QVBoxLayout *pvLayout = new QVBoxLayout();
    pvLayout->addLayout( phLayout );
    pvLayout->addWidget( pview );
    pWidget->setLayout(pvLayout);
    pWidget->setMinimumWidth(380);

    mpStackWidget = new QStackedWidget();
    //Filter condition, filter result
    FilterView * pFilterView = new FilterView(this, false );
    FilterView * pFilterView2 = new FilterView(this, true );
    pFilterView2->setDevTypeVolComboData( pFilterView );
    mpStackWidget->addWidget( pFilterView );
    mpStackWidget->addWidget( pFilterView2  );

    phSplitter->setStyleSheet("QSplitter::handle { background-color: gray }");
    phSplitter->setHandleWidth(1);
    phSplitter->addWidget( pWidget );
    phSplitter->addWidget( mpStackWidget );
    phSplitter->setStretchFactor( 0, 0);
    phSplitter->setStretchFactor( 1, 1);

    QSplitter *vsplitter = new QSplitter( Qt::Vertical, this );
    mpIrImageView = new IrImageView(this);
    mpIrImageView->setFixedHeight( this->height()*2/5);

    vsplitter->setStyleSheet("QSplitter::handle { background-color: gray }");
    vsplitter->setHandleWidth(1);
    vsplitter->addWidget( phSplitter );
    vsplitter->addWidget( mpIrImageView );
    vsplitter->setStretchFactor( 0, 3);
    vsplitter->setStretchFactor( 1, 2);
    QSplitterHandle *handle = vsplitter->handle(1);
    handle->setDisabled( true );

    QSplitter *vsplitter2 = new QSplitter( Qt::Vertical, this );
    vsplitter2->setStyleSheet("QSplitter::handle { background-color: gray }");
    vsplitter2->setHandleWidth(2);
    vsplitter2->addWidget( mpToolBar );
    vsplitter2->addWidget( vsplitter );
    QVBoxLayout *pvLay = new QVBoxLayout();
    pvLay->addWidget( vsplitter2 );
    pvLay->setMargin( 0 );
    pvLay->setContentsMargins( 0, 0, 0, 0 );
    this->setLayout( pvLay );
    //this->

    //this->setCentralWidget( vsplitter );//pMainWidget
    //this->set
    this->setMinimumSize( 1050, 650 );
    mbRadioCheckFlag = true;

    connect(pFilterView, SIGNAL(tableSelectionChanged(QueryResultTable*, bool)), mpIrImageView, SLOT(tableSelectionChangedSlot(QueryResultTable*, bool)) );
    connect(pview, SIGNAL(treeItemSelectionChanged(QStringList)), pFilterView, SLOT(treeItemSelectionChangedSlot(QStringList)) );
    connect(pview, SIGNAL(treeItemSelectionChanged(QStringList)), pFilterView2, SLOT(treeItemSelectionChangedSlot(QStringList)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug() << "window width:" << event->size().width() << " height:" << event->size().height();
}*/

//Create the mpToolBar
void MainWindow::createToolbar()
{
#define BTN_WIDTH 90
#define BTN_HEIGHT 25
    //QPixmap *pPixMap = new QPixmap();
    //pPixMap->load( ":/res/toolbar_ana.bmp" );
    //QPixmap tmpPixmap = pPixMap->copy( BTN_WIDTH, 0, BTN_WIDTH, BTN_HEIGHT );
    //bool bRet = tmpPixmap.save("test.bmp");

    importShootResultAction = new QAction(this);//tr("Import Shoot Result"),
    importShootResultAction->setShortcut(Qt::CTRL + Qt::Key_R);

    exportAction = new QAction( this);//tr("Export"),
    exportAction->setShortcut(Qt::CTRL + Qt::Key_E);
    importAction = new QAction( this);//tr("Import"),
    importAction->setShortcut(Qt::CTRL + Qt::Key_I);
    batchDiagnoseAction = new QAction( this);//tr("Batch Diagnose"),
    batchDiagnoseAction->setShortcut(Qt::CTRL + Qt::Key_B);
    helpAction = new QAction( this);//tr("Help"),
    helpAction->setShortcut(QKeySequence::HelpContents);
    aboutAction = new QAction(this);//tr("About"),
    aboutAction->setShortcut(Qt::CTRL + Qt::Key_A);

    mpToolBar = new QToolBar( this );
    //mpToolBar->setu

    //QFont toolBarFont("Times", 10);
    //mpToolBar->setFont( toolBarFont );
    /*mpToolBar->addAction( importShootResultAction );
    mpToolBar->addAction( exportAction );
    mpToolBar->addAction( importAction );
    mpToolBar->addAction( batchDiagnoseAction );
    mpToolBar->addAction( helpAction );
    mpToolBar->addAction( aboutAction );*/

    QToolButton *mpImportShootResultBtn = new QToolButton( );
    //mpImportShootResultBtn->clearMask();
    //mpImportShootResultBtn->setBackgroundRole( QPalette::Base );
    mpImportShootResultBtn->setFixedSize( BTN_WIDTH, BTN_HEIGHT );
    mpImportShootResultBtn->setStyleSheet("background:url(:/res/importShootResult.png)");
    //mpImportShootResultBtn->setMask( tmpPixmap.createHeuristicMask() );
    //mpImportShootResultBtn->setToolButtonStyle( Qt::ToolButtonIconOnly );
    //mpImportShootResultBtn->setIcon( tmpPixmap );
    //mpImportShootResultBtn->setIconSize( QSize(BTN_WIDTH, BTN_HEIGHT) );
    //mpImportShootResultBtn->setAutoFillBackground( true );
    //background:url(:/res/ImportShootResult.bmp)
    //QSizePolicy policy = QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );//QSizePolicy::Maximum Fixed
    //mpImportShootResultBtn->setSizePolicy( policy );
    mpImportShootResultBtn->setDefaultAction( importShootResultAction );
    mpToolBar->addWidget( mpImportShootResultBtn );

    QToolButton *mpExportBtn = new QToolButton( );
    mpExportBtn->setFixedSize( BTN_WIDTH, BTN_HEIGHT );
    mpExportBtn->setStyleSheet("background:url(:/res/export.png)");
    mpExportBtn->setDefaultAction( exportAction );
    mpToolBar->addWidget( mpExportBtn );

    QToolButton *mpImportBtn = new QToolButton( );
    mpImportBtn->setFixedSize( BTN_WIDTH, BTN_HEIGHT );
    mpImportBtn->setStyleSheet("background:url(:/res/import.png)");
    mpImportBtn->setDefaultAction( importAction );
    mpToolBar->addWidget( mpImportBtn );

    QToolButton *mpBatchDiagnoseBtn = new QToolButton( );
    mpBatchDiagnoseBtn->setFixedSize( BTN_WIDTH, BTN_HEIGHT );
    mpBatchDiagnoseBtn->setStyleSheet("background:url(:/res/batchDiagnose.png)");
    mpBatchDiagnoseBtn->setDefaultAction( batchDiagnoseAction );
    mpToolBar->addWidget( mpBatchDiagnoseBtn );

    QToolButton *mpHelpBtn = new QToolButton( );
    mpHelpBtn->setFixedSize( BTN_WIDTH, BTN_HEIGHT );
    mpHelpBtn->setStyleSheet("background:url(:/res/help.png)");
    mpHelpBtn->setDefaultAction( helpAction );
    mpToolBar->addWidget( mpHelpBtn );

    QToolButton *mpAboutBtn = new QToolButton( );
    mpAboutBtn->setFixedSize( BTN_WIDTH, BTN_HEIGHT );
    mpAboutBtn->setStyleSheet("background:url(:/res/about.png)");
    mpAboutBtn->setDefaultAction( aboutAction );
    mpToolBar->addWidget( mpAboutBtn );

    connect(importShootResultAction, SIGNAL(triggered()), this, SLOT(importShootResultSlot()));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportSlot()));
    connect(importAction, SIGNAL(triggered()), this, SLOT(importSlot()));
    connect(batchDiagnoseAction, SIGNAL(triggered()), this, SLOT(batchDiagnoseSlot()));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(helpSlot()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutSlot()));
}

//Process the import shoot result click event
void MainWindow::importShootResultSlot()
{
    qDebug()<<"importShootResultSlot.";
    ImpShootResultDlg *dlg = new ImpShootResultDlg( DIALOG_FLAG_IMPORT_SHOOT_RESULT );
    dlg->exec();
}

void MainWindow::exportSlot()
{
    qDebug()<<"exportSlot.";
    ExportSettingDlg dlg;
    dlg.exec();
}

void MainWindow::importSlot()
{
    qDebug()<<"importSlot.";
    ImpShootResultDlg *dlg = new ImpShootResultDlg( DIALOG_FLAG_IMPORT );
    dlg->exec();
}

void MainWindow::batchDiagnoseSlot()
{
    qDebug()<<"batchDiagnoseSlot.";
    BatchDiagDlg dlg;
    dlg.exec();
}

void MainWindow::helpSlot()
{
    qDebug()<<"helpSlot.";
    QMessageBox::information( 0, tr("Help"),
          tr("1. Import shoot result function: Select file or directory to import to the database;\n"
          "2. Export function: Export the selected substations data to other database;\n"
                      "3. Import function: Import the backup data;\n"
                      "4. Help function: Show help info;\n"
                      "5. About function: Show about info.\n"));
}

void MainWindow::aboutSlot()
{
    qDebug()<<"aboutSlot.";
    QMessageBox::about( 0, tr("About analyse"),
          tr("Version: 0.1\n"
          "Copyrighter: HangZhou Meisheng co. ltd\n"
                      "Warning: The software including datas and their derivatives including but not limited to its products or service, "
                      "which are created or developed on the basis of Meisheng copyright. The intellectual property is protected by Copyright Laws of the People's Republic of China.\n"
                      "Without prior written consent by Meisheng, any reproduction, modification, storage in a retrieval system or retransmission, "
                      "or tied sale with other products in any form or by any means, regarding any part of the above products, service, information and materials, "
                      "electronic, mechanical or otherwise, is illegal and strictly prohibited."));
}

//Process the Ir. radio click event
void MainWindow::irRadClick(bool bCheck)
{
    //qDebug() << "MainWindow irRadClick:" << bCheck << " mbRadioCheckFlag=" << (mbRadioCheckFlag?"true":"false");
    if( bCheck ) {
        if( mbRadioCheckFlag )  {
            return ;
        }
        mpStackWidget->setCurrentIndex( 0 );
        //mpgLayout->setRowStretch( 1, 2 );
        mpIrImageView->setHidden( false );
        mbRadioCheckFlag = true;
    } else {
        if( !mbRadioCheckFlag )  {
            return ;
        }
        mpStackWidget->setCurrentIndex( 1 );
        //mpgLayout->setRowStretch( 1, 0 );
        mpIrImageView->setHidden( true );
        mbRadioCheckFlag = false;
    }
    FilterView *mpfview = (FilterView *)mpStackWidget->currentWidget();
    mpfview->setIrRadioChecked( bCheck );
}




