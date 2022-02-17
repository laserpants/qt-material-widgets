#include "qtmaterialdialog.h"

namespace md
{

/*!
 *  \class DialogPrivate
 *  \internal
 */

DialogPrivate::DialogPrivate(Dialog *q)
    : q_ptr(q)
{
}

DialogPrivate::~DialogPrivate()
{
}

void DialogPrivate::init()
{
    Q_Q(Dialog);

    dialogWindow = new DialogWindow(q);
    proxyStack   = new QStackedLayout;
    stateMachine = new QStateMachine(q);
    proxy        = new DialogProxy(dialogWindow, proxyStack, q);

    QVBoxLayout *layout = new QVBoxLayout;
    q->setLayout(layout);

    QWidget *widget = new QWidget;
    widget->setLayout(proxyStack);
    widget->setMinimumWidth(400);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0, 200));
    effect->setBlurRadius(64);
    effect->setOffset(0, 13);
    widget->setGraphicsEffect(effect);

    layout->addWidget(widget);
    layout->setAlignment(widget, Qt::AlignCenter);

    proxyStack->addWidget(dialogWindow);
    proxyStack->addWidget(proxy);
    proxyStack->setCurrentIndex(1);

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QState *hiddenState = new QState;
    QState *visibleState = new QState;

    stateMachine->addState(hiddenState);
    stateMachine->addState(visibleState);
    stateMachine->setInitialState(hiddenState);

    StateTransition *transition;

    transition = new StateTransition(DialogShowTransition);
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new StateTransition(DialogHideTransition);
    transition->setTargetState(hiddenState);
    visibleState->addTransition(transition);

    visibleState->assignProperty(proxy, "opacity", 1);
    visibleState->assignProperty(effect, "color", QColor(0, 0, 0, 200));
    visibleState->assignProperty(dialogWindow, "offset", 0);
    hiddenState->assignProperty(proxy, "opacity", 0);
    hiddenState->assignProperty(effect, "color", QColor(0, 0, 0, 0));
    hiddenState->assignProperty(dialogWindow, "offset", 200);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(proxy, "opacity", q);
    animation->setDuration(280);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(effect, "color", q);
    animation->setDuration(280);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(dialogWindow, "offset", q);
    animation->setDuration(280);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    stateMachine->addDefaultAnimation(animation);

    QObject::connect(visibleState, SIGNAL(propertiesAssigned()),
                     proxy, SLOT(makeOpaque()));
    QObject::connect(hiddenState, SIGNAL(propertiesAssigned()),
                     proxy, SLOT(makeTransparent()));

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class Dialog
 */

Dialog::Dialog(QWidget *parent)
    : OverlayWidget(parent),
      d_ptr(new DialogPrivate(this))
{
    d_func()->init();
}

Dialog::~Dialog()
{
}

QLayout *Dialog::windowLayout() const
{
    Q_D(const Dialog);

    return d->dialogWindow->layout();
}

void Dialog::setWindowLayout(QLayout *layout)
{
    Q_D(Dialog);

    d->dialogWindow->setLayout(layout);
}

void Dialog::showDialog()
{
    Q_D(Dialog);

    d->stateMachine->postEvent(new StateTransitionEvent(DialogShowTransition));
    raise();
}

void Dialog::hideDialog()
{
    Q_D(Dialog);

    d->stateMachine->postEvent(new StateTransitionEvent(DialogHideTransition));
    setAttribute(Qt::WA_TransparentForMouseEvents);
    d->proxyStack->setCurrentIndex(1);
}

void Dialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Dialog);

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.setOpacity(d->proxy->opacity()/2.4);
    painter.drawRect(rect());
}
}
