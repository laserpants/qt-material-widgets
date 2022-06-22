#ifndef CHECKBOXSETTINGSEDITOR_H
#define CHECKBOXSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColorDialog>

#include <checkbox.h>

#include "ui_checkboxsettingsform.h"

using namespace md;

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
    Checkable      *const m_checkBox;
};

#endif // CHECKBOXSETTINGSEDITOR_H
