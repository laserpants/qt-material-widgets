#ifndef MENU_H
#define MENU_H

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

#endif // MENU_H
