#-------------------------------------------------
#
# Project created by QtCreator 2015-12-19T10:58:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OwnBallistixGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ballcalcresults.cpp \
    ../OwnVersion/VVAballistix/vva_constants.cpp \
    ../OwnVersion/VVAballistix/vva_diffequ.cpp \
    ../OwnVersion/atmosphcalc.cpp \
    ../OwnVersion/atmosphtable.cpp \
    ../OwnVersion/ballarchive.cpp \
    ../OwnVersion/ballcharacts.cpp \
    ../OwnVersion/basic_diffequ.cpp \
    ../OwnVersion/basic_draglaw.cpp \
    ../OwnVersion/generalcalc.cpp \
    ../OwnVersion/typesnconstants.cpp \
    ../OwnVersion/S8_KLballistix/s8_kl_constants.cpp \
    ../OwnVersion/S8_KLballistix/s8_kl_diffequ.cpp \
    ../OwnVersion/butchertables.cpp \
    ../930mBallist/atmosph.cpp \
    ../930mBallist/Support/uni_base_func.cpp \
    ../930mBallist/Support/uni_recode.cpp \
    ../930mBallist/Support/uni_time.cpp \
    ../930mBallist/Support/uni_user_func.cpp \
    ../930mBallist/Support/uni_vector.cpp \
    ../930mBallist/atmosph_calc.cpp \
    ../930mBallist/atmosph_tabl.cpp \
    ../930mBallist/ballarch.cpp \
    ../930mBallist/ballist.cpp \
    ../930mBallist/calccntr.cpp \
    ../930mBallist/codetab.cpp \
    ../930mBallist/draglaw.cpp \
    ../930mBallist/formchar.cpp \
    ../930mBallist/incode.cpp

HEADERS  += mainwindow.h \
    ballcalcresults.h \
    ../gentypes.h \
    ../OwnVersion/VVAballistix/vva_constants.h \
    ../OwnVersion/VVAballistix/vva_diffequ.h \
    ../OwnVersion/atmosph.h \
    ../OwnVersion/ballarchive.h \
    ../OwnVersion/ballcharacts.h \
    ../OwnVersion/basic_diffequ.h \
    ../OwnVersion/basic_draglaw.h \
    ../OwnVersion/generalcalc.h \
    ../OwnVersion/typesnconstants.h \
    ../OwnVersion/S8_KLballistix/s8_kl_constants.h \
    ../OwnVersion/S8_KLballistix/s8_kl_diffequ.h \
    ../OwnVersion/butchertables.h \
    ../930mBallist/ballist_pi.h \
    ../930mBallist/ballist_ui.h \
    ../930mBallist/Support/config_circle.h \
    ../930mBallist/Support/typeSysBGT.h \
    ../930mBallist/Support/uni_base_func.h \
    ../930mBallist/Support/uni_math_def.h \
    ../930mBallist/Support/uni_types.h \
    ../930mBallist/Support/uni_user_types.h \
    ../930mBallist/Support/uni_vector.h \
    ../930mBallist/Support/uni_usr_func.h \
    ../930mBallist/Support/uni_time.h \
    ../930mBallist/Support/uni_recode.h

FORMS    += mainwindow.ui \
    ballcalcresults.ui
