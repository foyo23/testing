/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现配置参数的设置、读取
 */
#include "config.h"
#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QSettings>

Config::Config(QObject *parent) :
    QObject(parent)
{
    QString sdir = ":/res/app.json"; //QCoreApplication::applicationDirPath() + "app.json";
    //QSettings settings(sdir, QSettings::IniFormat);
    //QVariant var = settings.value("Def/UrgentDef");
    QFile file( sdir );

    if (!file.open(QIODevice::ReadOnly))
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
        QJsonValue val = obj.take( "Def" );
        if( val.isObject() ) {
            QJsonObject defObj = val.toObject();
            msDefList.append( defObj.take("UrgentDef").toString() );
            msDefList.append( defObj.take("SeriousDef").toString() );
            msDefList.append( defObj.take("CommonlyDef").toString() );
            msDefList.append( defObj.take("Attention").toString() );
            msDefList.append( defObj.take("Normal").toString() );
        } 

        break;
    }

    msLoginUrl = "";
    msHostUrl = "";
    mnAutoLogin = 0;
}

QStringList Config::getDefList()
{
    return msDefList;
}

void Config::writeAutoLogin(int nAutoLogin)
{
    QString sdir = QCoreApplication::applicationDirPath() + "/app.conf";
    QSettings settings(sdir, QSettings::IniFormat);
    QJsonDocument doc;
    QJsonObject obj;

    obj.insert( "LoginUrl", msLoginUrl );
    obj.insert( "AutoLogin", mnAutoLogin );
    doc.setObject( obj );
    settings.setValue( "config", doc.toJson() );

    mnAutoLogin = nAutoLogin;
}

int Config::getAutoLogin()
{
    return mnAutoLogin;
}

QString Config::getHostUrl()
{
    if( msHostUrl.isEmpty() ) {
        getLoginUrl();
    }
    return msHostUrl;
}

QString Config::getLoginUrl()
{
    if( !msLoginUrl.isEmpty() ) {
        return msLoginUrl;
    }

    QString sdir = QCoreApplication::applicationDirPath() + "/app.conf";
    QSettings settings(sdir, QSettings::IniFormat);
    QJsonDocument doc = QJsonDocument::fromJson( settings.value("config").toByteArray() );

    if( !doc.isNull() && !doc.isEmpty() ) {
        if( doc.isObject() ) {
            QJsonObject obj = doc.object();
            if ( obj.contains( "HostUrl" ) ) {
                msHostUrl = obj.take( "HostUrl" ).toString();
            }
            if ( obj.contains( "LoginUrl" ) ) {
                msLoginUrl = msHostUrl + obj.take( "LoginUrl" ).toString();
            }
            if ( obj.contains( "AutoLogin" ) ) {
                mnAutoLogin = obj.take( "AutoLogin" ).toBool();
            }
        }
    }

    if( msLoginUrl.isEmpty() ) {
        msHostUrl = "http://192.168.1.160:3000";
        msLoginUrl = msHostUrl + "/api/users";
        mnAutoLogin = 0;
    }
    return msLoginUrl;
}
