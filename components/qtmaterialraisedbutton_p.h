#ifndef QTMATERIALRAISEDBUTTON_P_H
#define QTMATERIALRAISEDBUTTON_P_H

#include "qtmaterialflatbutton_p.h"
namespace md
{

class QStateMachine;
class QState;
class QGraphicsDropShadowEffect;
class RaisedButton;

class RaisedButtonPrivate : public FlatButtonPrivate
{
    Q_DISABLE_COPY(RaisedButtonPrivate)
    Q_DECLARE_PUBLIC(RaisedButton)

public:
    RaisedButtonPrivate(RaisedButton *q);
    ~RaisedButtonPrivate();

    void init();

    QStateMachine             *shadowStateMachine;
    QState                    *normalState;
    QState                    *pressedState;
    QGraphicsDropShadowEffect *effect;
};
}
#endif // QTMATERIALRAISEDBUTTON_P_H
