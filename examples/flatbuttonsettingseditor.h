#ifndef FLATBUTTONSETTINGSMANAGER_H
#define FLATBUTTONSETTINGSMANAGER_H

#include <QWidget>
#include <QColorDialog>
#include <QDebug>

#include <qtmaterialflatbutton.h>

#include "ui_flatbuttonsettingsform.h"

using namespace md;

class FlatButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FlatButtonSettingsEditor(QWidget *parent = 0);
    ~FlatButtonSettingsEditor();

protected:
    explicit FlatButtonSettingsEditor(FlatButton *button, QWidget *parent = 0);

    Ui::FlatButtonSettingsForm *const ui;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();
    void applyDefaultPreset();
    void applyCheckablePreset();

private:
    void init();

    FlatButton *const m_button;
};

#endif // FLATBUTTONSETTINGSMANAGER_H
