QT += core
QT -= gui

CONFIG += c++11

TARGET = sogoConsole
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += ../main.cpp \
        ../include/core/* \
        ../src/core/* \
