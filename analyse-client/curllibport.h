#ifndef CURLLIBPORT_H
#define CURLLIBPORT_H

#include <QObject>
#include <QLibrary>
#include "./libcurl_inc/curl.h"
#include "./libcurl_inc/easy.h"
#include "config.h"

struct MemoryStruct {
  char *memory;
  size_t size;
};

typedef enum {
    REQUEST_METHOD_GET,
    REQUEST_METHOD_POST
}REQUEST_METHOD_E;
class CurllibPort : public QObject
{
    Q_OBJECT
public:
    explicit CurllibPort(QObject *parent = 0);
    ~CurllibPort();
    static size_t writer(void *contents, size_t size, size_t nmemb, void *userp);
    bool login( QString sEmail, QString sPass, int nAutoLogin );
    bool sendRequest( QString sUrl, REQUEST_METHOD_E method, QString sParam );
    MemoryStruct getResponseContent();
    void freeResponseContent( MemoryStruct mem );
private:
    Config config;
    QLibrary *mpLibcurl;
    CURL * mpCurl;
    bool mbInited;
    bool mbLogined;
    QString msToken;
    typedef CURLcode (*curl_global_init)(long);
    typedef CURL* (*curl_easy_init)();
    typedef CURLcode (*curl_easy_setopt)(CURL *curl, CURLoption option, ...);
    typedef CURLcode (*curl_easy_perform)(CURL *curl);
    typedef void (*curl_easy_cleanup)(CURL *curl);
    typedef struct curl_slist *(*curl_slist_append)(struct curl_slist *, const char *);
    typedef void (*curl_slist_free_all)(struct curl_slist *);
    typedef void (*curl_global_cleanup)(void);
    typedef CURLcode (*curl_easy_getinfo)(CURL *curl, CURLINFO info, ...);

    curl_global_init mpGlobalInitFun;
    curl_easy_init mpInitFun;
    curl_easy_setopt mpSetoptFun;
    curl_easy_perform mpPerformFun;
    curl_easy_cleanup mpCleanupFun;
    curl_slist_append mpSlistAppendFun;
    curl_slist_free_all mpSlistClear;
    curl_global_cleanup mpGlobalCleanFun;
    curl_easy_getinfo mpGetInfoFun;

    void initLibcurl();
    bool extractToken(const char *pHtml , int nSize);
signals:
    
public slots:
    
};

#endif // CURLLIBPORT_H
