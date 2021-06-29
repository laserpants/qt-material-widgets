#ifndef PLUGINDEMOFORM_H
#define PLUGINDEMOFORM_H

#include <QWidget>

namespace Ui {
class PluginDemoForm;
}

class PluginDemoForm : public QWidget
{
    Q_OBJECT

public:
    explicit PluginDemoForm(QWidget *parent = nullptr);
    ~PluginDemoForm();

private:
    Ui::PluginDemoForm *ui;
};

#endif // PLUGINDEMOFORM_H
