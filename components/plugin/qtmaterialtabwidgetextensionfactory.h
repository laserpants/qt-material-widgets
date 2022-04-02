#ifndef QTMATERIALTABWIDGETEXTENSIONFACTORY_H
#define QTMATERIALTABWIDGETEXTENSIONFACTORY_H

#include <QtDesigner/QExtensionFactory>

QT_BEGIN_NAMESPACE
class QExtensionManager;
QT_END_NAMESPACE

class QtMaterialTabWidgetExtensionFactory: public QExtensionFactory
{
    Q_OBJECT

public:
    explicit QtMaterialTabWidgetExtensionFactory(QExtensionManager *parent = nullptr);

protected:
    QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const override;
};

#endif // QTMATERIALTABWIDGETEXTENSIONFACTORY_H
