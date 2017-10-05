#ifndef DIVIDERSETTINGSEDITOR_H
#define DIVIDERSETTINGSEDITOR_H

#include <QWidget>
#include "ui_dividersettingsform.h"

class QtMaterialDivider;

class DividerSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DividerSettingsEditor(QWidget *parent = 0);
    ~DividerSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();

private:
    Ui::DividerSettingsForm *const ui;
    QtMaterialDivider       *const m_divider;
};

#endif // DIVIDERSETTINGSEDITOR_H
