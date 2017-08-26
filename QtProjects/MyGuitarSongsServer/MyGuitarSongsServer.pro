#-------------------------------------------------
#
# Project created by QtCreator 2013-09-20T08:52:58
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyGuitarSongsServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    artistaddingdialog.cpp \
    songaddingdialog.cpp \
    filebrowserdialog.cpp

HEADERS  += mainwindow.h \
    artistaddingdialog.h \
    songaddingdialog.h \
    filebrowserdialog.h

FORMS    += mainwindow.ui \
    artistaddingdialog.ui \
    songaddingdialog.ui \
    filebrowserdialog.ui
