#-------------------------------------------------
#
# Project created by QtCreator 2016-08-27T15:45:47
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OOP_Term_Project_PVZ
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paireliminate.cpp \
    logic.cpp \
    qplant.cpp \
    qunit.cpp \
    qzombie.cpp \
    qweapon.cpp \
    qsunshine.cpp \
    qinitialinterface.cpp \
    qgamedayinterface.cpp \
    src_plants/qdoublepea.cpp \
    src_plants/qgatlingpea.cpp \
    src_plants/qpeashooter.cpp \
    src_plants/qsnowpea.cpp \
    src_plants/qsunflower.cpp \
    src_plants/qtorchwood.cpp \
    src_plants/qwallnut.cpp \
    src_weapons/qpeaweapon.cpp \
    qcard.cpp \
    src_cards/qpeashootercard.cpp \
    src_cards/qsnowpeacard.cpp \
    src_cards/qdoublepeacard.cpp \
    src_cards/qgatlingpeacard.cpp \
    src_cards/qsunflowercard.cpp \
    src_cards/qwallnutcard.cpp \
    src_cards/qtorchwoodcard.cpp \
    src_plants/qtallnut.cpp \
    src_cards/qtallnutcard.cpp \
    src_zombies/qcommonzombie.cpp

HEADERS  += mainwindow.h \
    paireliminate.h \
    const.h \
    logic.h \
    qplant.h \
    qunit.h \
    qzombie.h \
    qweapon.h \
    qsunshine.h \
    qinitialinterface.h \
    qgamedayinterface.h \
    src_plants/qdoublepea.h \
    src_plants/qgatlingpea.h \
    src_plants/qpeashooter.h \
    src_plants/qsnowpea.h \
    src_plants/qsunflower.h \
    src_plants/qtorchwood.h \
    src_plants/qwallnut.h \
    src_weapons/qpeaweapon.h \
    qcard.h \
    src_cards/qpeashootercard.h \
    src_cards/qsnowpeacard.h \
    src_cards/qdoublepeacard.h \
    src_cards/qgatlingpeacard.h \
    src_cards/qsunflowercard.h \
    src_cards/qwallnutcard.h \
    src_cards/qtorchwoodcard.h \
    src_plants/qtallnut.h \
    src_cards/qtallnutcard.h \
    src_zombies/qcommonzombie.h

FORMS    += mainwindow.ui \
    paireliminate.ui \
    qinitialinterface.ui \
    qgamedayinterface.ui
