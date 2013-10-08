/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现libcurl接口的封装及登录功能的实现
 */
#include "curllibport.h"
#include <QDebug>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

static MemoryStruct mMemStruct;
CurllibPort::CurllibPort(QObject *parent) :
    QObject(parent)
{
    mbLogined = false;
    initLibcurl();
}

CurllibPort::~CurllibPort()
{
    if( mpLibcurl && mpLibcurl->isLoaded() ) {
        if( mpCurl && mpCleanupFun ) {
            mpCleanupFun( mpCurl );
        }
        mpGlobalCleanFun();
        mpLibcurl->unload();
    }
}

size_t CurllibPort::writer(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == 0) {
        qDebug() << "not enough memory (realloc returned NULL)";
        return 0;
    }
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

bool CurllibPort::login(QString sEmail, QString sPass, int nAutoLogin)
{
    if( config.getAutoLogin() != nAutoLogin ) {
        config.writeAutoLogin( nAutoLogin );
    }
    if( !mbInited ) {
        return false;
    }
    if( mbLogined ) {
        qDebug() << "Had login";
        return true;
    }

    QString sUrl = config.getLoginUrl();
    if( sUrl == 0 || sUrl.isEmpty() ) {
        qDebug() << "config.getLoginUrl() is Empty";
        return false;
    }

    CURLcode code = CURLE_OK;
    char errorBuffer[CURL_ERROR_SIZE];
    QString sErr;

    mMemStruct.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */
    if( mMemStruct.memory == 0 ) {
        qDebug() << "not enough memory (malloc(1) returned NULL)";
        return false;
    }
    mMemStruct.size = 0;
    //struct curl_slist *chunk = 0;
    while( CURLE_OK == code ) {
        code = mpSetoptFun(mpCurl, CURLOPT_ERRORBUFFER, errorBuffer);
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set error buffer [%1]").arg(code);
            break;
        }
        //chunk = curl_slist_append(chunk, "api_session_token: gzip, deflate");
        code = mpSetoptFun(mpCurl, CURLOPT_TIMEOUT, 120);
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set CURLOPT_TIMEOUT [%1]").arg(code);
            break;
        }

        /*code = mpSetoptFun( mpCurl,CURLOPT_POST, 0 );
        if (code != CURLE_OK)  {
            break;
        }*/

        mpSetoptFun(mpCurl, CURLOPT_VERBOSE, 1L);
        code = mpSetoptFun( mpCurl, CURLOPT_URL, sUrl.toUtf8().constData() );
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set URL [%1]").arg(code);
            break;
        }
        /*code = mpSetoptFun(mpCurl, CURLOPT_FOLLOWLOCATION, 1);
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set redirect option [%1]").arg(code);
            break;
        }*/
        code = mpSetoptFun(mpCurl, CURLOPT_WRITEFUNCTION, writer);
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set writer [%1]").arg(code);
            break;
        }
        code = mpSetoptFun(mpCurl, CURLOPT_WRITEDATA, (void *)&mMemStruct);
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set write data [%1]").arg(code);
            break;
        }

        /*code = mpSetoptFun(mpCurl, CURLOPT_COOKIEFILE, "");
           if (code != CURLE_OK)  {
               break;
           }*/
        code = mpSetoptFun(mpCurl, CURLOPT_COOKIEJAR, "./cookie.txt");
        if (code != CURLE_OK)  {
            break;
        }
        code = mpSetoptFun(mpCurl, CURLOPT_COOKIEFILE, "./cookie.txt");
        if (code != CURLE_OK)  {
            break;
        }

        //https use options
#ifdef SKIP_PEER_VERIFICATION
        mpSetoptFun(mpCurl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
#ifdef SKIP_HOSTNAME_VERIFICATION
        mpSetoptFun(mpCurl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

        long retcode = 0;
        /*code = mpPerformFun( mpCurl );
        if (code != CURLE_OK)  {
            sErr = QString("Failed to perform [%1]").arg( code );
            break;
        }

        code = mpGetInfoFun(mpCurl, CURLINFO_RESPONSE_CODE, &retcode);
        if (code != CURLE_OK)  {
            break;
        }
        qDebug() << "Get Login resp_code=" << retcode;
        if( retcode != 200 ) {
            if( retcode > 200  && retcode < 400 ) {
                mbLogined = true;
            }
            break;
        }

        //Post operation
        extractToken( mMemStruct.memory );
        if( msToken.isEmpty() ) {
            qDebug() << "Token is empty.";
            break;
        }
        qDebug() << "Token=" << msToken;
        */
        code = mpSetoptFun( mpCurl,CURLOPT_POST, 1 );
        if (code != CURLE_OK)  {
            break;
        }
        QString sPostFields;
        /*sPostFields.append( "authenticity_token=" );
        sPostFields.append( msToken );
        sPostFields.append( "&" );
        sPostFields.append( "user[email]=" );
        sPostFields.append( sEmail );
        sPostFields.append( "&" );
        sPostFields.append( "user[password]=" );
        sPostFields.append( sPass );
        sPostFields.append( "&" );
        sPostFields.append( "user[smscode]=" );
        sPostFields.append( "&" );
        sPostFields.append( "user[remember_me]=" );
        sPostFields.append( QString::number(nAutoLogin) );*/
        //email={ :email }&password={ :password }
        sPostFields.append( "email=" );
        sPostFields.append( sEmail );
        sPostFields.append( "&" );
        sPostFields.append( "password=" );
        sPostFields.append( sPass );

        QByteArray ba = sPostFields.toLatin1();
        //ba = ba.toPercentEncoding("=&");
        //ba = "utf8=%E2%9C%93&" + ba + "&commit=%E7%99%BB%E9%99%86";
        const char *pFields = ba.constData();

        qDebug() << pFields;
        code = mpSetoptFun( mpCurl, CURLOPT_POSTFIELDS, pFields );
        if (code != CURLE_OK)  {
            break;
        }
        code = mpPerformFun( mpCurl );
        if (code != CURLE_OK)  {
            sErr = QString("Failed to perform [%1]").arg( code );
            break;
        }

        code = mpGetInfoFun(mpCurl, CURLINFO_RESPONSE_CODE, &retcode);
        if (code != CURLE_OK)  {
            break;
        }
        qDebug() << "Post login resp_code=" << retcode;
        /*if( retcode != 200 ) {
            if( retcode > 200  && retcode < 400 ) {
                mbLogined = true;
            }
            break;
        }*/

        qDebug() << "Perform finish.";
        break;
    }

    mbLogined = false;
    //mpSlistClear( chunk );
    if (code != CURLE_OK)  {
        qDebug()<<sErr;
        qDebug() << errorBuffer;        
    } else {
        if( extractToken( mMemStruct.memory, (int)mMemStruct.size ) ) {
            mbLogined = true;
        }

        /*QString sTmp;

        if( mMemStruct.memory && mMemStruct.size > 0 ) {
            QTextCodec *defaultCodec = QTextCodec::codecForName( "UTF-8" );
            QTextCodec * codec = QTextCodec::codecForHtml( mMemStruct.memory, defaultCodec );
            sTmp = codec->toUnicode( mMemStruct.memory );
        }*/
    }

    if(mMemStruct.memory) {
        free(mMemStruct.memory);
    }
    return mbLogined;
}

bool CurllibPort::sendRequest(QString sUrl, REQUEST_METHOD_E method, QString sParam)
{
    if( !mbInited ) {
        return false;
    }
    if( !mbLogined ) {
        qDebug() << "Had not login";
        return false;
    }
    if( sUrl == 0 || sUrl.isEmpty() ) {
        qDebug() << "path is Empty";
        return false;
    }
    QString sHost = config.getHostUrl();
    if( sHost.isEmpty() ) {
        qDebug() << "Host is Empty";
        return false;
    }
    sUrl = sHost + sUrl;
    qDebug() << "Request url=" << sUrl;

    CURLcode code = CURLE_OK;
    char errorBuffer[CURL_ERROR_SIZE];
    QString sErr;

    mMemStruct.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */
    if( mMemStruct.memory == 0 ) {
        qDebug() << "not enough memory (malloc(1) returned NULL)";
        return false;
    }
    mMemStruct.size = 0;
    struct curl_slist *chunk = 0;
    QString sToken = "api_session_token:";
    sToken += msToken;
    while( CURLE_OK == code ) {
        code = mpSetoptFun(mpCurl, CURLOPT_ERRORBUFFER, errorBuffer);
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set error buffer [%1]").arg(code);
            break;
        }
        chunk = mpSlistAppendFun( chunk, sToken.toLatin1().constData() );
        code = mpSetoptFun(mpCurl, CURLOPT_HTTPHEADER, chunk);
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set CURLOPT_HTTPHEADER [%1]").arg(code);
            break;
        }

        code = mpSetoptFun(mpCurl, CURLOPT_TIMEOUT, 120);
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set CURLOPT_TIMEOUT [%1]").arg(code);
            break;
        }

        if ( method == REQUEST_METHOD_GET) {
            code = mpSetoptFun( mpCurl,CURLOPT_POST, 0 );
        } else {
            code = mpSetoptFun( mpCurl,CURLOPT_POST, 1 );
        }
        if (code != CURLE_OK)  {
            break;
        }

        code = mpSetoptFun( mpCurl, CURLOPT_URL, sUrl.toUtf8().constData() );
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set URL [%1]").arg(code);
            break;
        }

        /*code = mpSetoptFun(mpCurl, CURLOPT_WRITEFUNCTION, writer);
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set writer [%1]").arg(code);
            break;
        }
        code = mpSetoptFun(mpCurl, CURLOPT_WRITEDATA, (void *)&mMemStruct);
        if (code != CURLE_OK)  {
            sErr = QString("Failed to set write data [%1]").arg(code);
            break;
        }

        code = mpSetoptFun(mpCurl, CURLOPT_COOKIEJAR, "./cookie.txt");
        if (code != CURLE_OK)  {
            break;
        }
        code = mpSetoptFun(mpCurl, CURLOPT_COOKIEFILE, "./cookie.txt");
        if (code != CURLE_OK)  {
            break;
        }

        //https use options
#ifdef SKIP_PEER_VERIFICATION
        mpSetoptFun(mpCurl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
#ifdef SKIP_HOSTNAME_VERIFICATION
        mpSetoptFun(mpCurl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
*/

        if( !sParam.isEmpty() ) {
            QByteArray ba = sParam.toLatin1();
            //ba = ba.toPercentEncoding("=&");
            //ba = "utf8=%E2%9C%93&" + ba + "&commit=%E7%99%BB%E9%99%86";
            const char *pFields = ba.constData();
            qDebug() << pFields;
            code = mpSetoptFun( mpCurl, CURLOPT_POSTFIELDS, pFields );
            if (code != CURLE_OK)  {
                break;
            }
        }

        code = mpPerformFun( mpCurl );
        if (code != CURLE_OK)  {
            sErr = QString("Failed to perform [%1]").arg( code );
            break;
        }

        long retcode = 0;
        code = mpGetInfoFun(mpCurl, CURLINFO_RESPONSE_CODE, &retcode);
        if (code != CURLE_OK)  {
            break;
        }
        qDebug() << "Request resp_code=" << retcode;
        /*if( retcode != 200 ) {
            if( retcode > 200  && retcode < 400 ) {
                mbLogined = true;
            }
            break;
        }*/

        qDebug() << "Perform finish.";
        break;
    }


    mpSlistClear( chunk );
    if (code != CURLE_OK)  {
        qDebug()<<sErr;
        qDebug() << errorBuffer;
        return false;
    } else {
        return true;
        /*QString sTmp;

        if( mMemStruct.memory && mMemStruct.size > 0 ) {
            QTextCodec *defaultCodec = QTextCodec::codecForName( "UTF-8" );
            QTextCodec * codec = QTextCodec::codecForHtml( mMemStruct.memory, defaultCodec );
            sTmp = codec->toUnicode( mMemStruct.memory );
        }*/
    }
}

void CurllibPort::freeResponseContent(MemoryStruct mem)
{
    if( mem.memory ) {
        free(mem.memory);
        mem.memory = 0;
    }
}

void CurllibPort::initLibcurl()
{
    QString sfn = "./libcurl";//QApplication::applicationDirPath()+"/libcurl";
    mpLibcurl = new  QLibrary(sfn);
    mbInited = false;
    while( true ) {
        if( mpLibcurl && mpLibcurl->load() ) {
            qDebug() << "Load libcurl success.";
        } else {
            qDebug() << "Load libcurl fail.";
            break;
        }

        mpGlobalInitFun = (curl_global_init)mpLibcurl->resolve( "curl_global_init" );
        if( mpGlobalInitFun == 0 ) {
            qDebug() << "Resolve curl_global_init fail.";
            break;
        }
        mpInitFun = (curl_easy_init)mpLibcurl->resolve( "curl_easy_init" );
        if( mpInitFun == 0 ) {
            qDebug() << "Resolve curl_easy_init fail.";
            break;
        }
        mpSetoptFun = (curl_easy_setopt)mpLibcurl->resolve( "curl_easy_setopt" );
        if( mpSetoptFun == 0 ) {
            qDebug() << "Resolve curl_easy_setopt fail.";
            break;
        }
        mpPerformFun = (curl_easy_perform)mpLibcurl->resolve( "curl_easy_perform" );
        if( mpPerformFun == 0 ) {
            qDebug() << "Resolve curl_easy_perform fail.";
            break;
        }
        mpCleanupFun = (curl_easy_cleanup)mpLibcurl->resolve( "curl_easy_cleanup" );
        if( mpCleanupFun == 0 ) {
            qDebug() << "Resolve curl_easy_cleanup fail.";
            break;
        }
        mpSlistAppendFun = (curl_slist_append)mpLibcurl->resolve( "curl_slist_append" );
        if( mpSlistAppendFun == 0 ) {
            qDebug() << "Resolve curl_slist_append fail.";
            break;
        }
        mpSlistClear = (curl_slist_free_all)mpLibcurl->resolve( "curl_slist_free_all" );
        if( mpSlistClear == 0 ) {
            qDebug() << "Resolve curl_slist_free_all fail.";
            break;
        }
        mpGlobalCleanFun = (curl_global_cleanup)mpLibcurl->resolve( "curl_global_cleanup" );
        if( mpGlobalCleanFun == 0 ) {
            qDebug() << "Resolve curl_global_cleanup fail.";
            break;
        }
        mpGetInfoFun = (curl_easy_getinfo)mpLibcurl->resolve( "curl_easy_getinfo" );
        if( mpGetInfoFun == 0 ) {
            qDebug() << "Resolve curl_easy_getinfo fail.";
            break;
        }

        CURLcode code = CURLE_OK;
        code = mpGlobalInitFun( CURL_GLOBAL_DEFAULT );
        if( code != CURLE_OK ) {
            qDebug() << "Call curl_global_init() fail.";
            break;
        }
        mpCurl = mpInitFun();
        if( mpCurl == 0 ) {
            qDebug() << "Call curl_easy_init() fail.";
            break;
        }

        qDebug() << "libcurl inited.";
        mbInited = true;
        break;
    }
}

bool CurllibPort::extractToken(const char *pHtml, int nSize )
{
    msToken.clear();
    QJsonDocument doc = QJsonDocument::fromJson( QByteArray(pHtml, nSize) );
    if( doc.isNull() || doc.isEmpty() ) {
        return false;
    }
    if( doc.isObject() ) {
        QJsonObject obj = doc.object();
        if( obj.contains("session_token") ) {
            msToken = obj.take("session_token").toString();
            qDebug()<< "Get Token=" << msToken;
            return true;
        }
    }
    return false;

    /*while( true ) {
        const char *pMetaContent = strstr( pHtml, "meta content=\"");
        if( pMetaContent == 0 ) {
            break;
        }
        pMetaContent += 14;
        const char *pEnd = strstr( pMetaContent, "/>");
        if( pEnd == 0 ) {
            break;
        }
        const char *pName = strstr( pMetaContent, "name=\"" );
        if( pName == 0 ) {
            break;
        }
        pName += 6;
        if( strncmp( pName, "csrf-token", 10 ) == 0 && pName < pEnd ) {
            const char *pQut = strchr( pMetaContent, '"' );
            if( pQut == 0 ) {
                break;
            }
            int nSize = pQut-pMetaContent;
            char *pMem = (char *)malloc( nSize+ 1);
            if( 0 == pMem ) {
                qDebug() << "not enough memory (malloc returned NULL)";
                break;
            }
            memcpy( pMem, pMetaContent, nSize);
            pMem[nSize] = 0;
            msToken = pMem;
            free(pMem);
            break;
        } else {
            pHtml = pEnd;
        }
    }*/

}


MemoryStruct CurllibPort::getResponseContent()
{
    return mMemStruct;
}
