#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T09:23:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ezdict
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
QMAKE_LFLAGS += -ljsoncpp

RESOURCES +=
