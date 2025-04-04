QT += testlib network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += coverage
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -fprofile-arcs -ftest-coverage

TEMPLATE = app

SOURCES +=  tst_clienttests.cpp
INCLUDEPATH += ../../Client
HEADERS += ../../Client/client.h
SOURCES += ../../Client/client.cpp
