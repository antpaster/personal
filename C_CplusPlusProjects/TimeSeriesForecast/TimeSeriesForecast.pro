TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    sma.cpp \
    ema.cpp \
    resampling.cpp \
    commontsdata.cpp

HEADERS += \
    sma.h \
    commontsdata.h \
    ema.h \
    resampling.h
