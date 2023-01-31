#ifndef CHECKBOXSETTINGSEDITOR_H
#define CHECKBOXSETTINGSEDITOR_H

#include <QWidget>
#include "ui_checkboxsettingsform.h"

class QtMaterialCheckable;

class CheckBoxSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CheckBoxSettingsEditor(QWidget *parent = 0);
    ~CheckBoxSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::CheckBoxSettingsForm *const ui;
    QtMaterialCheckable      *const m_checkBox;
};

#endif // CHECKBOXSETTINGSEDITOR_H
