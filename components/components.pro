QT          += widgets uiplugin designer
CONFIG      += plugin #release
TEMPLATE    = lib

include(link_components.pri)

SOURCES += \
    plugin/qtmaterialplugins.cpp \
    plugin/qtmaterialtabwidgetcontainerextension.cpp \
    plugin/qtmaterialtabwidgetextensionfactory.cpp \
    plugin/qtmaterialtabwidgetplugin.cpp
HEADERS += \
    plugin/plugintemplate.h \
    plugin/qtmaterialplugins.h \
    plugin/qtmaterialtabwidgetcontainerextension.h \
    plugin/qtmaterialtabwidgetextensionfactory.h \
    plugin/qtmaterialtabwidgetplugin.h

TARGET = $$qtLibraryTarget(qt-material-widget)
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

OBJECTS_DIR = $$PWD/../../qt-material-widgets-build/components/build/obj
MOC_DIR = $$PWD/../../qt-material-widgets-build/components/build/moc
RCC_DIR = $$PWD/../../qt-material-widgets-build/components/build/qrc
UI_DIR = $$PWD/../../qt-material-widgets-build/components/build/ui
DESTDIR = $$PWD/../../qt-material-widgets-build/components/lib

