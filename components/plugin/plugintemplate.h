#ifndef PLUGINTEMPLATE_H
#define PLUGINTEMPLATE_H

#define QT_DESIGN_PLUGIN(pluginName, headerFile, className)                           \
class pluginName : public QObject, public QDesignerCustomWidgetInterface              \
{                                                                                     \
    Q_OBJECT                                                                          \
public:                                                                               \
    explicit pluginName(QObject *parent = nullptr):QObject(parent) {}                 \
                                                                                      \
    QString name() const override { return #className; }                              \
    QString group() const override { return "Qt Material Widgets"; }                  \
    QString toolTip() const override { return QString(); }                            \
    QString whatsThis() const override { return QString(); }                          \
    QString includeFile() const override { return headerFile; }                       \
    QIcon icon() const override { return QIcon(); }                                   \
                                                                                      \
    QWidget *createWidget(QWidget *parent) override { return new className(parent); } \
    bool isContainer() const override { return true; }                                \
    bool isInitialized() const override { return initialized; }                       \
    void initialize(QDesignerFormEditorInterface * /*core*/) override {               \
        if (initialized)                                                              \
            return;                                                                   \
                                                                                      \
        initialized = true;                                                           \
    }                                                                                 \
                                                                                      \
private:                                                                              \
    bool initialized;                                                                 \
};                                                                                    \


#endif // PLUGINTEMPLATE_H
