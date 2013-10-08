#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QStringList>

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = 0);
    QStringList getDefList();
    void writeAutoLogin(int nAutoLogin);
    int getAutoLogin();
    QString getHostUrl();
    QString getLoginUrl();
signals:
    
public slots:
private:
    QStringList msDefList;
    int mnAutoLogin;
    QString msLoginUrl;
    QString msHostUrl;
};

#endif // CONFIG_H
