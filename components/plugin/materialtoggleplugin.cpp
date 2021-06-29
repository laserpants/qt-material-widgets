#include "materialtoggleplugin.h"
#include "qtmaterialtoggle.h"
#include <QtPlugin>

MaterialTogglePlugin::
MaterialTogglePlugin(QObject* parent) :
    QObject(parent),
    initialized(false)
{
}

QString MaterialTogglePlugin::
name() const
{
    return "Material Toggle";
}

QString MaterialTogglePlugin::
group() const
{
    return tr("Qt Meterial Widgets");
}

QString MaterialTogglePlugin::
toolTip() const
{
    return tr("Material toggle button");
}

QString MaterialTogglePlugin::
whatsThis() const
{
    return tr("Material toggle button");
}

QString MaterialTogglePlugin::
includeFile() const
{
    return "qtmaterialtoggle.h";
}

QIcon MaterialTogglePlugin::
icon() const
{
    return QIcon();
}

bool MaterialTogglePlugin::
isContainer() const
{
    return false;
}

QWidget * MaterialTogglePlugin::
createWidget(QWidget *parent)
{
    return new QtMaterialToggle(parent);
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
Q_EXPORT_PLUGIN2(MaterialTogglePlugin, MaterialTogglePlugin)
#endif
