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
                ../include/utility/ \

HEADERS +=      ../include/core/* \
                ../include/gui/* \
                ../include/utility/* \
    ../include/gui/GameView2D.h \
    ../include/Subject.h \
    ../include/IObserver.h

SOURCES +=      main.cpp \
                ../src/core/* \
                ../src/gui/*  \
                ../src/utility/* \

