QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network positioning

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Shared/booking.cpp \
    ../Shared/carbooking.cpp \
    ../Shared/planebooking.cpp \
    client.cpp \
    main.cpp \
    mainwindow.cpp
HEADERS += \
    ../Shared/booking.h \
    ../Shared/carbooking.h \
    ../Shared/planebooking.h \
    client.h \
    mainwindow.h
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += $$files(../Shared/*.h)
SOURCES += $$files(../Shared/*.cpp)
