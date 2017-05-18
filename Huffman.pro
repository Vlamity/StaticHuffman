TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tree.cpp \
    countsymbols.cpp \
    coding.cpp

HEADERS += \
    tree.h \
    countsymbols.h \
    coding.h
