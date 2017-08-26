TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    triangle.c \
    vect2rd.c \
    scalar.c \
    vect_lib.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    triangle.h \
    figures.h \
    vect2rd.h \
    scalar.h \
    vect_lib.h

