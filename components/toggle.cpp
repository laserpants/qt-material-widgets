#include "toggle.h"

#include "toggle_p.h"
#include "toggle_internal.h"
#include "lib/style.h"

namespace md
{

/*!
 *  \class QtMaterialTogglePrivate
 *  \internal
 */

TogglePrivate::TogglePrivate(Toggle *q)
    : q_ptr(q)
{
}

TogglePrivate::~TogglePrivate()
{
}

void TogglePrivate::init()
{
    Q_Q(Toggle);

    track          = new ToggleTrack(q);
    thumb          = new ToggleThumb(q);
    rippleOverlay  = new ToggleRippleOverlay(thumb, track, q);
    stateMachine   = new QStateMachine(q);
    offState       = new QState;
    onState        = new QState;
    orientation    = Qt::Horizontal;
    useThemeColors = true;

    q->setCheckable(true);
    q->setChecked(false);
    q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    stateMachine->addState(offState);
    stateMachine->addState(onState);
    stateMachine->setInitialState(offState);

    offState->assignProperty(thumb, "shift", 0);
    onState->assignProperty(thumb, "shift", 1);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    //

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(onState);
    offState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(offState);
    onState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    setupProperties();

    stateMachine->start();
    QCoreApplication::processEvents();
}

void TogglePrivate::setupProperties()
{
    Q_Q(Toggle);

    if (q->isEnabled()) {
        const qreal shift = thumb->shift();
        if (qFuzzyCompare(shift, 1)) {
            thumb->setThumbColor(q->activeColor());
            track->setTrackColor(q->activeColor().lighter(110));
        } else if (qFuzzyCompare(1+shift, 1)) {
            thumb->setThumbColor(q->inactiveColor());
            track->setTrackColor(q->trackColor());
        }
    }

    offState->assignProperty(track, "trackColor", q->trackColor().lighter(110));
    onState->assignProperty(track, "trackColor", q->activeColor().lighter(110));

    offState->assignProperty(thumb, "thumbColor", q->inactiveColor());
    onState->assignProperty(thumb, "thumbColor", q->activeColor());

    q->update();
}

/*!
 *  \class QtMaterialToggle
 */

Toggle::Toggle(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new TogglePrivate(this))
{
    d_func()->init();
}

Toggle::~Toggle()
{
}

void Toggle::setUseThemeColors(bool value)
{
    Q_D(Toggle);

    d->useThemeColors = value;
    d->setupProperties();
}

bool Toggle::useThemeColors() const
{
    Q_D(const Toggle);

    return d->useThemeColors;
}

void Toggle::setDisabledColor(const QColor &color)
{
    Q_D(Toggle);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->setupProperties();
}

QColor Toggle::disabledColor() const
{
    Q_D(const Toggle);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return Style::instance().themeColor("disabled");
    } else {
        return d->disabledColor;
    }
}

void Toggle::setActiveColor(const QColor &color)
{
    Q_D(Toggle);

    d->activeColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->setupProperties();
}

QColor Toggle::activeColor() const
{
    Q_D(const Toggle);

    if (d->useThemeColors || !d->activeColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->activeColor;
    }
}

void Toggle::setInactiveColor(const QColor &color)
{
    Q_D(Toggle);

    d->inactiveColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->setupProperties();
}

QColor Toggle::inactiveColor() const
{
    Q_D(const Toggle);

    if (d->useThemeColors || !d->inactiveColor.isValid()) {
        return Style::instance().themeColor("canvas");
    } else {
        return d->inactiveColor;
    }
}

void Toggle::setTrackColor(const QColor &color)
{
    Q_D(Toggle);

    d->trackColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->setupProperties();
}

QColor Toggle::trackColor() const
{
    Q_D(const Toggle);

    if (d->useThemeColors || !d->trackColor.isValid()) {
        return Style::instance().themeColor("accent3");
    } else {
        return d->trackColor;
    }
}

void Toggle::setOrientation(Qt::Orientation orientation)
{
    Q_D(Toggle);

    if (d->orientation == orientation) {
        return;
    }

    d->orientation = orientation;
    updateGeometry();
}

Qt::Orientation Toggle::orientation() const
{
    Q_D(const Toggle);

    return d->orientation;
}

QSize Toggle::sizeHint() const
{
    Q_D(const Toggle);

    return Qt::Horizontal == d->orientation
        ? QSize(64, 48)
        : QSize(48, 64);
}

bool Toggle::event(QEvent *event)
{
    Q_D(Toggle);

    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->rippleOverlay->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QAbstractButton::event(event);
}

void Toggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
}
}
