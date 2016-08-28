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
    logic.cpp

HEADERS  += mainwindow.h \
    paireliminate.h \
    const.h \
    logic.h

FORMS    += mainwindow.ui \
    paireliminate.ui
