#ifndef QTMATERIALSTATETRANSITION_H
#define QTMATERIALSTATETRANSITION_H

#include <QAbstractTransition>
#include "lib/qtmaterialstatetransitionevent.h"

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

#endif // QTMATERIALSTATETRANSITION_H
