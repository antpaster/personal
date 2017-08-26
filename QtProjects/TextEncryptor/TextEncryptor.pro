#-------------------------------------------------
#
# Project created by QtCreator 2013-08-26T15:29:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEncryptor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    encryptingalg.cpp

HEADERS  += mainwindow.h \
    encryptingalg.h

FORMS    += mainwindow.ui
