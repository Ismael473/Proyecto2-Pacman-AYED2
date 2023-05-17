#-------------------------------------------------
#
# Project created by QtCreator 2023-05-16T19:08:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProyectoPacman
TEMPLATE = app


SOURCES += main.cpp \
    Game.cpp \
    Enemy.cpp \
    PathGrid.cpp \
    Tree.cpp \
    Node.cpp \
    Graph.cpp \
    Edge.cpp \
    Mapeo.cpp \
    Player.cpp \
    Health.cpp

HEADERS  += \
    Game.h \
    Enemy.h \
    Tree.h \
    Node.h \
    Graph.h \
    Edge.h \
    PathGrid.h \
    Player.h \
    Mapeo.h \
    Health.h

FORMS    +=
