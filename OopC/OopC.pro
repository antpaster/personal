TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    vect2rd.c \
    scalar.c \
    vect3rd.c \
    matr3x3.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    vect2rd.h \
    scalar.h \
    vect_lib.h \
    vect3rd.h \
    matr3x3.h

