#-------------------------------------------------
#
# Project created by QtCreator 2015-02-16T18:36:01
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game_board
TEMPLATE = app

INCLUDEPATH += /usr/local/include

LIBS += -L "/usr/local/lib" -lsfml-audio -lsfml-system -lsfml-graphics -lsfml-window

SOURCES +=\
        board_widget.cpp \
    ../Controller.cpp \
    ../main.cpp \
    ../memory_handler.cpp \
    ../songinfoparser.cpp \
    ../qdsleep.cpp \
    qt_main.cpp

HEADERS  += board_widget.h \
    ../beat_sequence.h \
    ../Controller.h \
    ../memory_handler.h \
    ../songinfoparser.h \
    ../qdsleep.h

DISTFILES += \
    button_animation.qml

CONFIG += c++11 lsfml-audio lsfml-system lsfml-graphics lsfml-window
