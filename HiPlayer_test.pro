#-------------------------------------------------
#
# Project created by QtCreator 2017-12-19T16:32:58
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HiPlayer_test
TEMPLATE = app

#RC_ICONS = logo.ico
RC_ICONS = HiLogo4.ico
CONFIG += c++11
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp \
    hiButton.cpp \
    aboutDialog.cpp \
    hiLabel.cpp \
    lrcLabel.cpp \
    hiLrcWidget.cpp \
    hiVolBotton.cpp \
    singleApp.cpp \
    main1.cpp \
    nofocusdelegate.cpp \
    network.cpp \
    hiplayer.cpp \
    miniWindow.cpp \
    playslider.cpp

HEADERS  += widget.h \
    hiButton.h \
    aboutDialog.h \
    hiLabel.h \
    lrcLabel.h \
    hiLrcWidget.h \
    hiVolBotton.h \
    singleApp.h \
    songinfo.h \
    nofocusdelegate.h \
    network.h \
    hiplayer.h \
    miniWindow.h \
    playslider.h

RESOURCES += \
    icon.qrc
