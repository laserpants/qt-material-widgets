#ifndef AUTOCOMPLETESETTINGSEDITOR_H
#define AUTOCOMPLETESETTINGSEDITOR_H

#include <QWidget>
//#include "ui_autocompletesettingsform.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>

#include <qtmaterialautocomplete.h>
#include "lib/qtmaterialoverlaywidget.h"

using namespace md;

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
    AutoComplete       *const m_autocomplete;
};

#endif // AUTOCOMPLETESETTINGSEDITOR_H
