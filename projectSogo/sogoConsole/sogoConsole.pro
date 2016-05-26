QT += core
QT -= gui

CONFIG += c++11

TARGET = sogoConsole
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../include/core/ \
                ../include/utility/ \

HEADERS  += ../include/core/*

SOURCES += \
        ../src/core/* \
        ../src/utility/* \
        ../tests/* \
           main.cpp
