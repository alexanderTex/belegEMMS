# /===============================================\
#
# Sogo Widget-Application
#
# \===============================================/

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sogoApp
TEMPLATE = app


INCLUDEPATH +=  ../include/core/ \
                ../include/gui/ \

HEADERS +=      ../include/core/* \
                ../include/gui/* \

SOURCES +=      ../main.cpp \
                ../src/core/* \
                ../src/gui/*
