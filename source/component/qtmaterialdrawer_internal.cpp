#include "qtmaterialdrawer_internal.h"
#include <QState>
#include <QPainter>
#include <QtWidgets/QLayout>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include "qtmaterialdrawer.h"

/*!
 *  \class QtMaterialDrawerStateMachine
 *  \internal
 */

QtMaterialDrawerStateMachine::QtMaterialDrawerStateMachine(QtMaterialDrawerWidget *drawer, QtMaterialDrawer *parent)
    : QStateMachine(parent),
      m_drawer(drawer),
      m_main(parent),
      m_openingState(new QState),
      m_openedState(new QState),
      m_closingState(new QState),
      m_closedState(new QState),
      m_opacity(0)
{
    addState(m_openingState);
    addState(m_openedState);
    addState(m_closingState);
    addState(m_closedState);

    setInitialState(m_closedState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    transition = new QSignalTransition(this, SIGNAL(signalOpen()));
    transition->setTargetState(m_openingState);
    m_closedState->addTransition(transition);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(m_openedState);
    m_openingState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(signalClose()));
    transition->setTargetState(m_closingState);
    m_openingState->addTransition(transition);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::InCirc);
    transition->addAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(m_closedState);
    m_closingState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(signalClose()));
    transition->setTargetState(m_closingState);
    m_openedState->addTransition(transition);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::InCirc);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(m_closedState);
    m_closingState->addTransition(transition);

    updatePropertyAssignments();
}

QtMaterialDrawerStateMachine::~QtMaterialDrawerStateMachine()
{
}

void QtMaterialDrawerStateMachine::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    m_main->update();
}

bool QtMaterialDrawerStateMachine::isInClosedState() const
{
    return m_closedState->active();
}

void QtMaterialDrawerStateMachine::updatePropertyAssignments()
{
    const qreal closedOffset = -(m_drawer->width()+32);

    m_closingState->assignProperty(m_drawer, "offset", closedOffset);
    m_closedState->assignProperty(m_drawer, "offset", closedOffset);

    m_closingState->assignProperty(this, "opacity", 0);
    m_closedState->assignProperty(this, "opacity", 0);

    m_openingState->assignProperty(m_drawer, "offset", 0);
    m_openingState->assignProperty(this, "opacity", 0.4);
}

/*!
 *  \class QtMaterialDrawerWidget
 *  \internal
 */

QtMaterialDrawerWidget::QtMaterialDrawerWidget(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      m_offset(0)
{
}

QtMaterialDrawerWidget::~QtMaterialDrawerWidget()
{
}

void QtMaterialDrawerWidget::setOffset(int offset)
{
    m_offset = offset;

    QWidget *widget = parentWidget();
    if (widget) {
        setGeometry(widget->rect().translated(offset, 0));
    }
    update();
}

void QtMaterialDrawerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawRect(rect().adjusted(0, 0, -16, 0));

    QLinearGradient gradient(QPointF(width()-16, 0), QPointF(width(), 0));
    gradient.setColorAt(0, QColor(0, 0, 0, 80));
    gradient.setColorAt(0.5, QColor(0, 0, 0, 20));
    gradient.setColorAt(1, QColor(0, 0, 0, 0));
    painter.setBrush(QBrush(gradient));

    painter.drawRect(width()-16, 0, 16, height());
}

QRect QtMaterialDrawerWidget::overlayGeometry() const
{
    return QtMaterialOverlayWidget::overlayGeometry().translated(m_offset, 0);
}
