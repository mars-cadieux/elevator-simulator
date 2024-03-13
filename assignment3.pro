QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audiosystem.cpp \
    building.cpp \
    controller.cpp \
    display.cpp \
    door.cpp \
    ecs.cpp \
    ecsthread.cpp \
    elevator.cpp \
    elevatorbutton.cpp \
    elevatorui.cpp \
    floorbutton.cpp \
    floorrequest.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    audiosystem.h \
    building.h \
    controller.h \
    defs.h \
    display.h \
    door.h \
    ecs.h \
    ecsthread.h \
    elevator.h \
    elevatorbutton.h \
    elevatorui.h \
    floorbutton.h \
    floorrequest.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
