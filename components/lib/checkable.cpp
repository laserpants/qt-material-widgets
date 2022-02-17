#include "lib/checkable.h"
#include "lib/checkable_p.h"
#include "lib/rippleoverlay.h"
#include "lib/ripple.h"
#include "lib/style.h"
#include "lib/checkable_internal.h"

namespace md
{
/*!
 *  \class CheckablePrivate
 *  \internal
 */

CheckablePrivate::CheckablePrivate(Checkable *q)
    : q_ptr(q)
{
}

CheckablePrivate::~CheckablePrivate()
{
}

void CheckablePrivate::init()
{
    Q_Q(Checkable);

    rippleOverlay          = new RippleOverlay;
    checkedIcon            = new CheckableIcon(QIcon(QDir::currentPath()+"/../components/icons/toggle/svg/production/ic_check_box_24px.svg"), q);
    uncheckedIcon          = new CheckableIcon(QIcon(QDir::currentPath()+"/../components/icons/toggle/svg/production/ic_check_box_outline_blank_24px.svg"), q);
    stateMachine           = new QStateMachine(q);
    uncheckedState         = new QState;
    checkedState           = new QState;
    disabledUncheckedState = new QState;
    disabledCheckedState   = new QState;
    uncheckedTransition    = new QSignalTransition(q, SIGNAL(toggled(bool)));
    checkedTransition      = new QSignalTransition(q, SIGNAL(toggled(bool)));
    labelPosition          = Checkable::LabelPositionRight;
    useThemeColors         = true;

    rippleOverlay->setParent(q->parentWidget());
    rippleOverlay->installEventFilter(q);

    q->setCheckable(true);
    q->setStyle(&Style::instance());
    q->setFont(QFont("Roboto", 11, QFont::Normal));

    stateMachine->addState(uncheckedState);
    stateMachine->addState(checkedState);
    stateMachine->addState(disabledUncheckedState);
    stateMachine->addState(disabledCheckedState);
    stateMachine->setInitialState(uncheckedState);

    // Transition to checked

    uncheckedTransition->setTargetState(checkedState);
    uncheckedState->addTransition(uncheckedTransition);

    // Transition to unchecked

    checkedTransition->setTargetState(uncheckedState);
    checkedState->addTransition(checkedTransition);

    QAbstractTransition *transition;

    // Transitions enabled <==> disabled

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(disabledUncheckedState);
    uncheckedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(uncheckedState);
    disabledUncheckedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(disabledCheckedState);
    checkedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(checkedState);
    disabledCheckedState->addTransition(transition);

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(disabledCheckedState);
    disabledUncheckedState->addTransition(transition);

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(disabledUncheckedState);
    disabledCheckedState->addTransition(transition);

    //

    checkedState->assignProperty(checkedIcon, "opacity", 1);
    checkedState->assignProperty(uncheckedIcon, "opacity", 0);

    uncheckedState->assignProperty(checkedIcon, "opacity", 0);
    uncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

    disabledCheckedState->assignProperty(checkedIcon, "opacity", 1);
    disabledCheckedState->assignProperty(uncheckedIcon, "opacity", 0);

    disabledUncheckedState->assignProperty(checkedIcon, "opacity", 0);
    disabledUncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

    checkedState->assignProperty(checkedIcon, "color", q->checkedColor());
    checkedState->assignProperty(uncheckedIcon, "color", q->checkedColor());

    uncheckedState->assignProperty(uncheckedIcon, "color", q->uncheckedColor());
    uncheckedState->assignProperty(uncheckedIcon, "color", q->uncheckedColor());

    disabledUncheckedState->assignProperty(uncheckedIcon, "color", q->disabledColor());
    disabledCheckedState->assignProperty(checkedIcon, "color", q->disabledColor());

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class QtMaterialCheckable
 */

Checkable::Checkable(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new CheckablePrivate(this))
{
    d_func()->init();
}

Checkable::~Checkable()
{
}

void Checkable::setLabelPosition(LabelPosition placement)
{
    Q_D(Checkable);

    d->labelPosition = placement;
    update();
}

Checkable::LabelPosition Checkable::labelPosition() const
{
    Q_D(const Checkable);

    return d->labelPosition;
}

void Checkable::setUseThemeColors(bool value)
{
    Q_D(Checkable);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    setupProperties();
}

bool Checkable::useThemeColors() const
{
    Q_D(const Checkable);

    return d->useThemeColors;
}

void Checkable::setCheckedColor(const QColor &color)
{
    Q_D(Checkable);

    d->checkedColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    setupProperties();
}

QColor Checkable::checkedColor() const
{
    Q_D(const Checkable);

    if (d->useThemeColors || !d->checkedColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->checkedColor;
    }
}

void Checkable::setUncheckedColor(const QColor &color)
{
    Q_D(Checkable);

    d->uncheckedColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    setupProperties();
}

QColor Checkable::uncheckedColor() const
{
    Q_D(const Checkable);

    if (d->useThemeColors || !d->uncheckedColor.isValid()) {
        return Style::instance().themeColor("text");
    } else {
        return d->uncheckedColor;
    }
}

void Checkable::setTextColor(const QColor &color)
{
    Q_D(Checkable);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    setupProperties();
}

QColor Checkable::textColor() const
{
    Q_D(const Checkable);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void Checkable::setDisabledColor(const QColor &color)
{
    Q_D(Checkable);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    setupProperties();
}

QColor Checkable::disabledColor() const
{
    Q_D(const Checkable);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return Style::instance().themeColor("accent3");
    } else {
        return d->disabledColor;
    }
}

void Checkable::setCheckedIcon(const QIcon &icon)
{
    Q_D(Checkable);

    d->checkedIcon->setIcon(icon);
    update();
}

QIcon Checkable::checkedIcon() const
{
    Q_D(const Checkable);

    return d->checkedIcon->icon();
}

void Checkable::setUncheckedIcon(const QIcon &icon)
{
    Q_D(Checkable);

    d->uncheckedIcon->setIcon(icon);
    update();
}

QIcon Checkable::uncheckedIcon() const
{
    Q_D(const Checkable);

    return d->uncheckedIcon->icon();
}

/*!
 *  \reimp
 */
QSize Checkable::sizeHint() const
{
    if (text().isEmpty()) {
        return QSize(40, 40);
    }
    return QSize(fontMetrics().size(Qt::TextShowMnemonic, text()).width()+52, 40);
}

Checkable::Checkable(CheckablePrivate &d, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
bool Checkable::event(QEvent *event)
{
    Q_D(Checkable);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move:
        d->checkedIcon->setGeometry(rect());
        d->uncheckedIcon->setGeometry(rect());
        d->rippleOverlay->setGeometry(geometry().adjusted(-8, -8, 8, 8));
        break;
    case QEvent::ParentChange:
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->rippleOverlay->setParent(widget);
        }
        break;
    default:
        break;
    }
    return QAbstractButton::event(event);
}

/*!
 *  \reimp
 */
bool Checkable::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(Checkable);

        d->rippleOverlay->setGeometry(geometry().adjusted(-8, -8, 8, 8));
    }
    return QAbstractButton::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void Checkable::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    Q_D(Checkable);

    if (!isEnabled()) {
        return;
    }

    Ripple *ripple;
    if (Checkable::LabelPositionLeft == d->labelPosition) {
         ripple = new Ripple(QPoint(width()-14, 28));
    } else {
         ripple = new Ripple(QPoint(28, 28));
    }
    ripple->setRadiusEndValue(22);
    ripple->setColor(isChecked() ? checkedColor() : uncheckedColor());
    if (isChecked()) {
        ripple->setOpacityStartValue(1);
    }
    d->rippleOverlay->addRipple(ripple);

    setChecked(!isChecked());
}

/*!
 *  \reimp
 */
void Checkable::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Checkable);

    QPainter painter(this);

    QPen pen;
    pen.setColor(isEnabled() ? textColor() : disabledColor());
    painter.setPen(pen);

    if (Checkable::LabelPositionLeft == d->labelPosition) {
        painter.drawText(4, 25, text());
    } else {
        painter.drawText(48, 25, text());
    }
}

void Checkable::setupProperties()
{
    Q_D(Checkable);

    d->checkedState->assignProperty(d->checkedIcon, "color", checkedColor());
    d->checkedState->assignProperty(d->uncheckedIcon, "color", checkedColor());
    d->uncheckedState->assignProperty(d->uncheckedIcon, "color", uncheckedColor());
    d->disabledUncheckedState->assignProperty(d->uncheckedIcon, "color", disabledColor());
    d->disabledCheckedState->assignProperty(d->checkedIcon, "color", disabledColor());

    if (isEnabled()) {
        if (isChecked()) {
            d->checkedIcon->setColor(checkedColor());
        } else {
            d->uncheckedIcon->setColor(uncheckedColor());
        }
    } else {
        d->checkedIcon->setColor(disabledColor());
        d->uncheckedIcon->setColor(disabledColor());
    }

    update();
}

}
