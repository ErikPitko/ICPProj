#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T16:47:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICPProj
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    block.cpp \
    drawableobject.cpp \
    link.cpp \
    myrect.cpp \
    point2d.cpp \
    port.cpp

HEADERS  += widget.h \
    block.h \
    drawableobject.h \
    EBlock.h \
    link.h \
    myrect.h \
    point2d.h \
    port.h

FORMS    += widget.ui
