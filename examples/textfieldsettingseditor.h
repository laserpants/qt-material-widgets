#ifndef TEXTFIELDSETTINGSEDITOR_H
#define TEXTFIELDSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColorDialog>

#include <textfield.h>

#include "ui_textfieldsettingsform.h"

using namespace md;

class TextFieldSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TextFieldSettingsEditor(QWidget *parent = 0);
    ~TextFieldSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();
    void setShowInputLine();

private:
    Ui::TextFieldSettingsForm *const ui;
    TextField       *const m_textField;
};

#endif // TEXTFIELDSETTINGSEDITOR_H
