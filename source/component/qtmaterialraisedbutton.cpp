#include "qtmaterialraisedbutton.h"
#include "qtmaterialraisedbutton_p.h"
#include <QStateMachine>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QEventTransition>

/*!
 *  \class QtMaterialRaisedButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialRaisedButtonPrivate::QtMaterialRaisedButtonPrivate(QtMaterialRaisedButton *q)
    : QtMaterialFlatButtonPrivate(q)
{
}

/*!
 *  \internal
 */
QtMaterialRaisedButtonPrivate::~QtMaterialRaisedButtonPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialRaisedButtonPrivate::init()
{
    Q_Q(QtMaterialRaisedButton);

    shadowStateMachine = new QStateMachine(q);
    normalState        = new QState;
    pressedState       = new QState;
    effect             = new QGraphicsDropShadowEffect;

    effect->setBlurRadius(7);
    effect->setOffset(QPointF(0, 2));
    effect->setColor(QColor(0, 0, 0, 75));

    q->setBackgroundMode(Qt::OpaqueMode);
    q->setMinimumHeight(42);
    q->setGraphicsEffect(effect);
    q->setBaseOpacity(0.3);

    shadowStateMachine->addState(normalState);
    shadowStateMachine->addState(pressedState);

    normalState->assignProperty(effect, "offset", QPointF(0, 2));
    normalState->assignProperty(effect, "blurRadius", 7);

    pressedState->assignProperty(effect, "offset", QPointF(0, 5));
    pressedState->assignProperty(effect, "blurRadius", 29);

    QAbstractTransition *transition;

    transition = new QEventTransition(q, QEvent::MouseButtonPress);
    transition->setTargetState(pressedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::MouseButtonDblClick);
    transition->setTargetState(pressedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::MouseButtonRelease);
    transition->setTargetState(normalState);
    pressedState->addTransition(transition);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(effect, "offset", q);
    animation->setDuration(100);
    shadowStateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(effect, "blurRadius", q);
    animation->setDuration(100);
    shadowStateMachine->addDefaultAnimation(animation);

    shadowStateMachine->setInitialState(normalState);
    shadowStateMachine->start();
}

/*!
 *  \class QtMaterialRaisedButton
 */

QtMaterialRaisedButton::QtMaterialRaisedButton(QWidget *parent)
    : QtMaterialFlatButton(*new QtMaterialRaisedButtonPrivate(this), parent)
{
    d_func()->init();
}

QtMaterialRaisedButton::QtMaterialRaisedButton(const QString &text, QWidget *parent)
    : QtMaterialFlatButton(*new QtMaterialRaisedButtonPrivate(this), parent)
{
    d_func()->init();

    setText(text);
}

QtMaterialRaisedButton::~QtMaterialRaisedButton()
{
}

QtMaterialRaisedButton::QtMaterialRaisedButton(QtMaterialRaisedButtonPrivate &d, QWidget *parent)
    : QtMaterialFlatButton(d, parent)
{
    d_func()->init();
}

bool QtMaterialRaisedButton::event(QEvent *event)
{
    Q_D(QtMaterialRaisedButton);

    if (QEvent::EnabledChange == event->type()) {
        if (isEnabled()) {
            d->shadowStateMachine->start();
            d->effect->setEnabled(true);
        } else {
            d->shadowStateMachine->stop();
            d->effect->setEnabled(false);
        }
    }
    return QtMaterialFlatButton::event(event);
}
