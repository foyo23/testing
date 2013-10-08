/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现设备树操作和展示
 */
#include "devtreeview.h"
#include <QDebug>
#include <QTreeWidgetItem>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QCoreApplication>
#include <QMetaType>
#include <QFile>
#include<QtSql/QSql>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>

DevTreeView::DevTreeView(QWidget *par):QTreeWidget(par)
{
    init_top_level();
}

/*
DevTreeView::DevTreeView(QWidget *par):QTreeWidget(par)
{
    this->setColumnCount(1);
    setHeaderHidden(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setStyleSheet("QTreeWidget::item{height:20px; }");//border: 0px;
    //qDebug() << "DevTree indentation=" << this->indentation(); default is 20
    this->setIndentation( 15 );
    qDebug() << "codecForLocale:" << QTextCodec::codecForLocale()->name().constData();

    //Load data
    //QStringList contentList;
    QTreeWidgetItem *pRootItem = 0;//*pItem = 0, *pParItem = 0
    QString sdir = ":/res/devtree.json";//QCoreApplication::applicationDirPath() + "devtree.json";
    QFile file( sdir );

    if (!file.open(QFile::ReadOnly))
        return ;
    QByteArray data = file.readAll();
    //QTextCodec *codec = QTextCodec::codecForName( "UTF-8" );
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
        QList<QJsonObject> jobjl;
        jobjl.append( obj );
        parseJsonObj( jobjl, &pRootItem );
        break;
    }

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChangedSlot()) );

}
*/
//Parse device tree data
void DevTreeView::parseJsonObj( QList<QJsonObject> jobjl, QTreeWidgetItem **ppItem )
{
    QList<QJsonObject> njobjl;
    QTreeWidgetItem *pParItem = 0;

    for( int seq=0; seq<jobjl.size(); seq++ ) {
        QStringList contentList;
        QJsonObject jobj = jobjl.takeAt( seq );

        if ( !jobj.contains( "name" ) ) {
            qDebug() << "Not contains name key";
            break;
        }
        QJsonValue v = jobj.take( "name" );
        if( v.isString() ) {
            QString stmp = v.toString();
            //stmp = codec->toUnicode( stmp.toUtf8() );
            contentList << stmp;
            if ( *ppItem ) {
                pParItem = new QTreeWidgetItem(*ppItem, contentList);               
            } else {
                pParItem = new QTreeWidgetItem(this, contentList);
            }

        } else {
            break;
        }

        //Parse children
        if ( !jobj.contains( "children") ) {
           // qDebug() << "Has not children";
            break;
        }
        QJsonValue val = jobj.take("children");
        if( !val.isArray() ) {
            qDebug() << "children is not a array";
            break;
        }

        QJsonArray arr = val.toArray();
        njobjl.clear();
        for ( int i=0; i<arr.size(); i++ ) {
            QJsonValue value = arr.at(i);
            if( value.isObject() ) {
                njobjl.append( value.toObject() );
            }
        }
        parseJsonObj( njobjl, &pParItem );
        break;
    }

    if( jobjl.size() > 0 ) {
        parseJsonObj( jobjl, ppItem );
    }

}

void DevTreeView::itemSelectionChangedSlot()
{
    QList<QTreeWidgetItem *> itemList = this->selectedItems();
    QTreeWidgetItem *pItem = itemList.at(0);
    QStringList sList;
    while( pItem ) {
        sList.insert( 0, pItem->text(0) );
        pItem = pItem->parent();
    }
    emit treeItemSelectionChanged(sList);
}

void DevTreeView::init_top_level() {
    //开始初始化顶部
    clear();
    QString s_cmd = "select id,name from regions where parent_id = 0 ";
    QSqlQuery o_query;
    o_query.prepare( s_cmd );
    if( !o_query.exec() ) {
        QSqlError o_err= o_query.lastError() ;
        qDebug()<<o_err; return ;
    }

    int i_find_id;
    QString s_name;
    QList<QTreeWidgetItem *>items;
    while( o_query.next() ) {
        i_find_id = o_query.value(0).toInt();
        s_name = o_query.value(1).toString();
        QTreeWidgetItem *ptemp = new QTreeWidgetItem();
        ptemp->setText( 0, s_name );
        ptemp->setData( 0, Qt::UserRole, i_find_id );
        ptemp->insertChild( 0,new QTreeWidgetItem() );
        items.append( ptemp );
    }
    insertTopLevelItems( 0 , items );
    //构造区域树
    for( int i = 0; i < items.size(); i++ ){ item_expanded ( items.at( i ) ); }
}

void DevTreeView::item_expanded( QTreeWidgetItem *p_item ) {
    //扩展ITEM
    QTreeWidgetItem *p_children = p_item->child( 0 );
    QString s_text = p_children->text(0);
    if( s_text.isEmpty() ) {
        int i_parent_id = p_item->data( 0, Qt::UserRole ).toInt();
        QString s_cmd = "select id,name from regions where parent_id = :parent_id";
        QSqlQuery o_query;
        o_query.prepare( s_cmd );
        o_query.bindValue( ":parent_id", i_parent_id );
        if( !o_query.exec() ) {
            QSqlError o_err= o_query.lastError() ;
            qDebug()<<o_err; return ;
        }

        int i_find_id;
        QString s_name;
        QList<QTreeWidgetItem *> items;
        while( o_query.next() ) {
            i_find_id = o_query.value(0).toInt();
            s_name = o_query.value(1).toString();
            QTreeWidgetItem *ptemp = new QTreeWidgetItem();
            ptemp->setText( 0, s_name );
            ptemp->setData( 0, Qt::UserRole, i_find_id );
            ptemp->insertChild( 0,new QTreeWidgetItem() );
            items.append( ptemp );
        }
        //判断递归条件
        if( items.size() > 0) {
        for( int i = 0 ; i < items.size() ; i++){ item_expanded(items.at(i)); } }
        p_item->insertChildren( 1, items );
        p_item->removeChild( p_children );
    } else {  //处理完成
        QTreeWidget *p_tree = p_item->treeWidget();
        p_tree->setItemExpanded( p_item, true );
    }
}

void DevTreeView::init_tree_show() {

    //QString s_cmd = "select id,name from sqlite_master where type=\"table\"";
    QString s_cmd = "select name from regions ";
    QSqlQuery query;
    query.prepare( s_cmd );
    if( !query.exec() ) {
        QSqlError o_err = query.lastError();
        qDebug()<<"wrong";
        QString s_temp = o_err.text();
    }

    QStringList list_table;
    while( query.next() ) {
         int i_find_id = query.value(0).toInt();
         qDebug()<<i_find_id;
        QString s_temp = query.value(1).toString();
        //int s_temp1 = query.value(1).toInt();
        int s_temp2= query.value(2).toInt();
       // qDebug()<<s_temp1;
        qDebug()<<s_temp2;
        int i_parent_id = query.value(1).toInt();
        qDebug()<<"i_parent_id"<<i_parent_id;
        qDebug()<<"wik"<<s_temp;
        list_table.append( s_temp );
    }
qDebug()<<"wik";
    /*
    QSqlQuery o_query;

    QString s_cmd = "select  basic_types.ana_unit_text, basic_types.id, regions.standard_ir_file_name, basic_types.outline_vector_file_name, basic_types.basic_type_name from regions left join basic_types on regions.basic_type_id = basic_types.id where regions.id = :id;";
    o_query.prepare( s_cmd );
    o_query.bindValue( ":id", 1 );

    if( !o_query.exec() ) {
        QSqlError o_err= o_query.lastError() ;
        QString s= o_err.text();
        return ;
    }
*/
    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 10; ++i)
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
    insertTopLevelItems(1, items);
    QTreeWidgetItem *ptemp = new QTreeWidgetItem();
    ptemp->setText( 0, "test-child-node" );
   this->topLevelItem(1)->addChild(ptemp);
   QTreeWidgetItem *ptemp1 = new QTreeWidgetItem();
   ptemp1->setText( 0, "test--node" );
   this->topLevelItem(1)->child(0)->addChild(ptemp1);
}


/*
void DevTreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QModelIndex index0 = currentIndex();
        qDebug() << index0.data().toString();
    }
}
*/
