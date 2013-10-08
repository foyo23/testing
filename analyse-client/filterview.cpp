/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现查询条件、查询结果表展示
 */
#include "filterview.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QDebug>
#include <QTableWidgetItem>
#include "deflabel.h"

FilterView::FilterView(QWidget *parent, bool bDevDetail):QWidget(parent)
{
#define SPACE_SIZE 20
#define THIRDLINE_SPACE_WIDTH 200
#define SCROLL_TABLE_BTN_WIDTH 30
#define SCROLL_TABLE_EDT_HEIGHT 25
#define SCROLL_TABLE_EDT_WIDTH 60
#define DATE_SHOWALLBTN_HEIGHT 28
#define DATE_SHOWALLBTN_SIZE 10
    QGroupBox *pGroup = new QGroupBox;
    QStringList pLabTitleList;
    //pGroup->setStyleSheet(" border: 3px solid;");
    //First line
    QHBoxLayout *phLayout = new QHBoxLayout();
    QLabel *pdevtypeLab = new QLabel( tr("Dev type:") );
    pdevtypeLab->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    mpDevTypeCom = new QComboBox();
    QLabel *pdevvolLab = new QLabel( tr("Dev vol:") );
    pdevvolLab->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    mpDevRegVolCom = new QComboBox();
    phLayout->addWidget( pdevtypeLab );
    phLayout->addWidget( mpDevTypeCom, 2 );
    phLayout->addSpacing( SPACE_SIZE );
    phLayout->addWidget( pdevvolLab );
    phLayout->addWidget( mpDevRegVolCom, 2 );
    phLayout->addSpacing( SPACE_SIZE );

    if( bDevDetail ) {
        QLabel *pLab = new QLabel();
        phLayout->addWidget( pLab, 8 );
    } else {
        QCheckBox *pdateCheck = new QCheckBox( tr("Date:") );
        pdateCheck->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
        QDateEdit *pstartDate = new QDateEdit( QDate::currentDate() );
        pstartDate->setFixedHeight( DATE_SHOWALLBTN_HEIGHT );
        QFont font = pstartDate->font();
        font.setPointSize( DATE_SHOWALLBTN_SIZE );

        QLabel *ptoLab = new QLabel( tr("To") );
        ptoLab->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
        QDateEdit *pendDate = new QDateEdit( QDate::currentDate() );
        pendDate->setFixedHeight( DATE_SHOWALLBTN_HEIGHT );
        pendDate->setFont( font );

        phLayout->addWidget( pdateCheck );
        phLayout->addWidget( pstartDate, 3 );
        phLayout->addWidget( ptoLab );
        phLayout->addWidget( pendDate, 3 );
        phLayout->addSpacing( SPACE_SIZE );
    }

    QPushButton *pshowallBtn = new QPushButton(tr("Show all"));
    pshowallBtn->setFixedHeight( DATE_SHOWALLBTN_HEIGHT );
    QFont font = pshowallBtn->font();
    font.setPointSize( DATE_SHOWALLBTN_SIZE );
    pshowallBtn->setFont( font );

    pshowallBtn->setToolTip( tr("Show all record") );
    phLayout->addWidget( pshowallBtn, 2 );

    //Second line
    QVBoxLayout *pvLayout = new QVBoxLayout();
    pvLayout->addLayout( phLayout );
    if( bDevDetail ) {
        QLabel *pLab = new QLabel();
        pvLayout->addWidget( pLab );
        mpTotalLab = 0;
    } else {
        QHBoxLayout *phLayout2 = new QHBoxLayout();
        pLabTitleList << tr("Urgent defect") << tr("Serious defect") << tr("Commonly defect") << tr("Attention") << tr("Normal") << tr("Unknown") << tr("Total:");
        for( int i=0; i<pLabTitleList.size(); i++ ) {
            if( i <= DEF_LEV_NORMAL ) {
                DefLabel *pDefLab = new DefLabel( (E_DEF_LEVEL)(DEF_LEV_URGENT+i), this );
                phLayout2->addWidget( pDefLab, 0 );
            }
            QLabel *ptitleLab = new QLabel( pLabTitleList.at(i) );
            ptitleLab->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
            phLayout2->addWidget( ptitleLab, 0 );
            if( i < pLabTitleList.size()-1 ) {
                mpCheckBox[i] = new QCheckBox( "(0)" );
                phLayout2->addWidget( mpCheckBox[i], 0, Qt::AlignLeft );
            } else {
                mpTotalLab = new QLabel( "(0)" );
                phLayout2->addWidget( mpTotalLab, 0, Qt::AlignLeft );
            }
        }

        pvLayout->addLayout( phLayout2 );
    }
    pGroup->setLayout( pvLayout );

    //Third line
    QHBoxLayout *phLayout3 = new QHBoxLayout();
    mpIrRadionBtn = new QRadioButton( tr("Ir. image") );
    mpIrRadionBtn->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    mpDevDetailRadBtn = new QRadioButton( tr("Dev. detail") );
    mpDevDetailRadBtn->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    QButtonGroup *pBtnGrp = new QButtonGroup();
    mpIrRadionBtn->setChecked( true );
    pBtnGrp->addButton( mpIrRadionBtn );
    pBtnGrp->addButton( mpDevDetailRadBtn );
    pBtnGrp->setExclusive( true );    
    phLayout3->addWidget( mpIrRadionBtn, 0, Qt::AlignLeft );
    phLayout3->addWidget( mpDevDetailRadBtn, 0, Qt::AlignLeft );
    //phLayout3->addSpacing( THIRDLINE_SPACE_WIDTH );
    QLabel *pspaceLab = new QLabel( );
    phLayout3->addWidget( pspaceLab, 1, Qt::AlignLeft );
    //phLayout3->setContentsMargins( 0, 0, 0, 0 );
    //phLayout3->setMargin( 0 );

    QHBoxLayout *phLayout4 = new QHBoxLayout();
    pLabTitleList.clear();
    pLabTitleList << "|<<" << "<" << "0/0" << ">" << ">>|";
    QStringList sTipList;
    sTipList << tr("Turn to the first page") << tr("Turn to the previous page") << "" << tr("Turn to the next page") << tr("Turn to the last page");
    for( int i=0; i<pLabTitleList.size(); i++ ) {
        if( i == 2 ) {
            mpCountEdit = new QLineEdit( pLabTitleList.at(i) );
            mpCountEdit->setFixedSize( SCROLL_TABLE_EDT_WIDTH, SCROLL_TABLE_EDT_HEIGHT );
            mpCountEdit->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
            phLayout4->addWidget( mpCountEdit, 0, Qt::AlignRight );
            //mpCountEdit->setToolTip( sTipList.at(i) );
        } else {
            QPushButton *pPageBtn = new QPushButton( pLabTitleList.at(i) );
            pPageBtn->setFixedSize( SCROLL_TABLE_BTN_WIDTH, SCROLL_TABLE_EDT_HEIGHT );
            pPageBtn->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
            phLayout4->addWidget( pPageBtn, 0, Qt::AlignRight );
            pPageBtn->setToolTip( sTipList.at(i) );
        }
    }

    /*QWidget *pTmpWdiget = new QWidget();
    pTmpWdiget->setLayout( phLayout4 );
    pTmpWdiget->setFixedWidth( SCROLL_TABLE_EDT_WIDTH+SCROLL_TABLE_BTN_WIDTH*4+10 );
    phLayout3->addWidget( pTmpWdiget );*/
    phLayout3->addLayout( phLayout4 );

    QVBoxLayout *pvLay = new QVBoxLayout();
    pvLay->addWidget( pGroup );
    pvLay->addLayout( phLayout3 );

    //Show table    
    mpTable = new QueryResultTable(this, bDevDetail );
    pvLay->addWidget( mpTable );
    mpCountEdit->setText( "1/1" );
    mpCountEdit->setAlignment( Qt::AlignCenter );

    //Last line
    if( bDevDetail ) {
        QLabel *pLab = new QLabel();
        pvLay->addWidget( pLab );
    } else {
        QHBoxLayout *phLayout4 = new QHBoxLayout();
        QGroupBox *pContrastGroup = new QGroupBox( tr("Contrast") );
        mpPhaseRadBtn = new QRadioButton( tr("Phase Contrast") );
        QRadioButton *pHistoryRad = new QRadioButton( tr("History Contrase") );
        mpPhaseRadBtn->setChecked( true );
        QButtonGroup *pConstrastBtnGrp = new QButtonGroup();
        pConstrastBtnGrp->addButton( mpPhaseRadBtn );
        pConstrastBtnGrp->addButton( pHistoryRad );
        pConstrastBtnGrp->setExclusive( true );
        QHBoxLayout *phTmpLayout = new QHBoxLayout();
        phTmpLayout->addWidget( mpPhaseRadBtn );
        phTmpLayout->addWidget( pHistoryRad );
        phTmpLayout->addSpacing( SPACE_SIZE );
        pContrastGroup->setLayout( phTmpLayout );
        pContrastGroup->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

        phLayout4->addWidget( pContrastGroup, 0, Qt::AlignLeft );
        mpdevnameLab = new QLabel( tr("Image Info Region") );
        phLayout4->addWidget( mpdevnameLab, 1, Qt::AlignCenter );
        pLabTitleList.clear();
        pLabTitleList << "<<" << ">>";
        sTipList.clear();
        sTipList << tr("Turn to the previous history record") << tr("Turn to the next history record");
        for( int i=0; i<pLabTitleList.size(); i++ ) {
            QPushButton *pContrastPageBtn = new QPushButton( pLabTitleList.at(i) );
            pContrastPageBtn->setFixedWidth( SCROLL_TABLE_BTN_WIDTH );
            pContrastPageBtn->setToolTip( sTipList.at(i) );
            phLayout4->addWidget( pContrastPageBtn, 0, Qt::AlignRight );
        }
        pvLay->addLayout( phLayout4 );

        connect(mpPhaseRadBtn, SIGNAL(toggled(bool)), this, SLOT(phaseRadClick(bool)));
    }

    this->setLayout( pvLay );
    connect(mpIrRadionBtn, SIGNAL(toggled(bool)), this->parent(), SLOT(irRadClick(bool)));
    if( !bDevDetail ) {
        connect(mpTable, SIGNAL(itemSelectionChanged()), this, SLOT(tableSelectionChanged()));
        setDefCount();
        setDevTypeVolComboData( this );
    }
    connect(this, SIGNAL(treeItemSelectionChanged(QStringList)), mpTable, SLOT(treeItemSelectionChangedSlot(QStringList)) );
}

//Set Defect records number
void FilterView::setDefCount()
{
    QList<int> nCountList = mpTable->getDefCounts();
    if( nCountList.size() <= DEFCHECKBOX_COUNT || mpTotalLab == 0 ) {
        return ;
    }
    for( int i=0; i<DEFCHECKBOX_COUNT; i++ ) {
        mpCheckBox[i]->setText( "(" + QString::number(nCountList.at(i)) + ")" );
    }
    mpTotalLab->setText( "(" + QString::number(nCountList.at(DEFCHECKBOX_COUNT)) + ")" );
}

//Set DevType ComboBox data, Set DevRegVol ComboBox data
void FilterView::setDevTypeVolComboData(FilterView *pFilterView)
{
    QList<QStringList> dLists = pFilterView->mpTable->getAllDatas();
    mpDevTypeCom->addItem("");
    mpDevRegVolCom->addItem("");
    for( int i=0; i<dLists.size(); i++ ) {
        QStringList sList = dLists.at(i);
        QString sDevType = sList.at(6);
        QString sDevRegVol = sList.at(4);
        bool bFlag = false;
        for( int j=0; j<mpDevTypeCom->count(); j++ ) {
            if( sDevType.compare(mpDevTypeCom->itemText(j)) == 0 ) {
                bFlag = true;
                break;
            }
        }
        if( !bFlag ) {
            mpDevTypeCom->addItem( sDevType );
        }

        //Add DevRegVol ComboBox items
        bFlag = false;
        for( int j=0; j<mpDevRegVolCom->count(); j++ ) {
            if( sDevRegVol.compare(mpDevRegVolCom->itemText(j)) == 0 ) {
                bFlag = true;
                break;
            }
        }
        if( !bFlag ) {
            mpDevRegVolCom->addItem( sDevRegVol );
        }

    }
}

//Process the table selected event
void FilterView::tableSelectionChanged()
{
    qDebug() << "tableSelectionChanged:" << mpTable->currentRow();

    QList<int> nColList;
    QTableWidgetItem *pItem;
    QString sdevname;

    nColList << 3 << 5 << 4 << 7 << 6;
    for( int i=0; i<nColList.size(); i++ ) {
        pItem = mpTable->item( mpTable->currentRow(), nColList.at(i) );
        sdevname += pItem->text();
        if( i<nColList.size()-1 ) {
            sdevname += "-";
        }
    }
    mpdevnameLab->setText( sdevname );
    emit tableSelectionChanged( mpTable, mpPhaseRadBtn->isChecked() );
}

//Process the Phase Contrast radio click event
void FilterView::phaseRadClick(bool bChecked)
{
    if( mpTable->currentRow() >= 0 ) {
        emit tableSelectionChanged( mpTable, bChecked );
    }
}

//Process the Ir. image radio click event
void FilterView::setIrRadioChecked(bool bCheck)
{    
    mpIrRadionBtn->setChecked( bCheck );
    mpDevDetailRadBtn->setChecked( !bCheck );
}

void FilterView::treeItemSelectionChangedSlot(QStringList textList)
{
    //qDebug() << "FilterView::treeItemSelectionChangedSlot";
    emit treeItemSelectionChanged(textList);
    setDefCount();
}




