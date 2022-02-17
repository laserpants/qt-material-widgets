#ifndef DRAWERSETTINGSEDITOR_H
#define DRAWERSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColorDialog>

#include <qtmaterialdrawer.h>

#include "ui_drawersettingsform.h"

using namespace md;

class DrawerSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DrawerSettingsEditor(QWidget *parent = 0);
    ~DrawerSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();

private:
    Ui::DrawerSettingsForm *const ui;
    Drawer       *const m_drawer;
};

#endif // DRAWERSETTINGSEDITOR_H
