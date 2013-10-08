/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现红外图片、可见光图片及参数表的展示
 */
#include "irimageview.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSpacerItem>
#include <QTableWidgetItem>
#include <QPixmap>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QHeaderView>
#include <QResizeEvent>
#include <QApplication>


//#define PARAMTABLE_GROUP_WIDTH 140
#define TABLE_COLUMN_WIDTH 55
IrImageView::IrImageView(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *phLayout = new QHBoxLayout();    
    QStringList header;
    header << tr("Type") << tr("Value");
    int nLabWidth = this->width()/4;
    int nLabHeight = nLabWidth*3/4;
    mpConfig = new Config(this);
    for( int i=0; i<SHOW_IMAGE_COUNT; i++ ) {
        QHBoxLayout *phLayout3 = new QHBoxLayout();
        static const QChar data[3] = { 'A', 'B', 'C' };
        QString stitle(&data[i], 1);
        stitle.append( tr("title") );

        mpLab[i] = new QLabel( stitle );
        mpLab[i]->setFixedHeight( 18 );
        mpDefColorLab[i] = new DefLabel( DEF_LEV_NONE, this );
        mpPhaseLab[i] = new QLabel( "" );
        QHBoxLayout *phLay = new QHBoxLayout();
        phLay->addWidget( mpLab[i] );
        phLay->addWidget( mpDefColorLab[i] );
        phLay->addWidget( mpPhaseLab[i] );

        mpImgLab[i] = new ImageLabel(this);
        mpTextLab[i] = new ImageLabel(this);
        mpTextLab[i]->setHidden( true );
        mpImgLab[i]->setFixedSize( nLabWidth, nLabHeight );
        mpTextLab[i]->setFixedSize( nLabWidth, nLabHeight );

        QGroupBox *pGroup = new QGroupBox;
        QVBoxLayout *pvLayout = new QVBoxLayout();
        pvLayout->addLayout( phLay );
        pvLayout->setAlignment( phLay, Qt::AlignCenter );
        pvLayout->addWidget( mpImgLab[i] );
        pvLayout->addWidget( mpTextLab[i] );
        pGroup->setLayout( pvLayout );

        phLayout3->addWidget( pGroup, 3);

        QGroupBox *pGroup2 = new QGroupBox;
        mpIrImgRadBtn[i] = new QRadioButton( tr("Ir. image") );
        QRadioButton *pVLightRad = new QRadioButton( tr("Visible light image") );
        QButtonGroup *pBtnGrp = new QButtonGroup();        
        mpIrImgRadBtn[i]->setChecked( true );

        mpTable[i] = new QTableWidget();
        QHeaderView *phView = mpTable[i]->verticalHeader();
        phView->setHidden( true );
        mpTable[i]->setColumnCount( header.size() );
        mpTable[i]->setHorizontalHeaderLabels( header );
        mpTable[i]->setColumnWidth( 0, TABLE_COLUMN_WIDTH );
        mpTable[i]->setColumnWidth( 1, TABLE_COLUMN_WIDTH-5 );

        pBtnGrp->addButton( mpIrImgRadBtn[i] );
        pBtnGrp->addButton( pVLightRad );
        pBtnGrp->setExclusive( true );
        QHBoxLayout *phLayout2 = new QHBoxLayout();
        phLayout2->addWidget( mpIrImgRadBtn[i] );
        phLayout2->addWidget( pVLightRad );
        QVBoxLayout *pvLayout2 = new QVBoxLayout();
        pvLayout2->addLayout( phLayout2 );
        pvLayout2->addWidget( mpTable[i] );
        pGroup2->setLayout( pvLayout2 );
        //pGroup2->setFixedWidth( PARAMTABLE_GROUP_WIDTH );

        phLayout3->addWidget( pGroup2, 1 );
        //phLayout3->set
        phLayout->addLayout( phLayout3, 1 );
    }
    this->setLayout( phLayout );

    connect(mpIrImgRadBtn[0], SIGNAL(toggled(bool)), this, SLOT(irImgARadClickSlot(bool)));
    connect(mpIrImgRadBtn[1], SIGNAL(toggled(bool)), this, SLOT(irImgBRadClickSlot(bool)));
    connect(mpIrImgRadBtn[2], SIGNAL(toggled(bool)), this, SLOT(irImgCRadClickSlot(bool)));
    mpQueryResultTab = 0;
}

void IrImageView::resizeEvent(QResizeEvent *event)
{
    int nLabWidth = event->size().width()/4;
    int nLabHeight = nLabWidth*3/4;
    qDebug() << "nLabWidth=" << nLabWidth << " nLabHeight=" << nLabHeight;// << " mpLab[0]->height()" << mpLab[0]->height();
    for( int i=0; i<SHOW_IMAGE_COUNT; i++ ) {
        mpImgLab[i]->setFixedSize( nLabWidth, nLabHeight );
        mpTextLab[i]->setFixedSize( nLabWidth, nLabHeight );
    }
    this->setFixedHeight( nLabHeight + mpLab[0]->height() + 5 );
}

void IrImageView::processImgRadClick(int seq, bool bChecked)
{
    int nCurrIndex;
    if( mpQueryResultTab == 0 ) {
        return ;
    }
    QList<QStringList> list = mpQueryResultTab->getSelectedDatas( mbPhaseContrast, &nCurrIndex );
    int i = seq;

    if( list.size() > i && list.at(i).size() > 19 ) {
        QString sfn;
        if( bChecked ) {
            sfn = list.at(i).at(17);//ir
            sfn = QCoreApplication::applicationDirPath() + "/irimages/" + sfn;//
        } else {
            sfn = list.at(i).at(19);//light
            sfn = QCoreApplication::applicationDirPath() +"/lightimages/" + sfn;
        }

        qDebug() << sfn;
        mpImgLab[i]->clear();
        mpImgLab[i]->loadImage( sfn );
        mpImgLab[i]->setHidden( false );
        mpTextLab[i]->setHidden( true );
    } else {
        mpTextLab[i]->clear();
        mpTextLab[i]->setAlignment( Qt::AlignCenter );
        if( bChecked ) {
            mpTextLab[i]->setText("<b style='font-family:verdana;font-size:xx-large;color:gray'>" + tr("No Ir Image") + "</b>");
        } else {
            mpTextLab[i]->setText("<b style='font-family:verdana;font-size:xx-large;color:gray'>" + tr("No Light Image") + "</b>");
        }
        mpTextLab[i]->setHidden( false );
        mpImgLab[i]->setHidden( true );
    }
}

void IrImageView::irImgARadClickSlot(bool bChecked)
{
    processImgRadClick( 0, bChecked );
}

void IrImageView::irImgBRadClickSlot(bool bChecked)
{
    processImgRadClick( 1, bChecked );
}

void IrImageView::irImgCRadClickSlot(bool bChecked)
{
    processImgRadClick( 2, bChecked );
}

//Process the table selected event
void IrImageView::tableSelectionChangedSlot(QueryResultTable *pTable, bool bPhaseContrast)
{
    QList<int> nColList;    
    QString sdevname;
    int nCurrIndex;
    QList<QStringList> list = pTable->getSelectedDatas( bPhaseContrast, &nCurrIndex );

    mbPhaseContrast = bPhaseContrast;
    mpQueryResultTab = pTable;
    nColList << 7 << 0 << 1;// << 9;
    for( int i=0; i<SHOW_IMAGE_COUNT; i++ ) {
        //Set title text
        sdevname.clear();
        mpLab[i]->clear();
        mpDefColorLab[i]->clear();
        mpPhaseLab[i]->clear();
        if( list.size() > i ) {
            QStringList slist = list.at(i);
            for( int j=0; j<nColList.size(); j++ ) {                
                if( slist.size() <= nColList.at(j) ) {
                    break;
                }
                //qDebug
                sdevname += slist.at(nColList.at(j));
                if( i<nColList.size()-1 ) {
                    sdevname += " ";
                }
            }
        }
        if( !sdevname.isEmpty() ) {
            if( nCurrIndex == i ) {
                mpLab[i]->setText( "<b>" + sdevname + "</b>" );
            } else {
                mpLab[i]->setText( sdevname );
            }

            QString sdef = list.at(i).at(9);
            E_DEF_LEVEL def_lev = DEF_LEV_NONE;
            QStringList defList = mpConfig->getDefList();
            for( int j=0; j<defList.size(); j++ ) {
                if( sdef.compare( defList.at(j)) == 0 ) {
                    def_lev = (E_DEF_LEVEL)j;
                    break;
                }
            }
            mpDefColorLab[i]->setDefLev(def_lev);

            if( nCurrIndex == i ) {
                mpPhaseLab[i]->setText( "<b>" + sdef + "</b>" );
            } else {
                mpPhaseLab[i]->setText( sdef );
            }
        }


        //Load image
        processImgRadClick( i, mpIrImgRadBtn[i]->isChecked() );
        /*if( list.size() > i ) {
            QString sfn;
            if( mpIrImgRadBtn[i]->isChecked() ) {
                sfn = list.at(i).at(17);
            } else {
                sfn = list.at(i).at(19);
            }

            qDebug() << sfn;            
            mpImgLab[i]->loadImage( sfn );
            mpImgLab[i]->setHidden( false );
            mpTextLab[i]->setHidden( true );
        } else {
            mpTextLab[i]->setAlignment( Qt::AlignCenter );
            if( mpIrImgRadBtn[i]->isChecked() ) {
                mpTextLab[i]->setText("<b style='font-family:verdana;font-size:xx-large;color:gray'>"+tr("No Ir Image") + "</b>");
            } else {
                mpTextLab[i]->setText("<b style='font-family:verdana;font-size:xx-large;color:gray'>"+tr("No Light Image") + "</b>");
            }
            mpTextLab[i]->setHidden( false );
            mpImgLab[i]->setHidden( true );
        }*/

        //Set param table
        mpTable[i]->clearContents();
        if( list.size() > i && list.at(i).size() > 18 ) {
            QString sResult = list.at(i).at(18);
            //qDebug() << sResult;
            QJsonParseError err;
            QJsonDocument doc = QJsonDocument::fromJson( sResult.toUtf8(), &err );
            while( true ) {
                if( doc.isNull() || doc.isEmpty() ) {
                    qDebug() << "Json parse: " << err.errorString();
                    break;
                }
                if( !doc.isObject() ) {
                    qDebug() << "Json doc is not a object";
                    break;
                }

                QJsonObject jobj = doc.object();
                QString sReg = "reg";
                int nRow =0;
                for (QJsonObject::Iterator it = jobj.begin(); it != jobj.end(); it++) {
                    if( sReg.compare(it.key()) == 0 ) {
                        QJsonObject obj = it.value().toObject();
                        for (QJsonObject::Iterator it2 = obj.begin(); it2 != obj.end(); it2++) {
                            nRow++;
                        }
                    } else {
                        nRow++;
                    }
                }
                mpTable[i]->setRowCount( nRow );                

                nRow =0;
                for (QJsonObject::Iterator it = jobj.begin(); it != jobj.end(); it++) {
                    if( sReg.compare(it.key()) == 0 ) {
                        QJsonObject obj = it.value().toObject();
                        for (QJsonObject::Iterator it2 = obj.begin(); it2 != obj.end(); it2++) {
                            mpTable[i]->setItem( nRow, 0, new QTableWidgetItem( it2.key() ) );
                            mpTable[i]->setItem( nRow, 1, new QTableWidgetItem( it2.value().toString() ) );
                            mpTable[i]->setRowHeight( nRow, 20 );
                            nRow++;
                        }
                    } else {
                        mpTable[i]->setItem( nRow, 0, new QTableWidgetItem( it.key() ) );
                        mpTable[i]->setItem( nRow, 1, new QTableWidgetItem( it.value().toString() ) );
                        mpTable[i]->setRowHeight( nRow, 20 );
                        nRow++;
                    }
                }
                break;
            }
        }

    }
}
