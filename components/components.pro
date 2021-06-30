QT          += widgets uiplugin designer
CONFIG      += plugin release
TEMPLATE    = lib

TARGET = $$qtLibraryTarget(qt-material-widget)
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

include(link_components.pri)

SOURCES += \
    plugin/qtmaterialplugins.cpp
HEADERS += \
    plugin/plugintemplate.h \
    plugin/qtmaterialplugins.h
