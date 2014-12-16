#-------------------------------------------------
#
# Project created by QtCreator 2014-10-26T15:54:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2labOED
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    all_func.cpp

HEADERS  += mainwindow.h \
    all_func.h

FORMS    += mainwindow.ui
