#ifndef MATERIALTOGGLEPLUGIN_H
#define MATERIALTOGGLEPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class MaterialTogglePlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
public:
    explicit MaterialTogglePlugin(QObject *parent = nullptr);

    QString name() const;
    QString group() const;
    QString toolTip() const;
    QString whatsThis() const;
    QString includeFile() const;
    QIcon icon() const;

    bool isContainer() const;

    QWidget *createWidget(QWidget *parent);

private:
    bool initialized;
};

#endif // MATERIALTOGGLEPLUGIN_H
