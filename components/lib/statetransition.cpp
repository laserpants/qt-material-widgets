#include "lib/statetransition.h"

namespace md
{
StateTransition::StateTransition(StateTransitionType type)
    : m_type(type)
{
}

bool StateTransition::eventTest(QEvent *event)
{
    if (event->type() != QEvent::Type(QEvent::User + 1)) {
        return false;
    }
    StateTransitionEvent *transition = static_cast<StateTransitionEvent *>(event);
    return (m_type == transition->type);
}

void StateTransition::onTransition(QEvent *)
{
}
}
