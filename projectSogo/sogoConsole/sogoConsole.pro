QT += core
QT -= gui

CONFIG += c++11

TARGET = sogoConsole
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../include/* \

HEADERS  += ../include/core/* \

SOURCES += ../main.cpp \
        ../src/core/* \
