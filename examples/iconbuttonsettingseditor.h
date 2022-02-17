#ifndef ICONBUTTONSETTINGSMANAGER_H
#define ICONBUTTONSETTINGSMANAGER_H

#include <QWidget>
#include <QColorDialog>

#include <qtmaterialiconbutton.h>
#include <lib/qtmaterialtheme.h>

#include "ui_iconbuttonsettingsform.h"

using namespace md;

class IconButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit IconButtonSettingsEditor(QWidget *parent = 0);
    ~IconButtonSettingsEditor();

protected:
    explicit IconButtonSettingsEditor(IconButton *button, QWidget *parent = 0);

    Ui::IconButtonSettingsForm *const ui;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    void init();

    IconButton *const m_button;
};

#endif // ICONBUTTONSETTINGSMANAGER_H
