#ifndef QTMATERIALMENU_H
#define QTMATERIALMENU_H

#include <QtWidgets/QWidget>
#include <QtUiPlugin/QDesignerExportWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT QtMaterialMenu : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialMenu(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // QTMATERIALMENU_H
