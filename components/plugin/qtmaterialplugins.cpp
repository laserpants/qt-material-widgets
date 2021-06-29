#include "qtmaterialplugins.h"
#include "materialtoggleplugin.h"

QtMaterialPlugins::QtMaterialPlugins(QObject *parent) : QObject(parent)
{
    m_plugins << new MaterialTogglePlugin(this);
}

QList<QDesignerCustomWidgetInterface*> QtMaterialPlugins::customWidgets() const {
    return m_plugins;
}
