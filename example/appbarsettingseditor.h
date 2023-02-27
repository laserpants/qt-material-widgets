#ifndef APPBARSETTINGSEDITOR_H
#define APPBARSETTINGSEDITOR_H

#include <QWidget>
#include "ui_appbarsettingsform.h"

class QtMaterialAppBar;

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
    QtMaterialAppBar       *const m_appBar;
};

#endif // APPBARSETTINGSEDITOR_H
