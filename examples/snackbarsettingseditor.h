#ifndef SNACKBARSETTINGSEDITOR_H
#define SNACKBARSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColorDialog>

#include <qtmaterialsnackbar.h>

#include "ui_snackbarsettingsform.h"

using namespace md;

class SnackbarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SnackbarSettingsEditor(QWidget *parent = 0);
    ~SnackbarSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void showSnackbar();

private:
    Ui::SnackbarSettingsForm *const ui;
    SnackBar       *const m_snackbar;
};

#endif // SNACKBARSETTINGSEDITOR_H
