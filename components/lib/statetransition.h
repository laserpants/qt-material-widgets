#ifndef STATETRANSITION_H
#define STATETRANSITION_H

#include <QAbstractTransition>
#include "lib/statetransitionevent.h"

namespace md
{
class StateTransition : public QAbstractTransition
{
    Q_OBJECT

public:
    StateTransition(StateTransitionType type);

protected:
    virtual bool eventTest(QEvent *event);
    virtual void onTransition(QEvent *);

private:
    StateTransitionType m_type;
};
}

#endif // STATETRANSITION_H
