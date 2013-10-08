#include "yfsqlite.h"

YFSqlite::YFSqlite() {
    b_connect_stat = false;
}

YFSqlite::~YFSqlite() {
    if( b_connect_stat ) {
        mo_db.close();
    }
}

bool YFSqlite::connect_sqlite( QString s_sqlite_name, QString s_passwd ) {
    mo_db = QSqlDatabase::addDatabase( "QSQLITE" );
    mo_db.setDatabaseName( s_sqlite_name );
    mo_db.setPassword( s_passwd );

    if( mo_db.open() ) {
        b_connect_stat = true;
        return true;
    }else{
        QSqlError o_err;
        o_err = mo_db.lastError();
        throw o_err.number();
    }
}
