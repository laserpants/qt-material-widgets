QT += core gui widgets
TEMPLATE = app
SOURCES = mainwindow.cpp \
    main.cpp \
    avatarsettingseditor.cpp \
    badgesettingseditor.cpp \
    checkboxsettingseditor.cpp \
    fabsettingseditor.cpp \
    raisedbuttonsettingseditor.cpp \
    flatbuttonsettingseditor.cpp \
    iconbuttonsettingseditor.cpp
HEADERS = mainwindow.h \
    avatarsettingseditor.h \
    badgesettingseditor.h \
    checkboxsettingseditor.h \
    fabsettingseditor.h \
    raisedbuttonsettingseditor.h \
    flatbuttonsettingseditor.h \
    iconbuttonsettingseditor.h
LIBS += ../components/libcomponents.a
INCLUDEPATH += ../components/
TARGET = ../examples-exe

RESOURCES += \
    examples.qrc

FORMS += \
    avatarsettingsform.ui \
    badgesettingsform.ui \
    checkboxsettingsform.ui \
    fabsettingsform.ui \
    flatbuttonsettingsform.ui \
    iconbuttonsettingsform.ui
