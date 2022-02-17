#ifndef QTMATERIALMENU_H
#define QTMATERIALMENU_H

#include <QtWidgets/QWidget>

namespace md
{
class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
};
}

#endif // QTMATERIALMENU_H
