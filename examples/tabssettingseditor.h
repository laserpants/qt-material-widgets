#ifndef TABSSETTINGSEDITOR_H
#define TABSSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColorDialog>

#include <tabs.h>

#include "ui_tabssettingsform.h"

using namespace md;

class TabsSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TabsSettingsEditor(QWidget *parent = 0);
    ~TabsSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();

private:
    Ui::TabsSettingsForm *const ui;
    Tabs       *const m_tabs;
};

#endif // TABSSETTINGSEDITOR_H
