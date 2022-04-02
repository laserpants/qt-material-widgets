QT += core gui widgets
TEMPLATE = app
CONFIG += c++11

TARGET = examples-exe

SOURCES += mainwindow.cpp \
    main.cpp \
    avatarsettingseditor.cpp \
    badgesettingseditor.cpp \
    checkboxsettingseditor.cpp \
    fabsettingseditor.cpp \
    plugindemoform.cpp \
    raisedbuttonsettingseditor.cpp \
    flatbuttonsettingseditor.cpp \
    iconbuttonsettingseditor.cpp \
    progresssettingseditor.cpp \
    circularprogresssettingseditor.cpp \
    slidersettingseditor.cpp \
    radiobuttonsettingseditor.cpp \
    togglesettingseditor.cpp \
    textfieldsettingseditor.cpp \
    tabssettingseditor.cpp \
    snackbarsettingseditor.cpp \
    dialogsettingseditor.cpp \
    drawersettingseditor.cpp \
    scrollbarsettingseditor.cpp \
    appbarsettingseditor.cpp \
    autocompletesettingseditor.cpp \
    menusettingseditor.cpp
HEADERS += mainwindow.h \
    avatarsettingseditor.h \
    badgesettingseditor.h \
    checkboxsettingseditor.h \
    fabsettingseditor.h \
    plugindemoform.h \
    raisedbuttonsettingseditor.h \
    flatbuttonsettingseditor.h \
    iconbuttonsettingseditor.h \
    progresssettingseditor.h \
    circularprogresssettingseditor.h \
    slidersettingseditor.h \
    radiobuttonsettingseditor.h \
    togglesettingseditor.h \
    textfieldsettingseditor.h \
    tabssettingseditor.h \
    snackbarsettingseditor.h \
    dialogsettingseditor.h \
    drawersettingseditor.h \
    scrollbarsettingseditor.h \
    appbarsettingseditor.h \
    autocompletesettingseditor.h \
    menusettingseditor.h

FORMS += \
    avatarsettingsform.ui \
    badgesettingsform.ui \
    checkboxsettingsform.ui \
    fabsettingsform.ui \
    flatbuttonsettingsform.ui \
    iconbuttonsettingsform.ui \
    plugindemoform.ui \
    progresssettingsform.ui \
    circularprogresssettingsform.ui \
    slidersettingsform.ui \
    snackbarsettingsform.ui \
    radiobuttonsettingsform.ui \
    togglesettingsform.ui \
    textfieldsettingsform.ui \ 
    dialogsettingsform.ui \
    drawersettingsform.ui \
    scrollbarsettingsform.ui \
    appbarsettingsform.ui \
    tabssettingsform.ui

RESOURCES += \
    ../components/material_res.qrc \
    examples.qrc

OBJECTS_DIR = $$PWD/../../qt-material-widgets-build/examples/build/obj
MOC_DIR = $$PWD/../../qt-material-widgets-build/examples/build/moc
RCC_DIR = $$PWD/../../qt-material-widgets-build/examples/build/qrc
UI_DIR = $$PWD/../../qt-material-widgets-build/examples/build/ui
DESTDIR = $$PWD/../../qt-material-widgets-build/examples/bin

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../qt-material-widgets-build/components/lib/ -lqt-material-widget
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../qt-material-widgets-build/components/lib/ -lqt-material-widgetd
else:unix:!macx: LIBS += -L$$PWD/../../qt-material-widgets-build/components/lib/ -lqt-material-widget

INCLUDEPATH += $$PWD/../components
DEPENDPATH += $$PWD/../../qt-material-widgets-build/components
