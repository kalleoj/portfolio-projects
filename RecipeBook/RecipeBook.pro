QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addrecipetab.cpp \
    clickablelabel.cpp \
    datahandler.cpp \
    editablelabel.cpp \
    errorpopup.cpp \
    ingredient.cpp \
    ingredientdisplay.cpp \
    main.cpp \
    mainwindow.cpp \
    recipe.cpp \
    recipedisplay.cpp \
    viewrecipestab.cpp

HEADERS += \
    addrecipetab.hh \
    clickablelabel.hh \
    datahandler.hh \
    editablelabel.hh \
    errorpopup.hh \
    ingredient.hh \
    ingredientdisplay.hh \
    mainwindow.hh \
    recipe.hh \
    recipedisplay.hh \
    searchable.hh \
    viewrecipestab.hh

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \

RESOURCES += \
    resources.qrc
