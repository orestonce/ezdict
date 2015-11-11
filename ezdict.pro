#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T09:23:09
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ezdict
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbconnection.cpp \
    translation.cpp

HEADERS  += mainwindow.h \
    dbconnection.h \
    translation.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

RC_FILE += \
    app.rc
