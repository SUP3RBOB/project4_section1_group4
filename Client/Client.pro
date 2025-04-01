QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network positioning quickwidgets location

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Login.cpp \
    client.cpp \
    main.cpp \

HEADERS += \
    Login.h \
    client.h \

FORMS += \
    Login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += $$files(../Shared/*.h)
SOURCES += $$files(../Shared/*.cpp)
INCLUDEPATH += ../Shared

RESOURCES += \
    qml.qrc
