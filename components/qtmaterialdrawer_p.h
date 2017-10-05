#ifndef DRAWER_P_H
#define DRAWER_P_H

#include <QObject>

class QtMaterialDrawer;
class QtMaterialDrawerStateMachine;

class QtMaterialDrawerPrivate
{
    Q_DISABLE_COPY(QtMaterialDrawerPrivate)
    Q_DECLARE_PUBLIC(QtMaterialDrawer)

public:
    QtMaterialDrawerPrivate(QtMaterialDrawer *q);
    ~QtMaterialDrawerPrivate();

    void init();

    QtMaterialDrawer             *const q_ptr;
    QtMaterialDrawerStateMachine *stateMachine;
    QWidget                      *window;
    int                           width;
    bool                          clickToClose;
    bool                          autoRaise;
};

#endif // DRAWER_P_H
