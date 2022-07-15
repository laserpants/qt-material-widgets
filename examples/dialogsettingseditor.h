#ifndef DIALOGSETTINGSEDITOR_H
#define DIALOGSETTINGSEDITOR_H

#include "ui_dialogsettingsform.h"
#include <QWidget>

class QtMaterialDialog;

class DialogSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DialogSettingsEditor(QWidget *parent = 0);
    ~DialogSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();

private:
    Ui::DialogSettingsForm *const ui;
    QtMaterialDialog *const m_dialog;
};

#endif  // DIALOGSETTINGSEDITOR_H
