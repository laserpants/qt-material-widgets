#include "qtmaterialtabwidgetextensionfactory.h"
#include "qtmaterialtabwidgetcontainerextension.h"
#include "qtmaterialtabwidget.h"

QtMaterialTabWidgetExtensionFactory::QtMaterialTabWidgetExtensionFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{}
//! [0]

//! [1]
QObject *QtMaterialTabWidgetExtensionFactory::createExtension(QObject *object,
                                                          const QString &iid,
                                                          QObject *parent) const
{
    QtMaterialTabWidget *widget = qobject_cast<QtMaterialTabWidget*>(object);

    if (widget && (iid == Q_TYPEID(QDesignerContainerExtension)))
        return new QtMaterialTabWidgetContainerExtension(widget, parent);
    return nullptr;
}
