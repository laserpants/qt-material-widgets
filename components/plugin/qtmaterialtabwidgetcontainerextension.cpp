#include "qtmaterialtabwidgetcontainerextension.h"
#include "qtmaterialtabwidget.h"

QtMaterialTabWidgetContainerExtension::QtMaterialTabWidgetContainerExtension(QtMaterialTabWidget *widget,
                                                                     QObject *parent)
    : QObject(parent)
    , myWidget(widget)
{
}

void QtMaterialTabWidgetContainerExtension::addWidget(QWidget *widget)
{
    myWidget->addPage(widget);
}

int QtMaterialTabWidgetContainerExtension::count() const
{
    return myWidget->count();
}

int QtMaterialTabWidgetContainerExtension::currentIndex() const
{
    return myWidget->currentIndex();
}

void QtMaterialTabWidgetContainerExtension::insertWidget(int index, QWidget *widget)
{
    myWidget->insertPage(index, widget);
}

void QtMaterialTabWidgetContainerExtension::remove(int index)
{
    myWidget->removePage(index);
}

void QtMaterialTabWidgetContainerExtension::setCurrentIndex(int index)
{
    myWidget->setCurrentIndex(index);
}

QWidget* QtMaterialTabWidgetContainerExtension::widget(int index) const
{
    return myWidget->widget(index);
}
