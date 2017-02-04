TEMPLATE = app
CONFIG += console c++14 qt
CONFIG -= app_bundle
QT+=xml

SOURCES += main.cpp \
    graph.cpp \
    algorithms.cpp \
    commontypes.cpp \
    labeledgraph.cpp

HEADERS += \
    graph.h \
    algorithms.h \
    commontypes.hpp \
    labeledgraph.h \
    iserializable.h
