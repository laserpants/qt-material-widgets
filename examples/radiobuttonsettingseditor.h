#ifndef RADIOBUTTONSETTINGSEDITOR_H
#define RADIOBUTTONSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QColorDialog>

#include <radiobutton.h>

#include "ui_radiobuttonsettingsform.h"

using namespace md;

class RadioButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit RadioButtonSettingsEditor(QWidget *parent = 0);
    ~RadioButtonSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::RadioButtonSettingsForm *const ui;
    RadioButton       *const m_radioButton1;
    RadioButton       *const m_radioButton2;
    RadioButton       *const m_radioButton3;
};

#endif // RADIOBUTTONSETTINGSEDITOR_H
