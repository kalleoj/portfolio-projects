QT       += core gui
QT      += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += C:\Users\Omistaja\eigen-3.4.0\eigen-3.4.0

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    avatar.cpp \
    customexception.cpp \
    flyingavatar.cpp \
    game.cpp \
    gamedisplay.cpp \
    gameobject.cpp \
    grass.cpp \
    learningagent.cpp \
    main.cpp \
    mainwindow.cpp \
    point.cpp \
    solidgameobject.cpp \
    spacecube.cpp

HEADERS += \
    SurroundingsAware.hh \
    avatar.hh \
    customexception.hh \
    flyingavatar.hh \
    game.hh \
    gamedisplay.hh \
    gameobject.hh \
    grass.hh \
    learningagent.hh \
    mainwindow.hh \
    point.hh \
    solidgameobject.hh \
    spacecube.hh

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
