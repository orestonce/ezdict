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
    golib.cpp

HEADERS  += mainwindow.h \
    golib.h

FORMS    += mainwindow.ui

RC_FILE += \
    app.rc

LIBS += -L$$PWD -lgolib-impl

DISTFILES += \
    ezdict.ico \
    app.rc
