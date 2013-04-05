#-------------------------------------------------
#
# Project created by QtCreator 2012-06-04T20:20:06
#
#-------------------------------------------------

QT       += core gui

TARGET = convert
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogabout.cpp

HEADERS  += mainwindow.h \
    dialogabout.h

FORMS    += mainwindow.ui \
    dialogabout.ui

#CONFIG += static

QMAKE_LFLAGS += -static-libgcc

#win32 {
#    QMAKE_LFLAGS += -static-libgcc
#    }
