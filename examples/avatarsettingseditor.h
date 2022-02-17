#ifndef AVATARSETTINGSEDITOR_H
#define AVATARSETTINGSEDITOR_H

#include <QWidget>

#include <QColorDialog>
#include <qtmaterialavatar.h>
#include <lib/qtmaterialtheme.h>
#include "ui_avatarsettingsform.h"

using namespace md;
//class Avatar;

class AvatarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AvatarSettingsEditor(QWidget *parent = 0);
    ~AvatarSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::AvatarSettingsForm *const ui;
    Avatar       *const m_avatar;
};

#endif // AVATARSETTINGSEDITOR_H
