#ifndef QTMATERIALRAISEDBUTTON_P_H
#define QTMATERIALRAISEDBUTTON_P_H

#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QEventTransition>

#include "qtmaterialflatbutton_p.h"
#include "qtmaterialraisedbutton.h"

namespace md
{

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
