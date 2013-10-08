#ifndef DATABASESTRUCTURE_H
#define DATABASESTRUCTURE_H
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include<QtSql/QSql>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlRecord>
#include<QVector>
#include<QMap>
#include<QObject>
class DataBaseStructure
{
public:
    DataBaseStructure( QString s_database_name, QString s_passwd );
    ~DataBaseStructure();
    bool update_to_newest_db_structure();
    bool create_newest_db_structure();
    bool clear_db_structure();
private:
    QString ms_database_name;
    QString ms_passwd;
    bool b_create_database_label;
    QVector< QString > m_vector_sql_version;
    QMap< QString, QString > m_map_sqlversion_filename;

    bool b_connect_sucess_label;
    bool connect_sqlite_db();
    void analyse_file_version_info();

    bool exec_cmd( QString s_exename, QString s_cmd );
    QString get_latest_db_version();
    int get_tables_count();
    bool execution_sql_file_to_update_db( const QString s_sql_file_name );

    bool insert_version_info_to_db_schema_migrations_table( QString s_version );
    QSqlDatabase *mp_db;
};

#endif // DATABASESTRUCTURE_H
