#include "qtmaterialsnackbar_internal.h"
#include <QPropertyAnimation>
#include "qtmaterialsnackbar.h"
#include "lib/qtmaterialstatetransition.h"
#include <QDebug>
namespace md
{

SnackBarStateMachine::SnackBarStateMachine(SnackBar *parent)
    : QStateMachine(parent),
      m_snackbar(parent)
{
    m_timer.setSingleShot(true);

    QState *hiddenState = new QState;
    QState *visibleState = new QState;
    QState *finalState = new QState;

    addState(hiddenState);
    addState(visibleState);
    addState(finalState);

    setInitialState(hiddenState);

    StateTransition *transition;

    transition = new StateTransition(SnackbarShowTransition);
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new StateTransition(SnackbarHideTransition);
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new StateTransition(SnackbarHideTransition);
    transition->setTargetState(finalState);
    visibleState->addTransition(transition);

    transition = new StateTransition(SnackbarWaitTransition);
    transition->setTargetState(hiddenState);
    finalState->addTransition(transition);

    transition = new StateTransition(SnackbarNextTransition);
    transition->setTargetState(visibleState);
    finalState->addTransition(transition);

    connect(visibleState, SIGNAL(propertiesAssigned()),
            this, SLOT(snackbarShown()));
    connect(finalState, SIGNAL(propertiesAssigned()),
            m_snackbar, SLOT(dequeue()));

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(this, "offset", this);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setDuration(300);
    addDefaultAnimation(animation);

    hiddenState->assignProperty(this, "offset", 1);
    visibleState->assignProperty(this, "offset", 0);
    finalState->assignProperty(this, "offset", 1);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(progress()));

    m_snackbar->installEventFilter(this);
}

SnackBarStateMachine::~SnackBarStateMachine()
{
}

bool SnackBarStateMachine::eventFilter(QObject *watched, QEvent *event)
{
    if (QEvent::MouseButtonPress == event->type() && m_snackbar->clickToDismissMode()) {
        progress();
    }
    return QStateMachine::eventFilter(watched, event);
}

void SnackBarStateMachine::setOffset(qreal offset)
{
    m_offset = offset;
    m_snackbar->update();
}

void SnackBarStateMachine::progress()
{
    m_timer.stop();
    postEvent(new StateTransitionEvent(SnackbarHideTransition));
    if (m_snackbar->clickToDismissMode()) {
        m_snackbar->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }
}

void SnackBarStateMachine::snackbarShown()
{
    m_timer.start(m_snackbar->autoHideDuration());
    if (m_snackbar->clickToDismissMode()) {
        m_snackbar->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
}
}
