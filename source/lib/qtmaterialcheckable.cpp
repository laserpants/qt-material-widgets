#include "lib/qtmaterialcheckable.h"
#include "lib/qtmaterialcheckable_p.h"
#include <QPainter>
#include <QEvent>
#include <QStateMachine>
#include <QSignalTransition>
#include <QEventTransition>
#include <QColor>
#include <QCoreApplication>
#include "lib/qtmaterialrippleoverlay.h"
#include "lib/qtmaterialripple.h"
#include "lib/qtmaterialstyle.h"
#include "lib/qtmaterialcheckable_internal.h"

/*!
 *  \class QtMaterialCheckablePrivate
 *  \internal
 */

QtMaterialCheckablePrivate::QtMaterialCheckablePrivate(QtMaterialCheckable *q)
    : q_ptr(q)
{
}

QtMaterialCheckablePrivate::~QtMaterialCheckablePrivate()
{
}

void QtMaterialCheckablePrivate::init()
{
    Q_Q(QtMaterialCheckable);

    rippleOverlay          = new QtMaterialRippleOverlay;
    checkedIcon            = new QtMaterialCheckableIcon(QIcon(":/icons/icons/toggle/svg/production/ic_check_box_24px.svg"), q);
    uncheckedIcon          = new QtMaterialCheckableIcon(QIcon(":/icons/icons/toggle/svg/production/ic_check_box_outline_blank_24px.svg"), q);
    stateMachine           = new QStateMachine(q);
    uncheckedState         = new QState;
    checkedState           = new QState;
    disabledUncheckedState = new QState;
    disabledCheckedState   = new QState;
    uncheckedTransition    = new QSignalTransition(q, SIGNAL(toggled(bool)));
    checkedTransition      = new QSignalTransition(q, SIGNAL(toggled(bool)));
    labelPosition          = QtMaterialCheckable::LabelPositionRight;
    useThemeColors         = true;

    rippleOverlay->setParent(q->parentWidget());
    rippleOverlay->installEventFilter(q);

    q->setCheckable(true);
    q->setStyle(&QtMaterialStyle::instance());
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

QtMaterialCheckable::QtMaterialCheckable(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new QtMaterialCheckablePrivate(this))
{
    d_func()->init();
}

QtMaterialCheckable::~QtMaterialCheckable()
{
}

void QtMaterialCheckable::setLabelPosition(LabelPosition placement)
{
    Q_D(QtMaterialCheckable);

    d->labelPosition = placement;
    update();
}

QtMaterialCheckable::LabelPosition QtMaterialCheckable::labelPosition() const
{
    Q_D(const QtMaterialCheckable);

    return d->labelPosition;
}

void QtMaterialCheckable::setUseThemeColors(bool value)
{
    Q_D(QtMaterialCheckable);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    setupProperties();
}

bool QtMaterialCheckable::useThemeColors() const
{
    Q_D(const QtMaterialCheckable);

    return d->useThemeColors;
}

void QtMaterialCheckable::setCheckedColor(const QColor &color)
{
    Q_D(QtMaterialCheckable);

    d->checkedColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    setupProperties();
}

QColor QtMaterialCheckable::checkedColor() const
{
    Q_D(const QtMaterialCheckable);

    if (d->useThemeColors || !d->checkedColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->checkedColor;
    }
}

void QtMaterialCheckable::setUncheckedColor(const QColor &color)
{
    Q_D(QtMaterialCheckable);

    d->uncheckedColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    setupProperties();
}

QColor QtMaterialCheckable::uncheckedColor() const
{
    Q_D(const QtMaterialCheckable);

    if (d->useThemeColors || !d->uncheckedColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->uncheckedColor;
    }
}

void QtMaterialCheckable::setTextColor(const QColor &color)
{
    Q_D(QtMaterialCheckable);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    setupProperties();
}

QColor QtMaterialCheckable::textColor() const
{
    Q_D(const QtMaterialCheckable);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void QtMaterialCheckable::setDisabledColor(const QColor &color)
{
    Q_D(QtMaterialCheckable);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    setupProperties();
}

QColor QtMaterialCheckable::disabledColor() const
{
    Q_D(const QtMaterialCheckable);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent3");
    } else {
        return d->disabledColor;
    }
}

void QtMaterialCheckable::setCheckedIcon(const QIcon &icon)
{
    Q_D(QtMaterialCheckable);

    d->checkedIcon->setIcon(icon);
    update();
}

QIcon QtMaterialCheckable::checkedIcon() const
{
    Q_D(const QtMaterialCheckable);

    return d->checkedIcon->icon();
}

void QtMaterialCheckable::setUncheckedIcon(const QIcon &icon)
{
    Q_D(QtMaterialCheckable);

    d->uncheckedIcon->setIcon(icon);
    update();
}

QIcon QtMaterialCheckable::uncheckedIcon() const
{
    Q_D(const QtMaterialCheckable);

    return d->uncheckedIcon->icon();
}

/*!
 *  \reimp
 */
QSize QtMaterialCheckable::sizeHint() const
{
    if (text().isEmpty()) {
        return QSize(40, 40);
    }
    return QSize(fontMetrics().size(Qt::TextShowMnemonic, text()).width()+52, 40);
}

QtMaterialCheckable::QtMaterialCheckable(QtMaterialCheckablePrivate &d, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
bool QtMaterialCheckable::event(QEvent *event)
{
    Q_D(QtMaterialCheckable);

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
bool QtMaterialCheckable::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(QtMaterialCheckable);

        d->rippleOverlay->setGeometry(geometry().adjusted(-8, -8, 8, 8));
    }
    return QAbstractButton::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void QtMaterialCheckable::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialCheckable);

    if (!isEnabled()) {
        return;
    }

    QtMaterialRipple *ripple;
    if (QtMaterialCheckable::LabelPositionLeft == d->labelPosition) {
         ripple = new QtMaterialRipple(QPoint(width()-14, 28));
    } else {
         ripple = new QtMaterialRipple(QPoint(28, 28));
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
void QtMaterialCheckable::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialCheckable);

    QPainter painter(this);

    QPen pen;
    pen.setColor(isEnabled() ? textColor() : disabledColor());
    painter.setPen(pen);

    if (QtMaterialCheckable::LabelPositionLeft == d->labelPosition) {
        painter.drawText(4, 25, text());
    } else {
        painter.drawText(48, 25, text());
    }
}

void QtMaterialCheckable::setupProperties()
{
    Q_D(QtMaterialCheckable);

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
