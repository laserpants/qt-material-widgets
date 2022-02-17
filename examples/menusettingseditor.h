#ifndef MENUSETTINGSEDITOR_H
#define MENUSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>

#include <menu.h>
#include "lib/overlaywidget.h"

//#include "ui_menusettingsform.h"

using namespace md;

class MenuSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit MenuSettingsEditor(QWidget *parent = 0);
    ~MenuSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    //Ui::MenuSettingsForm *const ui;
    Menu       *const m_menu;
};

#endif // MENUSETTINGSEDITOR_H
