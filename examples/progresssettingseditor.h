#ifndef PROGRESSSETTINGSEDITOR_H
#define PROGRESSSETTINGSEDITOR_H

#include <QWidget>
#include <QColorDialog>

#include <progress.h>
#include <lib/theme.h>

#include "ui_progresssettingsform.h"

using namespace md;

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
    ProgressBar       *const m_progress;
};

#endif // PROGRESSSETTINGSEDITOR_H
