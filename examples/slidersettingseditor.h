#ifndef SLIDERSETTINGSEDITOR_H
#define SLIDERSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColorDialog>

#include <qtmaterialslider.h>

#include "ui_slidersettingsform.h"

using namespace md;

class SliderSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SliderSettingsEditor(QWidget *parent = 0);
    ~SliderSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();

private:
    Ui::SliderSettingsForm *const ui;
    Slider       *const m_slider;
};

#endif // SLIDERSETTINGSEDITOR_H
