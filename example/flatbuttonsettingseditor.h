#ifndef FLATBUTTONSETTINGSMANAGER_H
#define FLATBUTTONSETTINGSMANAGER_H

#include <QWidget>
#include "ui_flatbuttonsettingsform.h"

class QtMaterialFlatButton;

class FlatButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FlatButtonSettingsEditor(QWidget *parent = 0);
    ~FlatButtonSettingsEditor();

protected:
    explicit FlatButtonSettingsEditor(QtMaterialFlatButton *button, QWidget *parent = 0);

    Ui::FlatButtonSettingsForm *const ui;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();
    void applyDefaultPreset();
    void applyCheckablePreset();

private:
    void init();

    QtMaterialFlatButton *const m_button;
};

#endif // FLATBUTTONSETTINGSMANAGER_H
