#include "qtmaterialflatbutton_internal.h"
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QFocusEvent>
#include <QSequentialAnimationGroup>
#include "qtmaterialflatbutton.h"
#include "lib/qtmaterialstatetransition.h"

/*!
 *  \class QtMaterialFlatButtonStateMachine
 *  \internal
 */

QtMaterialFlatButtonStateMachine::QtMaterialFlatButtonStateMachine(QtMaterialFlatButton *parent)
    : QStateMachine(parent),
      m_button(parent),
      m_topLevelState(new QState(QState::ParallelStates)),
      m_configState(new QState(m_topLevelState)),
      m_checkableState(new QState(m_topLevelState)),
      m_checkedState(new QState(m_checkableState)),
      m_uncheckedState(new QState(m_checkableState)),
      m_neutralState(new QState(m_configState)),
      m_neutralFocusedState(new QState(m_configState)),
      m_hoveredState(new QState(m_configState)),
      m_hoveredFocusedState(new QState(m_configState)),
      m_pressedState(new QState(m_configState)),
      m_haloAnimation(new QSequentialAnimationGroup(this)),
      m_overlayOpacity(0),
      m_checkedOverlayProgress(parent->isChecked() ? 1 : 0),
      m_haloOpacity(0),
      m_haloSize(0.8),
      m_haloScaleFactor(1),
      m_wasChecked(false)
{
    Q_ASSERT(parent);

    parent->installEventFilter(this);

    m_configState->setInitialState(m_neutralState);
    addState(m_topLevelState);
    setInitialState(m_topLevelState);

    m_checkableState->setInitialState(parent->isChecked() ? m_checkedState
                                                          : m_uncheckedState);
    QtMaterialStateTransition *transition;
    QPropertyAnimation *animation;

    transition = new QtMaterialStateTransition(FlatButtonCheckedTransition);
    transition->setTargetState(m_checkedState);
    m_uncheckedState->addTransition(transition);

    animation = new QPropertyAnimation(this, "checkedOverlayProgress", this);
    animation->setDuration(200);
    transition->addAnimation(animation);

    transition = new QtMaterialStateTransition(FlatButtonUncheckedTransition);
    transition->setTargetState(m_uncheckedState);
    m_checkedState->addTransition(transition);

    animation = new QPropertyAnimation(this, "checkedOverlayProgress", this);
    animation->setDuration(200);
    transition->addAnimation(animation);

    addTransition(m_button, QEvent::FocusIn, m_neutralState, m_neutralFocusedState);
    addTransition(m_button, QEvent::FocusOut, m_neutralFocusedState, m_neutralState);
    addTransition(m_button, QEvent::Enter, m_neutralState, m_hoveredState);
    addTransition(m_button, QEvent::Leave, m_hoveredState, m_neutralState);
    addTransition(m_button, QEvent::Enter, m_neutralFocusedState, m_hoveredFocusedState);
    addTransition(m_button, QEvent::Leave, m_hoveredFocusedState, m_neutralFocusedState);
    addTransition(m_button, QEvent::FocusIn, m_hoveredState, m_hoveredFocusedState);
    addTransition(m_button, QEvent::FocusOut, m_hoveredFocusedState, m_hoveredState);

    transition = new QtMaterialStateTransition(FlatButtonPressedTransition);
    transition->setTargetState(m_pressedState);
    m_hoveredState->addTransition(transition);

    addTransition(m_button, QEvent::Leave, m_pressedState, m_neutralFocusedState);
    addTransition(m_button, QEvent::FocusOut, m_pressedState, m_hoveredState);

    m_neutralState->assignProperty(this, "haloSize", 0);
    m_neutralFocusedState->assignProperty(this, "haloSize", 0.7);
    m_hoveredState->assignProperty(this, "haloSize", 0);
    m_pressedState->assignProperty(this, "haloSize", 4);
    m_hoveredFocusedState->assignProperty(this, "haloSize", 0.7);

    QPropertyAnimation *grow = new QPropertyAnimation(this);
    QPropertyAnimation *shrink = new QPropertyAnimation(this);

    grow->setTargetObject(this);
    grow->setPropertyName("haloScaleFactor");
    grow->setStartValue(0.56);
    grow->setEndValue(0.63);
    grow->setEasingCurve(QEasingCurve::InOutSine);
    grow->setDuration(840);

    shrink->setTargetObject(this);
    shrink->setPropertyName("haloScaleFactor");
    shrink->setStartValue(0.63);
    shrink->setEndValue(0.56);
    shrink->setEasingCurve(QEasingCurve::InOutSine);
    shrink->setDuration(840);

    m_haloAnimation->addAnimation(grow);
    m_haloAnimation->addAnimation(shrink);
    m_haloAnimation->setLoopCount(-1);
}

QtMaterialFlatButtonStateMachine::~QtMaterialFlatButtonStateMachine()
{
}

void QtMaterialFlatButtonStateMachine::setOverlayOpacity(qreal opacity)
{
    m_overlayOpacity = opacity;
    m_button->update();
}

void QtMaterialFlatButtonStateMachine::setCheckedOverlayProgress(qreal progress)
{
    m_checkedOverlayProgress = progress;
    m_button->update();
}

void QtMaterialFlatButtonStateMachine::setHaloOpacity(qreal opacity)
{
    m_haloOpacity = opacity;
    m_button->update();
}

void QtMaterialFlatButtonStateMachine::setHaloSize(qreal size)
{
    m_haloSize = size;
    m_button->update();
}

void QtMaterialFlatButtonStateMachine::setHaloScaleFactor(qreal factor)
{
    m_haloScaleFactor = factor;
    m_button->update();
}

void QtMaterialFlatButtonStateMachine::startAnimations()
{
    m_haloAnimation->start();
    start();
}

void QtMaterialFlatButtonStateMachine::setupProperties()
{
    QColor overlayColor;

    if (Qt::TransparentMode == m_button->backgroundMode()) {
        overlayColor = m_button->backgroundColor();
    } else {
        overlayColor = m_button->foregroundColor();
    }

    const qreal baseOpacity = m_button->baseOpacity();

    m_neutralState->assignProperty(this, "overlayOpacity", 0);
    m_neutralState->assignProperty(this, "haloOpacity", 0);
    m_neutralFocusedState->assignProperty(this, "overlayOpacity", 0);
    m_neutralFocusedState->assignProperty(this, "haloOpacity", baseOpacity);
    m_hoveredState->assignProperty(this, "overlayOpacity", baseOpacity);
    m_hoveredState->assignProperty(this, "haloOpacity", 0);
    m_hoveredFocusedState->assignProperty(this, "overlayOpacity", baseOpacity);
    m_hoveredFocusedState->assignProperty(this, "haloOpacity", baseOpacity);
    m_pressedState->assignProperty(this, "overlayOpacity", baseOpacity);
    m_pressedState->assignProperty(this, "haloOpacity", 0);
    m_checkedState->assignProperty(this, "checkedOverlayProgress", 1);
    m_uncheckedState->assignProperty(this, "checkedOverlayProgress", 0);

    m_button->update();
}

void QtMaterialFlatButtonStateMachine::updateCheckedStatus()
{
    const bool checked = m_button->isChecked();
    if (m_wasChecked != checked) {
        m_wasChecked = checked;
        if (checked) {
            postEvent(new QtMaterialStateTransitionEvent(FlatButtonCheckedTransition));
        } else {
            postEvent(new QtMaterialStateTransitionEvent(FlatButtonUncheckedTransition));
        }
    }
}

bool QtMaterialFlatButtonStateMachine::eventFilter(QObject *watched,
                                                   QEvent  *event)
{
    if (QEvent::FocusIn == event->type()) {
        QFocusEvent *focusEvent = static_cast<QFocusEvent *>(event);
        if (focusEvent && Qt::MouseFocusReason == focusEvent->reason()) {
            postEvent(new QtMaterialStateTransitionEvent(FlatButtonPressedTransition));
            return true;
        }
    }
    return QStateMachine::eventFilter(watched, event);
}

void QtMaterialFlatButtonStateMachine::addTransition(QObject *object,
                                                     QEvent::Type eventType,
                                                     QState *fromState,
                                                     QState *toState)
{
    addTransition(new QEventTransition(object, eventType), fromState, toState);
}

void QtMaterialFlatButtonStateMachine::addTransition(QAbstractTransition *transition,
                                                     QState *fromState,
                                                     QState *toState)
{
    transition->setTargetState(toState);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(this, "overlayOpacity", this);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "haloOpacity", this);
    animation->setDuration(170);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "haloSize", this);
    animation->setDuration(350);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    transition->addAnimation(animation);

    fromState->addTransition(transition);
}
