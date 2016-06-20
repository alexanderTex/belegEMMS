# /===============================================\
#
# Sogo Widget-Application
#
# \===============================================/

QT       += core gui
            opengl


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sogoApp
TEMPLATE = app
TRANSLATIONS += sogoapp_de.ts \
                sogoapp_en.ts

INCLUDEPATH +=  ../include/core/ \
                ../include/gui/ \
                ../include/utility/ \

HEADERS +=      ../include/core/* \
                ../include/gui/* \
                ../include/utility/* \
                ../include/Subject.h \
                ../include/IObserver.h

SOURCES +=      main.cpp \
                ../src/core/* \
                ../src/gui/*  \
                ../src/utility/*

RESOURCES += \
    ressources.qrc

