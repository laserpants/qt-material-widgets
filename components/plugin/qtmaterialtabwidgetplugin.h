#ifndef QTMATERIALTABWIDGETPLUGIN_H
#define QTMATERIALTABWIDGETPLUGIN_H

#include <QObject>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class QtMaterialTabWidgetPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
public:
    explicit QtMaterialTabWidgetPlugin(QObject *parent = nullptr);

    QString name() const override;
    QString group() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QString includeFile() const override;
    QIcon icon() const override;
    bool isContainer() const override;
    QWidget *createWidget(QWidget *parent) override;
    bool isInitialized() const override;
    void initialize(QDesignerFormEditorInterface *formEditor) override;
    QString domXml() const override;

private slots:
    void currentIndexChanged(int index);
    void pageTitleChanged(const QString &title);

private:
    bool initialized = false;
};

#endif // QTMATERIALTABWIDGETPLUGIN_H
