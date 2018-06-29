#-------------------------------------------------
#
# Project created by QtCreator 2018-06-26T16:34:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_lottery
TEMPLATE = app

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
        mainwindow.cpp \
    cljlotteryuseritem.cpp \
    cljlotteryuser.cpp \
    cljlotteryresultview.cpp \
    cljlotteryanimationview.cpp \
    cljlotterymanager.cpp \
    cljlotteryresultdialog.cpp \
    cljshadowwidget.cpp \
    cljdialog.cpp \
    cljshadowengine.cpp

HEADERS  += mainwindow.h \
    cljlotteryuseritem.h \
    cljlotteryuser.h \
    cljlotteryresultview.h \
    cljlotteryanimationview.h \
    cljlotterymanager.h \
    cljlotteryresultdialog.h \
    cljshadowwidget.h \
    cljdialog.h \
    cljshadowengine.h

FORMS    += mainwindow.ui \
    cljlotteryresultdialog.ui

RESOURCES += \
    source.qrc
