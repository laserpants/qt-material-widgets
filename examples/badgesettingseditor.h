#ifndef BADGESETTINGSEDITOR_H
#define BADGESETTINGSEDITOR_H

#include <QWidget>

#include <qtmaterialavatar.h>
#include <qtmaterialbadge.h>

#include "ui_badgesettingsform.h"

using namespace md;

class BadgeSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit BadgeSettingsEditor(QWidget *parent = 0);
    ~BadgeSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::BadgeSettingsForm *const ui;
    Avatar      *const m_avatar;
    Badge       *const m_badge;
};

#endif // BADGESETTINGSEDITOR_H
