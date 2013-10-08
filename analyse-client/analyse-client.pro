#-------------------------------------------------
#
# Project created by QtCreator 2013-06-17T17:26:52
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = analyse-client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    devtreeview.cpp \
    filterview.cpp \
    queryresulttable.cpp \
    irimageview.cpp \
    imagelabel.cpp \
    config.cpp \
    deflabel.cpp \
    logindialog.cpp \
    curllibport.cpp \
    impshootresultdlg.cpp \
    exportsettingdlg.cpp \
    exportprogressdlg.cpp \
    batchdiagdlg.cpp \
    zlib/zutil.c \
    zlib/uncompr.c \
    zlib/trees.c \
    zlib/inftrees.c \
    zlib/inflate.c \
    zlib/inffast.c \
    zlib/infback.c \
    zlib/gzwrite.c \
    zlib/gzread.c \
    zlib/gzlib.c \
    zlib/gzclose.c \
    zlib/deflate.c \
    zlib/crc32.c \
    zlib/compress.c \
    zlib/adler32.c \
    database-structure.cpp \
    yfsqlite.cpp

HEADERS  += mainwindow.h \
    devtreeview.h \
    filterview.h \
    queryresulttable.h \
    irimageview.h \
    imagelabel.h \
    config.h \
    deflabel.h \
    logindialog.h \
    curllibport.h \
    impshootresultdlg.h \
    exportsettingdlg.h \
    exportprogressdlg.h \
    batchdiagdlg.h \
    zlib/zutil.h \
    zlib/zlib.h \
    zlib/zconf.h \
    zlib/trees.h \
    zlib/inftrees.h \
    zlib/inflate.h \
    zlib/inffixed.h \
    zlib/inffast.h \
    zlib/gzguts.h \
    zlib/deflate.h \
    zlib/crc32.h \
    database-structure.h \
    yfsqlite.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    impshootresultdlg.ui \
    exportsettingdlg.ui \
    exportprogressdlg.ui \
    batchdiagdlg.ui
TRANSLATIONS = analyse_client_zh_CN.ts

RESOURCES += \
    analyserec.qrc
