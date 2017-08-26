#-------------------------------------------------
#
# Project created by QtCreator 2013-08-24T01:07:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialFileTransfer
TEMPLATE = app


SOURCES += main.cpp\
    transferserver.cpp \
    transferclient.cpp \
    mainwindow.cpp

HEADERS  += \
    transferserver.h \
    transferclient.h \
    mainwindow.h

FORMS    += \
    mainwindow.ui
