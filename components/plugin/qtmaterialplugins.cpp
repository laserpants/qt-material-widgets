#include "qtmaterialplugins.h"
#include "qtmaterialtabwidgetplugin.h"
QtMaterialPlugins::QtMaterialPlugins(QObject *parent) : QObject(parent)
{
    m_plugins << new MaterialAppBarPlugin(this)
              << new MaterialAutoCompletePlugin(this)
              << new MaterialAvatarPlugin(this)
              << new MaterialBadgePlugin(this)
              << new MaterialCheckBoxPlugin(this)
              << new MaterialCircularProgressPlugin(this)
              << new MaterialDialogPlugin(this)
              << new MaterialDrawerPlugin(this)
              << new MaterialFabPlugin(this)
              << new MaterialFlatButtonPlugin(this)
              << new MaterialIconButtonPlugin(this)
////              << new MaterialListPlugin(this)
////              << new MaterialListItemPlugin(this)
//              << new MaterialMenuPlugin(this)
////              << new MaterialPaperPlugin(this)
              << new MaterialProgressPlugin(this)
              << new MaterialRadioButtonPlugin(this)
              << new MaterialRaisedButtonPlugin(this)
//              << new MaterialScrollbarPlugin(this)
              << new MaterialSliderPlugin(this)
              << new MaterialSnackbarPlugin(this)
////              << new MaterialTablePlugin(this)
              << new MaterialTabsPlugin(this)
              << new MaterialTextFieldPlugin(this)
              << new MaterialTogglePlugin(this)
              << new QtMaterialTabWidgetPlugin(this)
                 ;
}

QList<QDesignerCustomWidgetInterface*> QtMaterialPlugins::customWidgets() const {
    return m_plugins;
}
