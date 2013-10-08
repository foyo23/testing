/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现查询结果表的创建、数据的读取和展示
 */
#include "queryresulttable.h"
#include <QHeaderView>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QDate>
#include <QTime>

//#include <QLabel>
#include "deflabel.h"

QueryResultTable::QueryResultTable(QWidget *parent, bool bDevDetail ):QTableWidget(parent)
{
    QStringList header;
    QList<int> colWidths;
    if ( bDevDetail ) {
        header << tr("Sequence number") << tr("Substation") << tr("Bay unit") << tr("Device region");
        header << tr("Device model") << tr("Device Name") << tr("Device voltage") << tr("Phase");
        header << tr("Curr. device resource");
        colWidths << 80 << 160 << 100 << 70 << 160 << 140 << 70 << 70 << 180;
    } else {
        header << tr("Sequence number") << tr("Date")  << tr("Time")  << tr("Substation") << tr("Device region");
        header << tr("Device region voltage") << tr("Name remarks") << tr("Device type")  << tr("Phase");
        header << tr("Part angle")  << tr("Defect")  << tr("Device model")  << tr("Implementation");
        header << tr("Conlack time")  << tr("Conlack way") << tr("Defect text")  << tr("Formula text") << tr("Flag");
        header << "irimagefile" << "result" << "lightimgfile"; //Hide columns

        colWidths << 40 << 90 << 90 << 100 << 130 << 90 << 100 << 100 << 60 << 60 << 120 << 120 << 130;
        colWidths << 130 << 130 << 130 << 130 << 130 << 0 << 0 << 0;
    }

    this->setColumnCount( header.size() );
    for( int i=0; i<colWidths.size(); i++ ) {
        this->setColumnWidth( i, colWidths.at(i) );

        QTableWidgetItem *pHeaderItem = new QTableWidgetItem( header.at(i) );
        if( 0 == i ) {
            pHeaderItem->setTextAlignment(Qt::AlignRight);
        } else if( 1 == i || 2 == i || 8 == i || 10 == i ) {
            pHeaderItem->setTextAlignment(Qt::AlignCenter);
        } else {
            pHeaderItem->setTextAlignment(Qt::AlignLeft);
        }

        this->setHorizontalHeaderItem( i, pHeaderItem );
        if( colWidths.at(i) == 0 ) {
            this->setColumnHidden( i, true );
        }
    }
    /*if ( !bDevDetail ) {
        this->setColumnHidden( header.size()-1, true );
        this->setColumnHidden( header.size()-2, true );
    }*/

    this->setSelectionMode( QAbstractItemView::SingleSelection );
    this->setSelectionBehavior( QAbstractItemView::SelectRows );
    QHeaderView *phView = this->verticalHeader();
    phView->setHidden( true );


    if ( bDevDetail ) {
        mpConfig = 0;
    } else {
        mpConfig = new Config(0);
    }
    loadDatas( bDevDetail );
    setDatasToWidget();    

    connect(this->parent(), SIGNAL(treeItemSelectionChanged(QStringList)), this, SLOT(treeItemSelectionChangedSlot(QStringList)) );
}

//Get the three phase records or history records associated with the selected record
QList<QStringList> QueryResultTable::getSelectedDatas(bool bThreePhase, int *nCurrIndex)
{
    mSelectedDataList.clear();

    QTableWidgetItem *pItem;
    QStringList datas;

    if( bThreePhase ) {
        mSelectedDataList.append( datas );
        mSelectedDataList.append( datas );
        mSelectedDataList.append( datas );
    }
    for( int i=1; i<this->columnCount(); i++ ) {
        pItem = this->item( this->currentRow(), i );
        if( pItem == 0 ) {
            QWidget *pWid = this->cellWidget( this->currentRow(), i );
            if( pWid && i == 10 ) {
                DefLabel *pLab = (DefLabel *)pWid;
                datas << pLab->getString();
                continue;
            }
            return mSelectedDataList;
        }
        datas << pItem->text();
    }

    if( bThreePhase ) {
        if( datas.at(7).contains('A') ) {
            mSelectedDataList.replace( 0, datas );
            *nCurrIndex = 0;
        }
        else if ( datas.at(7).contains('B') ) {
            mSelectedDataList.replace( 1, datas );
            *nCurrIndex = 1;
        } else {
            mSelectedDataList.replace( 2, datas );
            *nCurrIndex = 2;
        }
    } else {
        mSelectedDataList.append( datas );
        *nCurrIndex = 0;
    }

    QDate dCurrDate = QDate::fromString( datas.at(0)+datas.at(1), Qt::ISODate );
    for ( int i=0; i<mTotalList.size(); i++ ) {
        QStringList tmpList = mTotalList.at(i);
        QString sPhase = tmpList.at( 7 );
        QString sSub = tmpList.at( 2 );
        QString sDevReg = tmpList.at( 3 );
        QString sNameRem = tmpList.at( 5 );
        QString sDevRegVol = tmpList.at( 4 );
        QString sDevType = tmpList.at( 6 );

        QString sDate = tmpList.at( 0 );
        QString sTime = tmpList.at( 1 );
        QDate dDate = QDate::fromString( sDate+sTime, Qt::ISODate );

        if( sSub.compare( datas.at(2)) == 0 && sDevReg.compare( datas.at(3)) == 0 && sNameRem.compare( datas.at(5)) == 0
                && sDevRegVol.compare( datas.at(4)) == 0 && sDevType.compare( datas.at(6)) == 0  ) {
            if( bThreePhase ) {
                if( sPhase.contains('A') ) {
                    if ( mSelectedDataList.at(0).size() == 0 ) {
                        mSelectedDataList.replace( 0, tmpList );
                    }
                } else if ( sPhase.contains('B') ) {
                    if ( mSelectedDataList.at(1).size() == 0 ) {
                        mSelectedDataList.replace( 1, tmpList );
                    }
                } else if ( sPhase.contains('C') ){
                    if ( mSelectedDataList.at(2).size() == 0 ) {
                        mSelectedDataList.replace( 2, tmpList );                       
                    }
                }
            } else {
                if( sPhase.compare(datas.at(7)) == 0 && dCurrDate > dDate ) {
                    bool bFlag = false;
                    int j;
                    for( j=0; j<mSelectedDataList.size(); j++ ) {
                        QDate dTmpDate = QDate::fromString( mSelectedDataList.at(j).at(0)+mSelectedDataList.at(j).at(1), Qt::ISODate );
                        if ( dTmpDate < dDate ) {
                            mSelectedDataList.insert(j, tmpList );
                            /*if( *nCurrIndex <= j ) {
                                *nCurrIndex = *nCurrIndex+1;
                            }*/
                            bFlag = true;
                            break;
                        }
                    }
                    if( !bFlag ) {
                        mSelectedDataList.append( tmpList );
                        /*if( *nCurrIndex <= j ) {
                            *nCurrIndex = *nCurrIndex+1;
                        }*/
                    }
                }
            }
        }
    }
    //qDebug() << "*nCurrIndex=" << *nCurrIndex;
    return mSelectedDataList;
}

//Get the Urgent, Serious, Commonly, attention, Normal, Unknown, total records number
QList<int> QueryResultTable::getDefCounts()
{
    QList<int> nRetList;

    for( int i=0; i<6; i++ ) {
        nRetList.append( 0 );
    }
    nRetList.append( mQueryResultList.size() );
    if( mpConfig ) {
        QStringList sDefList = mpConfig->getDefList();
        for( int i=0; i<mQueryResultList.size(); i++ ) {
            QString sDef = mQueryResultList.at(i).at(9);
            bool bFlag = false;
            for( int j=0; j<sDefList.size(); j++ ) {
                if( sDef.compare( sDefList.at(j)) == 0 ) {
                    int nCount = nRetList.at(j);
                    nCount++;
                    nRetList.replace( j, nCount );
                    bFlag = true;
                    break;
                }
            }

            if( !bFlag ) {
                int nCount = nRetList.at(5);
                nCount++;
                nRetList.replace( 5, nCount );
            }

        }
    }

    return nRetList;
}

//Get the all datas
QList<QStringList> QueryResultTable::getAllDatas()
{
    return mQueryResultList;//mTotalList
}

//Read the record datas
void QueryResultTable::loadDatas(bool bDevDetail)
{
    QString sdir;// = QCoreApplication::applicationDirPath();
    if( bDevDetail ) {
        sdir = ":/res/devdetails.json";
    } else {
        sdir = ":/res/datas.json";
    }

    QFile file( sdir );

    if (!file.open(QFile::ReadOnly))
        return ;
    QByteArray data = file.readAll();
    file.close();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson( data, &err );
    while( true ) {
        if( doc.isNull() || doc.isEmpty() ) {
            qDebug() << "Json parse: " << err.errorString();
            break;
        }
        if( !doc.isObject() ) {
            qDebug() << "Json doc is not a object";
            break;
        }

        QJsonObject obj = doc.object();
        QStringList skeyList;
        if( bDevDetail ) {
            skeyList << "sub" << "bay_unit" << "dev_reg" << "dev_model" << "dev_name" << "dev_vol" << "phase" << "curr_dev_res";
        } else {
            skeyList << "date" << "time" << "sub" << "dev_reg" << "dev_reg_vol" << "name_rem" << "dev_type" << "phase";
            skeyList << "part_ang" << "def" << "dev_model" << "implmentation" << "conlack_time" << "conlack_way";
            skeyList << "def_text" << "formula_text" << "flag" << "irimage" << "result" << "lightimg";
        }

        if ( obj.value("records").isArray() ) {
            QJsonArray arr = obj.value("records").toArray();                       
            for( int i=0; i<arr.size(); i++ ) {               
                QJsonObject jobj = arr.at( i ).toObject();
                QStringList datas;                
                for( int j=0; j<skeyList.size(); j++ ) {
                    if( jobj.contains( skeyList.at(j) ) ) {
                        QJsonValue val = jobj[skeyList.at(j)];
                        QString sTmp;
                        if( val.isString() ) {
                            sTmp = val.toString();
                        } else if( val.isObject() ){
                            QJsonDocument tmpDoc = QJsonDocument( val.toObject() );
                            sTmp = tmpDoc.toJson();
                        }                        
                        datas << sTmp;
                    }
                }
                mTotalList.append( datas );
                mQueryResultList.append( datas );
            }
        }
        break;
    }
}

void QueryResultTable::setDatasToWidget()
{
    this->clearContents();
    this->setRowCount( mQueryResultList.size() );
    int nDefColWidth = this->columnWidth( 10 );

    for( int i=0; i<mQueryResultList.size(); i++ ) {
        this->setRowHeight( i, 20 );
        int nRowHeight = this->rowHeight(i);
        QTableWidgetItem *pItem = new QTableWidgetItem( QString::number(i+1) );
        pItem->setTextAlignment( Qt::AlignRight );
        this->setItem( i, 0, pItem );
        for( int j=0; j<mQueryResultList.at(i).size(); j++ ) {
            QTableWidgetItem *pItem2;
            if( 9 == j && mpConfig ) {
                pItem2 = 0; //new DefNatureWidItem( mpConfig, mQueryResultList.at(i).at(j) );

                E_DEF_LEVEL def_lev = DEF_LEV_NONE;
                QString sdef = mQueryResultList.at(i).at(j);
                QStringList defList = mpConfig->getDefList();
                for( int k=0; k<defList.size(); k++ ) {
                    if( sdef.compare( defList.at(k)) == 0 ) {
                        def_lev = (E_DEF_LEVEL)k;
                        break;
                    }
                }
                DefLabel *pDefLab = new DefLabel( QSize(nDefColWidth, nRowHeight), sdef, def_lev, this);
                this->setCellWidget( i, j+1, pDefLab );
            } else {
                pItem2 = new QTableWidgetItem( mQueryResultList.at(i).at(j) );
            }
            if( pItem2 && (0 == j || 1 == j || 7 == j || 9 == j) ) {
                pItem2->setTextAlignment( Qt::AlignCenter );
            }
            if( pItem2 ) {
                this->setItem( i, j+1, pItem2 );
            }
        }
    }
}

void QueryResultTable::treeItemSelectionChangedSlot(QStringList textList)
{
    mQueryResultList.clear();
    for( int i=0; i<mTotalList.size(); i++ ) {
        bool bFlag = true;
        for( int j=3; j<textList.size(); j++ ) {
            QString sTmp = textList.at(j);
            if( j==3 && sTmp.compare(mTotalList.at(i).at(4)) != 0 ) { //Dev Reg vol
                bFlag = false;
                break;
            } else if( j== 4 && sTmp.compare(mTotalList.at(i).at(2)) != 0 ) { //substation
                bFlag = false;
                break;
            } else if( j== 5 && sTmp.compare(mTotalList.at(i).at(2)) != 0 ) { //Dev vol

            } else if( j== 6 && sTmp.compare(mTotalList.at(i).at(3)) != 0 ) { //Dev reg
                bFlag = false;
                break;
            } else if( j== 7 && sTmp.compare(mTotalList.at(i).at(6)) != 0 ) { //dev type
                bFlag = false;
                break;
            } else if( j== 8 && sTmp.compare( mTotalList.at(i).at(5) + mTotalList.at(i).at(7) ) != 0 ) { //name remark + phase
                bFlag = false;
                break;
            }
        }

        if( bFlag ) {
            mQueryResultList.append( mTotalList.at(i) );
        }
    }
    setDatasToWidget();
}
