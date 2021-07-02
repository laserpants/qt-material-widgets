#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormWindowInterface>
#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerPropertySheetExtension>

#include "qtmaterialtabwidgetplugin.h"
#include "qtmaterialtabwidget.h"
#include "qtmaterialtabwidgetextensionfactory.h"

QtMaterialTabWidgetPlugin::QtMaterialTabWidgetPlugin(QObject *parent)
    : QObject(parent)
{
}

QString QtMaterialTabWidgetPlugin::name() const
{
    return QLatin1String("QtMaterialTabWidget");
}

QString QtMaterialTabWidgetPlugin::group() const
{
    return QLatin1String("Qt Material Widgets");
}

QString QtMaterialTabWidgetPlugin::toolTip() const
{
    return QString();
}

QString QtMaterialTabWidgetPlugin::whatsThis() const
{
    return QString();
}

QString QtMaterialTabWidgetPlugin::includeFile() const
{
    return QLatin1String("qtmaterialtabwidget.h");
}

QIcon QtMaterialTabWidgetPlugin::icon() const
{
    return QIcon();
}

//! [0] //! [1]
bool QtMaterialTabWidgetPlugin::isContainer() const
{
    return true;
}

//! [1] //! [2]
QWidget *QtMaterialTabWidgetPlugin::createWidget(QWidget *parent)
{
    QtMaterialTabWidget *widget = new QtMaterialTabWidget(parent);
    connect(widget, &QtMaterialTabWidget::currentIndexChanged,
            this, &QtMaterialTabWidgetPlugin::currentIndexChanged);
    connect(widget, &QtMaterialTabWidget::pageTitleChanged,
            this, &QtMaterialTabWidgetPlugin::pageTitleChanged);
    return widget;
}

//! [2] //! [3]
bool QtMaterialTabWidgetPlugin::isInitialized() const
{
    return initialized;
}
//! [3]

//! [4]
void QtMaterialTabWidgetPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    if (initialized)
        return;
//! [4]

//! [5]
    QExtensionManager *manager = formEditor->extensionManager();
//! [5] //! [6]
    QExtensionFactory *factory = new QtMaterialTabWidgetExtensionFactory(manager);

    Q_ASSERT(manager != 0);
    manager->registerExtensions(factory, Q_TYPEID(QDesignerContainerExtension));

    initialized = true;
}
//! [6]

//! [7]
QString QtMaterialTabWidgetPlugin::domXml() const
{
    return QLatin1String("\
<ui language=\"c++\">\
    <widget class=\"QtMaterialTabWidget\" name=\"tabwidget\">\
        <widget class=\"QWidget\" name=\"page\" />\
    </widget>\
    <customwidgets>\
        <customwidget>\
            <class>QtMaterialTabWidget</class>\
            <extends>QWidget</extends>\
            <addpagemethod>addPage</addpagemethod>\
        </customwidget>\
    </customwidgets>\
</ui>");
}
//! [7]

//! [8]
void QtMaterialTabWidgetPlugin::currentIndexChanged(int index)
{
    Q_UNUSED(index);
    QtMaterialTabWidget *widget = qobject_cast<QtMaterialTabWidget*>(sender());
//! [8] //! [9]
    if (widget) {
        QDesignerFormWindowInterface *form = QDesignerFormWindowInterface::findFormWindow(widget);
        if (form)
            form->emitSelectionChanged();
    }
}
//! [9]

//! [10]
void QtMaterialTabWidgetPlugin::pageTitleChanged(const QString &title)
{
    Q_UNUSED(title);
    QtMaterialTabWidget *widget = qobject_cast<QtMaterialTabWidget*>(sender());
//! [10] //! [11]
    if (widget) {
        QWidget *page = widget->widget(widget->currentIndex());
        QDesignerFormWindowInterface *form;
        form = QDesignerFormWindowInterface::findFormWindow(widget);
//! [11]
        if (form) {
//! [12]
            QDesignerFormEditorInterface *editor = form->core();
            QExtensionManager *manager = editor->extensionManager();
//! [12] //! [13]
            QDesignerPropertySheetExtension *sheet;
            sheet = qt_extension<QDesignerPropertySheetExtension*>(manager, page);
            const int propertyIndex = sheet->indexOf(QLatin1String("windowTitle"));
            sheet->setChanged(propertyIndex, true);
        }
    }
}
