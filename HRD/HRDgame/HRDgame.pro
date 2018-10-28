#-------------------------------------------------
#
# Project created by QtCreator 2018-09-14T17:26:19
#
#-------------------------------------------------

QT       += core gui
QT       += core gui network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HRDgame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    widget.cpp \
    help.cpp \
    play.cpp \
    rank.cpp \
    menu.cpp \
    dialog.cpp \
    compare.cpp \
    fileOn.cpp \
    load.cpp \
    game.cpp \
    chess.cpp \
    level.cpp \
    user.cpp \
    warn.cpp \
    client.cpp \
    login.cpp \
    cleardialog.cpp \
    bgm.cpp \
    cleardialog1.cpp \
    levelrank.cpp \
    solution.cpp

HEADERS += \
    widget.h \
    help.h \
    play.h \
    rank.h \
    menu.h \
    dialog.h \
    fileOn.h \
    load.h \
    chess.h \
    level.h \
    user.h \
    game.h \
    warn.h \
    client.h \
    login.h \
    cleardialog.h \
    bgm.h \
    cleardialog1.h \
    levelrank.h \
    solution.h

FORMS += \
    help.ui \
    play.ui \
    rank.ui \
    menu.ui \
    dialog.ui \
    warn.ui \
    client.ui \
    login.ui \
    cleardialog.ui \
    cleardialog1.ui \
    levelrank.ui \
    solution.ui

RESOURCES += \
    picture.qrc

SUBDIRS += \
    ../../attention/attention.pro
