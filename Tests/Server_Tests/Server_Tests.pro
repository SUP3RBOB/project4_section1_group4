QT += testlib network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_servertests.cpp
INCLUDEPATH += ../../Server
HEADERS += ../../Server/server.h
SOURCES += ../../Server/server.cpp
