#ifndef QTMATERIALRAISEDBUTTON_P_H
#define QTMATERIALRAISEDBUTTON_P_H

#include "qtmaterialflatbutton_p.h"

class QStateMachine;
class QState;
class QGraphicsDropShadowEffect;
class QtMaterialRaisedButton;

class QtMaterialRaisedButtonPrivate : public QtMaterialFlatButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialRaisedButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialRaisedButton)

public:
    QtMaterialRaisedButtonPrivate(QtMaterialRaisedButton *q);
    ~QtMaterialRaisedButtonPrivate();

    void init();

    QStateMachine             *shadowStateMachine;
    QState                    *normalState;
    QState                    *pressedState;
    QGraphicsDropShadowEffect *effect;
};

#endif // QTMATERIALRAISEDBUTTON_P_H
