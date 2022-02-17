#ifndef FABSETTINGSEDITOR_H
#define FABSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QColorDialog>

#include <qtmaterialfab.h>

#include "ui_fabsettingsform.h"

using namespace md;

class FloatingActionButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FloatingActionButtonSettingsEditor(QWidget *parent = 0);
    ~FloatingActionButtonSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::FloatingActionButtonSettingsForm *const ui;
    FloatingActionButton       *const m_fab;
};

#endif // FABSETTINGSEDITOR_H
