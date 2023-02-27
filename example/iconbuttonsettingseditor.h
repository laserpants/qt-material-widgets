#ifndef ICONBUTTONSETTINGSMANAGER_H
#define ICONBUTTONSETTINGSMANAGER_H

#include <QWidget>
#include "ui_iconbuttonsettingsform.h"

class QtMaterialIconButton;

class IconButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit IconButtonSettingsEditor(QWidget *parent = 0);
    ~IconButtonSettingsEditor();

protected:
    explicit IconButtonSettingsEditor(QtMaterialIconButton *button, QWidget *parent = 0);

    Ui::IconButtonSettingsForm *const ui;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    void init();

    QtMaterialIconButton *const m_button;
};

#endif // ICONBUTTONSETTINGSMANAGER_H
