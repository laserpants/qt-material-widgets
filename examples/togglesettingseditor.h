#ifndef TOGGLESETTINGSEDITOR_H
#define TOGGLESETTINGSEDITOR_H

#include <QWidget>
#include <QColorDialog>

#include <toggle.h>

#include "ui_togglesettingsform.h"

using namespace md;

class ToggleSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ToggleSettingsEditor(QWidget *parent = 0);
    ~ToggleSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::ToggleSettingsForm *const ui;
    Toggle       *const m_toggle;
};

#endif // TOGGLESETTINGSEDITOR_H
