#-------------------------------------------------
#
# Project created by QtCreator 2015-06-21T21:02:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InvestmentAnalysisDiploma
TEMPLATE = app


SOURCES += main.cpp\
        inputmodule.cpp \
    cashflow.cpp \
    investmentportfolio.cpp \
    stock.cpp \
    investor.cpp \
    credit.cpp \
    economicalsituation.cpp \
    investmentproject.cpp \
    singleinvprojanalysisresults.cpp \
    singleinvprojanalysismodule.cpp \
    comparenrankinginvprojsmodule.cpp \
    comparenrankinginvprojsresults.cpp \
    invportfoliomakingmodule.cpp \
    limitedcapitalinvportfoliomaking.cpp \
    enoughcapitalinvportfoliomaking.cpp \
    invportfoliomakingresults.cpp

HEADERS  += inputmodule.h \
    cashflow.h \
    investmentportfolio.h \
    stock.h \
    investor.h \
    credit.h \
    economicalsituation.h \
    investmentproject.h \
    database.h \
    singleinvprojanalysisresults.h \
    singleinvprojanalysismodule.h \
    comparenrankinginvprojsmodule.h \
    comparenrankinginvprojsresults.h \
    invportfoliomakingmodule.h \
    limitedcapitalinvportfoliomaking.h \
    enoughcapitalinvportfoliomaking.h \
    invportfoliomakingresults.h

FORMS    += inputmodule.ui \
    singleinvprojanalysisresults.ui \
    singleinvprojanalysismodule.ui \
    comparenrankinginvprojsmodule.ui \
    comparenrankinginvprojsresults.ui \
    invportfoliomakingmodule.ui \
    limitedcapitalinvportfoliomaking.ui \
    enoughcapitalinvportfoliomaking.ui \
    invportfoliomakingresults.ui
