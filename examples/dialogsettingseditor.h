#ifndef DIALOGSETTINGSEDITOR_H
#define DIALOGSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColorDialog>
#include <dialog.h>

#include <flatbutton.h>

#include "ui_dialogsettingsform.h"

using namespace md;

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
    Dialog       *const m_dialog;
};

#endif // DIALOGSETTINGSEDITOR_H
