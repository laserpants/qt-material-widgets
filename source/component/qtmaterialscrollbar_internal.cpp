#include "qtmaterialscrollbar_internal.h"
#include <QPropertyAnimation>
#include <QEventTransition>

/*!
 *  \class QtMaterialScrollBarStateMachine
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialScrollBarStateMachine::QtMaterialScrollBarStateMachine(QtMaterialScrollBar *parent)
    : QStateMachine(parent),
      m_scrollBar(parent),
      m_focusState(new QState),
      m_blurState(new QState),
      m_opacity(0)
{
    Q_ASSERT(parent);

    addState(m_focusState);
    addState(m_blurState);
    setInitialState(m_blurState);

    QEventTransition *transition;

    transition = new QEventTransition(parent, QEvent::Enter);
    transition->setTargetState(m_focusState);
    m_blurState->addTransition(transition);

    transition = new QEventTransition(parent, QEvent::Leave);
    transition->setTargetState(m_blurState);
    m_focusState->addTransition(transition);

    m_focusState->assignProperty(this, "opacity", 1);
    m_blurState->assignProperty(this, "opacity", 0);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(340);
    addDefaultAnimation(animation);
}

/*!
 *  \internal
 */
QtMaterialScrollBarStateMachine::~QtMaterialScrollBarStateMachine()
{
}
