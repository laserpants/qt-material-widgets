#ifndef DRAWER_P_H
#define DRAWER_P_H

#include <QObject>
namespace md
{

class Drawer;
class DrawerWidget;
class DrawerStateMachine;

class DrawerPrivate
{
    Q_DISABLE_COPY(DrawerPrivate)
    Q_DECLARE_PUBLIC(Drawer)

public:
    DrawerPrivate(Drawer *q);
    ~DrawerPrivate();

    void init();
    void setClosed(bool value = true);

    Drawer             *const q_ptr;
    DrawerWidget       *widget;
    DrawerStateMachine *stateMachine;
    QWidget                      *window;
    int                           width;
    bool                          clickToClose;
    bool                          autoRaise;
    bool                          closed;
    bool                          overlay;
};
}
#endif // DRAWER_P_H
