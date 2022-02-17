#include "qtmaterialslider.h"
#include "qtmaterialslider_p.h"
#include <QtWidgets/QApplication>
#include <QMouseEvent>
#include "qtmaterialslider_internal.h"
#include "lib/qtmaterialstyle.h"
#include "lib/qtmaterialstatetransitionevent.h"

namespace md
{

/*!
 *  \class QtMaterialSliderPrivate
 *  \internal
 */

SliderPrivate::SliderPrivate(Slider *q)
    : q_ptr(q)
{
}

SliderPrivate::~SliderPrivate()
{
}

void SliderPrivate::init()
{
    Q_Q(Slider);

    thumb          = new SliderThumb(q);
    track          = new SliderTrack(thumb, q);
    stateMachine   = new SliderStateMachine(q, thumb, track);
    stepTo         = 0;
    oldValue       = q->value();
    trackWidth     = 2;
    hoverTrack     = false;
    hoverThumb     = false;
    hover          = false;
    step           = false;
    pageStepMode   = true;
    useThemeColors = true;

    q->setMouseTracking(true);
    q->setFocusPolicy(Qt::StrongFocus);
    q->setPageStep(1);

    QSizePolicy sp(QSizePolicy::Expanding,
                   QSizePolicy::Fixed);

    if (q->orientation() == Qt::Vertical) {
        sp.transpose();
    }

    q->setSizePolicy(sp);
    q->setAttribute(Qt::WA_WState_OwnSizePolicy, false);

    stateMachine->start();
    QCoreApplication::processEvents();
}

QRectF SliderPrivate::trackBoundingRect() const
{
    Q_Q(const Slider);

    qreal hw = static_cast<qreal>(trackWidth)/2;

    return Qt::Horizontal == q->orientation()
        ? QRectF(QT_MATERIAL_SLIDER_MARGIN, q->height()/2 - hw,
                 q->width() - QT_MATERIAL_SLIDER_MARGIN*2, hw*2)
        : QRectF(q->width()/2 - hw, QT_MATERIAL_SLIDER_MARGIN, hw*2,
                 q->height() - QT_MATERIAL_SLIDER_MARGIN*2);
}

QRectF SliderPrivate::thumbBoundingRect() const
{
    Q_Q(const Slider);

    return Qt::Horizontal == q->orientation()
        ? QRectF(thumb->offset(), q->height()/2 - QT_MATERIAL_SLIDER_MARGIN,
                 QT_MATERIAL_SLIDER_MARGIN*2, QT_MATERIAL_SLIDER_MARGIN*2)
        : QRectF(q->width()/2 - QT_MATERIAL_SLIDER_MARGIN, thumb->offset(),
                 QT_MATERIAL_SLIDER_MARGIN*2, QT_MATERIAL_SLIDER_MARGIN*2);
}

int SliderPrivate::valueFromPosition(const QPoint &pos) const
{
    Q_Q(const Slider);

    const int position = Qt::Horizontal == q->orientation() ? pos.x() : pos.y();

    const int span = Qt::Horizontal == q->orientation()
        ? q->width() - QT_MATERIAL_SLIDER_MARGIN*2
        : q->height() - QT_MATERIAL_SLIDER_MARGIN*2;

    return Style::sliderValueFromPosition(
                q->minimum(),
                q->maximum(),
                position - QT_MATERIAL_SLIDER_MARGIN,
                span,
                q->invertedAppearance());
}

void SliderPrivate::setHovered(bool status)
{
    Q_Q(Slider);

    if (hover == status) {
        return;
    }

    hover = status;

    if (!q->hasFocus()) {
        if (status) {
            stateMachine->postEvent(new StateTransitionEvent(SliderNoFocusMouseEnter));
        } else {
            stateMachine->postEvent(new StateTransitionEvent(SliderNoFocusMouseLeave));
        }
    }

    q->update();
}

/*!
 *  \class QtMaterialSlider
 */

Slider::Slider(QWidget *parent)
    : QAbstractSlider(parent),
      d_ptr(new SliderPrivate(this))
{
    d_func()->init();
}

Slider::~Slider()
{
}

void Slider::setUseThemeColors(bool value)
{
    Q_D(Slider);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool Slider::useThemeColors() const
{
    Q_D(const Slider);

    return d->useThemeColors;
}

void Slider::setThumbColor(const QColor &color)
{
    Q_D(Slider);

    d->thumbColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
    update();
}

QColor Slider::thumbColor() const
{
    Q_D(const Slider);

    if (d->useThemeColors || !d->thumbColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->thumbColor;
    }
}

void Slider::setTrackColor(const QColor &color)
{
    Q_D(Slider);

    d->trackColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
    update();
}

QColor Slider::trackColor() const
{
    Q_D(const Slider);

    if (d->useThemeColors || !d->trackColor.isValid()) {
        return Style::instance().themeColor("accent3");
    } else {
        return d->trackColor;
    }
}

void Slider::setDisabledColor(const QColor &color)
{
    Q_D(Slider);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
    update();
}

QColor Slider::disabledColor() const
{
    Q_D(const Slider);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return Style::instance().themeColor("disabled");
    } else {
        return d->disabledColor;
    }
}

void Slider::setPageStepMode(bool pageStep)
{
    Q_D(Slider);

    d->pageStepMode = pageStep;
}

bool Slider::pageStepMode() const
{
    Q_D(const Slider);

    return d->pageStepMode;
}

/*!
 *  \remip
 */
QSize Slider::minimumSizeHint() const
{
    return Qt::Horizontal == orientation()
            ? QSize(130, 34)
            : QSize(34, 130);
}

void Slider::setInvertedAppearance(bool value)
{
    QAbstractSlider::setInvertedAppearance(value);

    updateThumbOffset();
}

/*!
 *  \remip
 */
void Slider::sliderChange(SliderChange change)
{
    Q_D(Slider);

    if (SliderOrientationChange == change)
    {
        QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
        if (orientation() == Qt::Vertical) {
            sp.transpose();
        }
        setSizePolicy(sp);
    }
    else if (SliderValueChange == change)
    {
        if (minimum() == value()) {
            triggerAction(SliderToMinimum);
            d->stateMachine->postEvent(new StateTransitionEvent(SliderChangedToMinimum));
        } else if (maximum() == value()) {
            triggerAction(SliderToMaximum);
        }
        if (minimum() == d->oldValue) {
            d->stateMachine->postEvent(new StateTransitionEvent(SliderChangedFromMinimum));
        }
        d->oldValue = value();
    }

    updateThumbOffset();

    QAbstractSlider::sliderChange(change);
}

/*!
 *  \remip
 */
void Slider::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(Slider);

    if (isSliderDown())
    {
        setSliderPosition(d->valueFromPosition(event->pos()));
    }
    else
    {
        QRectF track(d->trackBoundingRect().adjusted(-2, -2, 2, 2));

        if (track.contains(event->pos()) != d->hoverTrack) {
            d->hoverTrack = !d->hoverTrack;
            update();
        }

        QRectF thumb(0, 0, 16, 16);
        thumb.moveCenter(d->thumbBoundingRect().center());

        if (thumb.contains(event->pos()) != d->hoverThumb) {
            d->hoverThumb = !d->hoverThumb;
            update();
        }

        d->setHovered(d->hoverTrack || d->hoverThumb);
    }

    QAbstractSlider::mouseMoveEvent(event);
}

/*!
 *  \remip
 */
void Slider::mousePressEvent(QMouseEvent *event)
{
    Q_D(Slider);

    const QPoint pos = event->pos();

    QRectF thumb(0, 0, 16, 16);
    thumb.moveCenter(d->thumbBoundingRect().center());

    if (thumb.contains(pos)) {
        setSliderDown(true);
        return;
    }

    if (!d->pageStepMode) {
        setSliderPosition(d->valueFromPosition(event->pos()));
        d->thumb->setHaloSize(0);
        setSliderDown(true);
        return;
    }

    d->step = true;
    d->stepTo = d->valueFromPosition(pos);

    SliderAction action = d->stepTo > sliderPosition()
        ? SliderPageStepAdd
        : SliderPageStepSub;

    triggerAction(action);
    setRepeatAction(action, 400, 8);
}

/*!
 *  \remip
 */
void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(Slider);

    if (isSliderDown()) {
        setSliderDown(false);
    } else if (d->step) {
        d->step = false;
        setRepeatAction(SliderNoAction, 0);
    }

    QAbstractSlider::mouseReleaseEvent(event);
}

/*!
 *  \remip
 */
void Slider::leaveEvent(QEvent *event)
{
    Q_D(Slider);

    if (d->hoverTrack) {
        d->hoverTrack = false;
        update();
    }
    if (d->hoverThumb) {
        d->hoverThumb = false;
        update();
    }

    d->setHovered(false);

    QAbstractSlider::leaveEvent(event);
}

void Slider::updateThumbOffset()
{
    Q_D(Slider);

    const int offset = Style::sliderPositionFromValue(
        minimum(),
        maximum(),
        sliderPosition(),
        Qt::Horizontal == orientation()
            ? width() - QT_MATERIAL_SLIDER_MARGIN*2
            : height() - QT_MATERIAL_SLIDER_MARGIN*2,
        invertedAppearance());

    d->thumb->setOffset(offset);
}
}
