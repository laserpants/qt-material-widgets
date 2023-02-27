#ifndef SCROLLBARSETTINGSEDITOR_H
#define SCROLLBARSETTINGSEDITOR_H

#include <QWidget>
#include "ui_scrollbarsettingsform.h"

class QtMaterialScrollBar;

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
    QtMaterialScrollBar       *const m_verticalScrollbar;
    QtMaterialScrollBar       *const m_horizontalScrollbar;
};

#endif // SCROLLBARSETTINGSEDITOR_H
