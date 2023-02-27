#ifndef AUTOCOMPLETESETTINGSEDITOR_H
#define AUTOCOMPLETESETTINGSEDITOR_H

#include <QWidget>
//#include "ui_autocompletesettingsform.h"

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialAutoComplete;

class AutoCompleteSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AutoCompleteSettingsEditor(QWidget *parent = 0);
    ~AutoCompleteSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    //Ui::AutoCompleteSettingsForm *const ui;
    QtMaterialAutoComplete       *const m_autocomplete;
};

#endif // AUTOCOMPLETESETTINGSEDITOR_H
