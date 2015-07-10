#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T21:00:20
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET          = Prototype
TEMPLATE        = app
QMAKE_CXXFLAGS  += -std=c++11
QMAKE_LFLAGS    += -static


SOURCES += main.cpp \
    Core/computer.cpp \
    Core/hero.cpp \
    Core/maze.cpp \
    Core/player.cpp \
    Core/point.cpp \
    Core/world.cpp \
    Application/button.cpp \
    Application/mainwindow.cpp \
    Application/screen.cpp \
    Core/Generator/generator.cpp

HEADERS  += \
    Core/computer.h \
    Core/hero.h \
    Core/maze.h \
    Core/player.h \
    Core/point.h \
    Core/world.h \
    Application/button.h \
    Application/mainwindow.h \
    Application/screen.h \
    Core/exception.h \
    Core/Generator/generator.h \
    Core/direction.h \
    Core/light.h

DISTFILES +=
