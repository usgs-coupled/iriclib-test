######################################################################
# Automatically generated by qmake (2.01a) ? 11 5 22:15:18 2014
######################################################################

TEMPLATE = app
TARGET = test13
CONFIG += debug_and_release
CONFIG += console

include( ../../../paths.pri )

QT -= core

LIBS += -liriclib

win32{
LIBS += -lcgnsdll
}
unix{
LIBS += -lcgns
}

# Input

SOURCES += test13.c
