#-------------------------------------------------
#
# Project created by QtCreator 2015-02-16T18:36:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game_board
TEMPLATE = app


SOURCES += main.cpp\
        board_widget.cpp

HEADERS  += board_widget.h

DISTFILES += \
    button_animation.qml

CONFIG += c++11
