#-------------------------------------------------
#
# Project created by QtCreator 2014-04-27T18:45:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TX
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rc4.cpp \
    RSA.cpp \
    BigInt.cpp \
    exceptions.cpp

HEADERS  += mainwindow.h \
    rc4.h \
    RSA.h \
    BigInt.h \
    exceptions.h

FORMS    += mainwindow.ui

CONFIG   += RTTI
