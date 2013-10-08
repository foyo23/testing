
#include "logindialog.h"
#include "mainwindow.h"
#include "curllibport.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include "yfsqlite.h"
#include "database-structure.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(analyserec);
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("MeiSheng");
    QCoreApplication::setOrganizationDomain("meisheng.com");
    QCoreApplication::setApplicationName("analyse-api-client");
    //Load local language
    QString sdir = ":/";//QCoreApplication::applicationDirPath();
    QString sfn = QString("analyse_api_client_") + QLocale::system().name();//"zh_CN"
    QTranslator myapp(0);
    bool ret = myapp.load( sfn, sdir );
    if( !ret ) {
        qDebug()<<"load language pack fail:" + sdir + sfn;
    }
    a.installTranslator( &myapp );

    QTranslator trans(0);
    ret = trans.load( "qt_"+QLocale::system().name(), sdir );
    if( !ret ) {
        qDebug()<<"load qt language pack fail";
    }
    a.installTranslator( &trans );

    QFont font  = a.font();
    font.setPointSize( 12 );
    a.setFont(font);
    //a.setFont(QApplication::font());    
    //  添加代码连接数据库
    QString s_current_path = QApplication::applicationDirPath();
    if( 1 ){
        //要做的其它操作
        DataBaseStructure o_data( "common.db3", "Yfgreat601ms" );
    }
    YFSqlite o_sql;
    o_sql.connect_sqlite( "common.db3", "Yfgreat601ms"  );

    CurllibPort port;
    MainWindow w;
    LoginDialog *pDlg = new LoginDialog( 0, &port );
    if( pDlg->exec() == QDialog::Accepted) {
        w.showMaximized();
    } else {
        return 0;
    }

    return a.exec();
}
