#ifndef QTMATERIALPLUGINS_H
#define QTMATERIALPLUGINS_H

#include <QDesignerCustomWidgetCollectionInterface>

class QtMaterialPlugins : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.meta-vi.QDesignerCustomWidgetCollectionInterface")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:
    explicit QtMaterialPlugins(QObject *parent = nullptr);
    QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface *> m_plugins;

};

#endif // QTMATERIALPLUGINS_H
