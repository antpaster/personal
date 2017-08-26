#-------------------------------------------------
#
# Project created by QtCreator 2013-09-03T10:19:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArtifNeuralNetwork
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    perceptron.cpp \
    neuralnetw.cpp

HEADERS  += mainwindow.h \
    perceptron.h \
    neuralnetw.h

FORMS    += mainwindow.ui
