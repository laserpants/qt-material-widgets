#ifndef PROGRESSSETTINGSEDITOR_H
#define PROGRESSSETTINGSEDITOR_H

#include <QWidget>
#include "ui_progresssettingsform.h"

class QtMaterialProgress;

class ProgressSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressSettingsEditor(QWidget *parent = 0);
    ~ProgressSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::ProgressSettingsForm *const ui;
    QtMaterialProgress       *const m_progress;
};

#endif // PROGRESSSETTINGSEDITOR_H
