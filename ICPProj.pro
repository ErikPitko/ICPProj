TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    block.cpp \
    drawableobject.cpp \
    point2d.cpp \
    port.cpp \
    link.cpp \
    myrect.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    block.h \
    drawableobject.h \
    point2d.h \
    EBlock.h \
    link.h \
    port.h \
    myrect.h

