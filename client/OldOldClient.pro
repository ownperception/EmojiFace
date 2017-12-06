QT += core
QT += gui
QT += widgets
QT += network

TARGET = OldOldClient
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myclient.cpp \
    user.cpp

HEADERS += \
    myclient.h \
    user.h

