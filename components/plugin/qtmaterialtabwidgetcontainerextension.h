#ifndef QTMATERIALTABWIDGETCONTAINEREXTENSION_H
#define QTMATERIALTABWIDGETCONTAINEREXTENSION_H

#include <QtDesigner/QDesignerContainerExtension>

QT_BEGIN_NAMESPACE
class QExtensionManager;
QT_END_NAMESPACE
class QtMaterialTabWidget;

class QtMaterialTabWidgetContainerExtension: public QObject,
        public QDesignerContainerExtension
{
Q_OBJECT
Q_INTERFACES(QDesignerContainerExtension)

public:
explicit QtMaterialTabWidgetContainerExtension(QtMaterialTabWidget *widget, QObject *parent);

void addWidget(QWidget *widget) override;
int count() const override;
int currentIndex() const override;
void insertWidget(int index, QWidget *widget) override;
void remove(int index) override;
void setCurrentIndex(int index) override;
QWidget *widget(int index) const override;

private:
QtMaterialTabWidget *myWidget;
};

#endif // QTMATERIALTABWIDGETCONTAINEREXTENSION_H
