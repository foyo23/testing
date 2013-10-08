#include "database-structure.h"
#include<QFile>
#include<QApplication>
#include<QCoreApplication>
#include<QDir>
#include<QProcess>
#include<QVariant>
#include<QProcess>
#include<QDebug>
#include <QObject>
#include <QProcessEnvironment>
DataBaseStructure::DataBaseStructure( QString s_database_name, QString s_passwd ) {
    b_create_database_label = false;
    if( !s_database_name.isEmpty() && !s_passwd.isEmpty()  ) {
        ms_database_name = s_database_name;
        ms_passwd = s_passwd;
        if( connect_sqlite_db() ){
            b_connect_sucess_label = true;
            analyse_file_version_info();
            if( b_create_database_label == true ) {
                create_newest_db_structure();
            }
        }else{
            b_connect_sucess_label = false;
        }
    }
}

DataBaseStructure::~DataBaseStructure() {
    if( b_connect_sucess_label == true ) {
        QString s_dbname = mp_db->connectionName();
        mp_db->close();
        delete mp_db;
        mp_db = NULL;
        QSqlDatabase::removeDatabase( s_dbname );
    }
}


bool DataBaseStructure::update_to_newest_db_structure() {
    //连接没有成功直接返回失败
     if( !b_connect_sucess_label ) { return false; }

     QString s_last_ver = get_latest_db_version();
     if( s_last_ver.isEmpty() ){
         //为空就表示没有版本号， 从00000开始执行
         QString s_version;
         QMap< QString, QString >::iterator iter;
         for( int i = 0; i < m_vector_sql_version.size(); i++ ) {
              s_version = m_vector_sql_version.at(i);
              iter = m_map_sqlversion_filename.find( s_version );
              if( iter != m_map_sqlversion_filename.end() ) {
                  if( execution_sql_file_to_update_db( iter.value() ) ) {
                       insert_version_info_to_db_schema_migrations_table( s_version );
                  }else {
                      return false;
                  }
              }
         }
     }else {
         //从这个版本的最后执行
         int i_start;
         for( int i = 0; i < m_vector_sql_version.size(); i++ ) {
             if( m_vector_sql_version.at(i).compare( s_last_ver ) > 0 ) {
                 i_start = i;
                 break;
             }
         }
         QString s_version;
         QMap< QString, QString >::iterator iter;
         for( int i = i_start; i < m_vector_sql_version.size(); i++ ) {
             s_version = m_vector_sql_version.at(i);
             iter = m_map_sqlversion_filename.find( s_version );
             if( iter != m_map_sqlversion_filename.end() ) {
                 if( execution_sql_file_to_update_db( iter.value() ) ) {
                      insert_version_info_to_db_schema_migrations_table( s_version );
                 }else{
                     return false;
                 }
             }
         }
     }
    return true;
}

bool DataBaseStructure::create_newest_db_structure() {
    //连接没有成功直接返回失败
    if( !b_connect_sucess_label ) { return false; }
    //QString s_current_path = QApplication::applicationDirPath();
    QString s_sql_dir;
    s_sql_dir += "db/";

    QString s_cmd_table_path=s_sql_dir;
    s_cmd_table_path += "schema.sql";

    QString s_cmd_seeds=s_sql_dir;
    s_cmd_seeds += "seeds.sql";
    //先测试一个
    QString s_exe_path = "sqlite3.exe";



    QString s_list_createlist_arg;
    s_list_createlist_arg = s_exe_path ;
    s_list_createlist_arg += " ";
    s_list_createlist_arg += ms_database_name;
    s_list_createlist_arg += " < ";
    s_list_createlist_arg += s_cmd_table_path;

    QString s_list_seeds_arg;
    s_list_seeds_arg = s_exe_path ;
    s_list_seeds_arg += " ";
    s_list_seeds_arg += ms_database_name;
    s_list_seeds_arg += " < ";
    s_list_seeds_arg += s_cmd_seeds;

    if( !exec_cmd( "cmd", s_list_createlist_arg ) ) {
        return false;
    }

    if( !exec_cmd( "cmd", s_list_seeds_arg ) ) {
        return false;
    }
    return true;
}

bool DataBaseStructure::clear_db_structure() {
    QString s_cmd = "select name from sqlite_master where type=\"table\"";
    QSqlQuery query;
    query.prepare( s_cmd );
    query.exec( s_cmd );

    QStringList list_table;
    while( query.next() ) {
        QString s_temp = query.boundValue(1).toString();
        list_table.append( s_temp );
    }
    if( list_table.size() == 0 ) return true;
    QString s_drop_cmd = "drop table ?";
    QSqlQuery drop_cmd;
    drop_cmd.prepare( s_drop_cmd );
    for( int i=0; i< list_table.size(); i++ ) {
        drop_cmd.addBindValue( list_table.at(i) );
        if( !drop_cmd.exec() ) { return false; }
    }

    return true;
}

int DataBaseStructure::get_tables_count() {
    QString s_cmd = "select name from sqlite_master where type=\"table\"";
    QSqlQuery query;
    query.prepare( s_cmd );
    query.exec( s_cmd );
    int i_count=0;
    while( query.next() ) {
        i_count++;
    }
    return i_count;
}

QString DataBaseStructure::get_latest_db_version() {
    QString s_cmd = "select max(version) from schema_migrations";
    QSqlQuery query;
    query.prepare( s_cmd );
    query.exec();
    QString list_version;
    while( query.next() ) {
        list_version = query.boundValue(1).toString();
    }
    return list_version;
}

bool DataBaseStructure::insert_version_info_to_db_schema_migrations_table( QString s_version ) {
    QString s_cmd;
    s_cmd = "insert into schema_migrations(version) values(:version)";
    QSqlQuery query;
    query.prepare( s_cmd );
    mp_db->transaction();
    query.bindValue(":version", s_version );
    if( query.exec( ) ) {
        return true;
    }else{
        return false;
    }
    mp_db->commit();
}

bool DataBaseStructure::execution_sql_file_to_update_db(const QString s_sql_file_name) {
    //执行sql 升级



    QString s_list_update_arg = "sqlite3.exe";
    s_list_update_arg += ms_database_name;
    s_list_update_arg += " < ";
    s_list_update_arg += s_sql_file_name;

    if( !exec_cmd( "cmd", s_list_update_arg ) ) {
        return false;
    }
    return true;
}

bool DataBaseStructure::connect_sqlite_db() {
    //联结sqlite
    mp_db =  new QSqlDatabase( QSqlDatabase::addDatabase( "QSQLITE" ) );
    mp_db->setDatabaseName( ms_database_name );
    mp_db->setPassword( ms_passwd );
    if( mp_db->open() ) {
        int i_count = get_tables_count();
        if( i_count == 0 ) {
            b_create_database_label = true;
        }
        return true;
    }else{
        //认别错误
        QSqlError o_err;
        o_err = mp_db->lastError();
        qDebug()<<o_err;
        return false;
    }
    return false;
}

void DataBaseStructure::analyse_file_version_info() {
    QString s_current_path = QApplication::applicationDirPath();//QDir::currentPath();
    s_current_path += "/db/migrate/";
    QDir *p_dir = new QDir();
    p_dir->setPath( s_current_path );

    if ( !p_dir->exists() ) return ;
    QStringList list_filter;
    list_filter<< "*.sql";
    p_dir->setNameFilters( list_filter );
   // p_dir->setFilter( QDir::NoDotAndDotDot );
    QFileInfoList list_file_info = p_dir->entryInfoList();
    qDebug()<<list_file_info.size();

    QVector< QString > vector_temp;
    foreach (QFileInfo o_fileinfo, p_dir->entryInfoList()) {
        //if( o_fileinfo.isFile() &&  ((o_fileinfo.suffix()).compare("sql") == 0 ) ) {
          QString s_filename = o_fileinfo.baseName();  //没有.sql
          vector_temp.push_back( s_filename.left( 14 ) );
          m_map_sqlversion_filename.insert(s_filename.left(14), o_fileinfo.absoluteFilePath() );
        //}
    }

    QString s_min_ver = "0000";
    int i_pos;
    while( vector_temp.size() > 1 ) {
        s_min_ver = vector_temp.at(0);
        i_pos=0;
        for(int i=0; i< vector_temp.size(); i++ ) {
            if( s_min_ver.compare( vector_temp.at(i) ) >=0  ) {
                s_min_ver = vector_temp.at(i);
                i_pos = i;
            }
        }
        vector_temp.remove( i_pos );  //记下最小的位置并删除掉
        m_vector_sql_version.push_back( s_min_ver );
    }

    m_vector_sql_version.push_back( vector_temp.at(0) );
}

bool DataBaseStructure::exec_cmd( QString s_exename, QString s_cmd ) {
    s_cmd += "\n";
    QProcess *p = new QProcess(  );
    p->start( s_exename );
    QString text = QString("sqlite3.exe 2.db < db/schema.sql\n");
    p->waitForStarted();
    p->write( s_cmd.toLatin1().data() );
    p->closeWriteChannel();
    qDebug()<<p->errorString();
    if ( !p->waitForFinished() )
    { return false; }
    else{
        p->close();
        return true;
    }
}



