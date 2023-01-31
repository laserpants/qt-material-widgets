#include "qtmaterialdialog.h"
#include "qtmaterialdialog_p.h"
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QStateMachine>
#include <QState>
#include <QtWidgets/QApplication>
#include <QPropertyAnimation>
#include <QPainter>
#include "qtmaterialdialog_internal.h"
#include "lib/qtmaterialstatetransition.h"

/*!
 *  \class QtMaterialDialogPrivate
 *  \internal
 */

QtMaterialDialogPrivate::QtMaterialDialogPrivate(QtMaterialDialog *q)
    : q_ptr(q)
{
}

QtMaterialDialogPrivate::~QtMaterialDialogPrivate()
{
}

void QtMaterialDialogPrivate::init()
{
    Q_Q(QtMaterialDialog);

    dialogWindow = new QtMaterialDialogWindow(q);
    proxyStack   = new QStackedLayout;
    stateMachine = new QStateMachine(q);
    proxy        = new QtMaterialDialogProxy(dialogWindow, proxyStack, q);

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

    QtMaterialStateTransition *transition;

    transition = new QtMaterialStateTransition(DialogShowTransition);
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new QtMaterialStateTransition(DialogHideTransition);
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
 *  \class QtMaterialDialog
 */

QtMaterialDialog::QtMaterialDialog(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      d_ptr(new QtMaterialDialogPrivate(this))
{
    d_func()->init();
}

QtMaterialDialog::~QtMaterialDialog()
{
}

QLayout *QtMaterialDialog::windowLayout() const
{
    Q_D(const QtMaterialDialog);

    return d->dialogWindow->layout();
}

void QtMaterialDialog::setWindowLayout(QLayout *layout)
{
    Q_D(QtMaterialDialog);

    d->dialogWindow->setLayout(layout);
}

void QtMaterialDialog::showDialog()
{
    Q_D(QtMaterialDialog);

    d->stateMachine->postEvent(new QtMaterialStateTransitionEvent(DialogShowTransition));
    raise();
}

void QtMaterialDialog::hideDialog()
{
    Q_D(QtMaterialDialog);

    d->stateMachine->postEvent(new QtMaterialStateTransitionEvent(DialogHideTransition));
    setAttribute(Qt::WA_TransparentForMouseEvents);
    d->proxyStack->setCurrentIndex(1);
}

void QtMaterialDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialDialog);

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.setOpacity(d->proxy->opacity()/2.4);
    painter.drawRect(rect());
}
