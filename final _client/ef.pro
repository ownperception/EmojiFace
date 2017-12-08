#-------------------------------------------------
#
# Project created by QtCreator 2017-11-28T18:12:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ef
TEMPLATE = app

INCLUDEPATH +=/usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_features2d -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_video -lopencv_videoio -lopencv_videostab
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    emoji.cpp \
    score.cpp \
    game.cpp \
    face.cpp \
    timer.cpp \
    mainwindow.cpp \
    user.cpp

HEADERS += \
    emoji.h \
    game.h \
    score.h \
    face.h \
    timer.h \
    mainwindow.h \
    user.h \
    emojiClass.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    res.qrc
QMAKE_CXXFLAGS += -std=gnu++14

