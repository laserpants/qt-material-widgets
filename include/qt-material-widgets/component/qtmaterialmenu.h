#ifndef QTMATERIALMENU_H
#define QTMATERIALMENU_H

#include <qt-material-widgets/qt-material-widgets_export.hpp>

#include <QtWidgets/QWidget>

class QT_MATERIAL_WIDGETS_EXPORT QtMaterialMenu : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialMenu(QWidget *parent = 0);
    ~QtMaterialMenu();
};

#endif // QTMATERIALMENU_H
