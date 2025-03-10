QT += testlib sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += coverage
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -fprofile-arcs -ftest-coverage

TEMPLATE = app

SOURCES +=  tst_databasetests.cpp
INCLUDEPATH += ../../Server
HEADERS += ../../Server/database.h
SOURCES += ../../Server/database.cpp
