#ifndef YFSQLITE_H
#define YFSQLITE_H
#include<QtSql/QSqlDatabase>
#include<QtSql/QSql>
#include<QtSql/QSqlError>
class YFSqlite
{
public:
    YFSqlite();
    ~YFSqlite();
    bool connect_sqlite( QString s_sqlite_name, QString s_passwd  );
    QSqlDatabase mo_db;
private:
    bool b_connect_stat;
};

#endif // YFSQLITE_H
