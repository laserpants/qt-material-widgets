#include "lib/qtmaterialstatetransition.h"

QtMaterialStateTransition::QtMaterialStateTransition(QtMaterialStateTransitionType type)
    : m_type(type)
{
}

bool QtMaterialStateTransition::eventTest(QEvent *event)
{
    if (event->type() != QEvent::Type(QEvent::User + 1)) {
        return false;
    }
    QtMaterialStateTransitionEvent *transition = static_cast<QtMaterialStateTransitionEvent *>(event);
    return (m_type == transition->type);
}

void QtMaterialStateTransition::onTransition(QEvent *)
{
}
