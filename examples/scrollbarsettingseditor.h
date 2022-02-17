#ifndef SCROLLBARSETTINGSEDITOR_H
#define SCROLLBARSETTINGSEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QtWidgets/QTextEdit>

#include <qtmaterialscrollbar.h>

#include "ui_scrollbarsettingsform.h"

using namespace md;

class ScrollBarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollBarSettingsEditor(QWidget *parent = 0);
    ~ScrollBarSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();

private:
    Ui::ScrollBarSettingsForm *const ui;
    ScrollBar       *const m_verticalScrollbar;
    ScrollBar       *const m_horizontalScrollbar;
};

#endif // SCROLLBARSETTINGSEDITOR_H
