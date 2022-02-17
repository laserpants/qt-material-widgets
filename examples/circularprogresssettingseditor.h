#ifndef CIRCULARPROGRESSSETTINGSEDITOR_H
#define CIRCULARPROGRESSSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColorDialog>

#include <qtmaterialcircularprogress.h>

#include "ui_circularprogresssettingsform.h"

using namespace md;

class CircularProgressSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CircularProgressSettingsEditor(QWidget *parent = 0);
    ~CircularProgressSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::CircularProgressSettingsForm *const ui;
    CircularProgress       *const m_progress;
};

#endif // CIRCULARPROGRESSSETTINGSEDITOR_H
