TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    Conexion.cpp

HEADERS += \
    Cliente.h \
    Conexion.h

LIBS += -lws2_32
