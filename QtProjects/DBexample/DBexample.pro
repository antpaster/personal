#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T11:34:06
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBexample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tabledatagateway.cpp \
    servicelayer.cpp

HEADERS  += mainwindow.h \
    database.h \
    tabledatagateway.h \
    servicelayer.h
