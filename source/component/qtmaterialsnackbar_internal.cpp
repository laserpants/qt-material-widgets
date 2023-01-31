#include "qtmaterialsnackbar_internal.h"
#include <QPropertyAnimation>
#include "qtmaterialsnackbar.h"
#include "lib/qtmaterialstatetransition.h"
#include <QDebug>

QtMaterialSnackbarStateMachine::QtMaterialSnackbarStateMachine(QtMaterialSnackbar *parent)
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

    QtMaterialStateTransition *transition;

    transition = new QtMaterialStateTransition(SnackbarShowTransition);
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new QtMaterialStateTransition(SnackbarHideTransition);
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new QtMaterialStateTransition(SnackbarHideTransition);
    transition->setTargetState(finalState);
    visibleState->addTransition(transition);

    transition = new QtMaterialStateTransition(SnackbarWaitTransition);
    transition->setTargetState(hiddenState);
    finalState->addTransition(transition);

    transition = new QtMaterialStateTransition(SnackbarNextTransition);
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

QtMaterialSnackbarStateMachine::~QtMaterialSnackbarStateMachine()
{
}

bool QtMaterialSnackbarStateMachine::eventFilter(QObject *watched, QEvent *event)
{
    if (QEvent::MouseButtonPress == event->type() && m_snackbar->clickToDismissMode()) {
        progress();
    }
    return QStateMachine::eventFilter(watched, event);
}

void QtMaterialSnackbarStateMachine::setOffset(qreal offset)
{
    m_offset = offset;
    m_snackbar->update();
}

void QtMaterialSnackbarStateMachine::progress()
{
    m_timer.stop();
    postEvent(new QtMaterialStateTransitionEvent(SnackbarHideTransition));
    if (m_snackbar->clickToDismissMode()) {
        m_snackbar->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }
}

void QtMaterialSnackbarStateMachine::snackbarShown()
{
    m_timer.start(m_snackbar->autoHideDuration());
    if (m_snackbar->clickToDismissMode()) {
        m_snackbar->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
}
