#include "qtmaterialautocomplete_internal.h"
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QDebug>

/*!
 *  \class QtMaterialAutoCompleteStateMachine
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialAutoCompleteStateMachine::QtMaterialAutoCompleteStateMachine(QWidget *menu)
    : QStateMachine(menu),
      m_menu(menu),
      m_closedState(new QState),
      m_openState(new QState),
      m_closingState(new QState)
{
    Q_ASSERT(menu);

    addState(m_closedState);
    addState(m_openState);
    addState(m_closingState);
    setInitialState(m_closedState);

    QSignalTransition *transition;

    transition = new QSignalTransition(this, SIGNAL(shouldOpen()));
    transition->setTargetState(m_openState);
    m_closedState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(shouldClose()));
    transition->setTargetState(m_closedState);
    m_openState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(shouldFade()));
    transition->setTargetState(m_closingState);
    m_openState->addTransition(transition);

    m_closedState->assignProperty(menu, "visible", false);
    m_openState->assignProperty(menu, "visible", true);

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect;
    menu->setGraphicsEffect(effect);

    m_openState->assignProperty(effect, "opacity", 1);
    m_closingState->assignProperty(effect, "opacity", 0);
    m_closedState->assignProperty(effect, "opacity", 0);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(effect, "opacity", this);
    animation->setDuration(240);
    addDefaultAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(m_closedState);
    m_closingState->addTransition(transition);
}

/*!
 *  \internal
 */
QtMaterialAutoCompleteStateMachine::~QtMaterialAutoCompleteStateMachine()
{
}
