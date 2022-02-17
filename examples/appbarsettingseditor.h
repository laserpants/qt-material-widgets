#ifndef APPBARSETTINGSEDITOR_H
#define APPBARSETTINGSEDITOR_H

#include <QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QColorDialog>
#include <QPalette>

#include <appbar.h>
#include <iconbutton.h>
#include <lib/theme.h>

#include "ui_appbarsettingsform.h"

using namespace md;

class AppBarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AppBarSettingsEditor(QWidget *parent = 0);
    ~AppBarSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::AppBarSettingsForm *const ui;
    AppBar       *const m_appBar;
};

#endif // APPBARSETTINGSEDITOR_H
