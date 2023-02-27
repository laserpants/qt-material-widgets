#include "qtmaterialslider.h"
#include "qtmaterialslider_p.h"
#include <QtWidgets/QApplication>
#include <QMouseEvent>
#include "qtmaterialslider_internal.h"
#include "lib/qtmaterialstyle.h"
#include "lib/qtmaterialstatetransitionevent.h"

/*!
 *  \class QtMaterialSliderPrivate
 *  \internal
 */

QtMaterialSliderPrivate::QtMaterialSliderPrivate(QtMaterialSlider *q)
    : q_ptr(q)
{
}

QtMaterialSliderPrivate::~QtMaterialSliderPrivate()
{
}

void QtMaterialSliderPrivate::init()
{
    Q_Q(QtMaterialSlider);

    thumb          = new QtMaterialSliderThumb(q);
    track          = new QtMaterialSliderTrack(thumb, q);
    stateMachine   = new QtMaterialSliderStateMachine(q, thumb, track);
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

QRectF QtMaterialSliderPrivate::trackBoundingRect() const
{
    Q_Q(const QtMaterialSlider);

    qreal hw = static_cast<qreal>(trackWidth)/2;

    return Qt::Horizontal == q->orientation()
        ? QRectF(QT_MATERIAL_SLIDER_MARGIN, q->height()/2 - hw,
                 q->width() - QT_MATERIAL_SLIDER_MARGIN*2, hw*2)
        : QRectF(q->width()/2 - hw, QT_MATERIAL_SLIDER_MARGIN, hw*2,
                 q->height() - QT_MATERIAL_SLIDER_MARGIN*2);
}

QRectF QtMaterialSliderPrivate::thumbBoundingRect() const
{
    Q_Q(const QtMaterialSlider);

    return Qt::Horizontal == q->orientation()
        ? QRectF(thumb->offset(), q->height()/2 - QT_MATERIAL_SLIDER_MARGIN,
                 QT_MATERIAL_SLIDER_MARGIN*2, QT_MATERIAL_SLIDER_MARGIN*2)
        : QRectF(q->width()/2 - QT_MATERIAL_SLIDER_MARGIN, thumb->offset(),
                 QT_MATERIAL_SLIDER_MARGIN*2, QT_MATERIAL_SLIDER_MARGIN*2);
}

int QtMaterialSliderPrivate::valueFromPosition(const QPoint &pos) const
{
    Q_Q(const QtMaterialSlider);

    const int position = Qt::Horizontal == q->orientation() ? pos.x() : pos.y();

    const int span = Qt::Horizontal == q->orientation()
        ? q->width() - QT_MATERIAL_SLIDER_MARGIN*2
        : q->height() - QT_MATERIAL_SLIDER_MARGIN*2;

    return QtMaterialStyle::sliderValueFromPosition(
                q->minimum(),
                q->maximum(),
                position - QT_MATERIAL_SLIDER_MARGIN,
                span,
                q->invertedAppearance());
}

void QtMaterialSliderPrivate::setHovered(bool status)
{
    Q_Q(QtMaterialSlider);

    if (hover == status) {
        return;
    }

    hover = status;

    if (!q->hasFocus()) {
        if (status) {
            stateMachine->postEvent(new QtMaterialStateTransitionEvent(SliderNoFocusMouseEnter));
        } else {
            stateMachine->postEvent(new QtMaterialStateTransitionEvent(SliderNoFocusMouseLeave));
        }
    }

    q->update();
}

/*!
 *  \class QtMaterialSlider
 */

QtMaterialSlider::QtMaterialSlider(QWidget *parent)
    : QAbstractSlider(parent),
      d_ptr(new QtMaterialSliderPrivate(this))
{
    d_func()->init();
}

QtMaterialSlider::~QtMaterialSlider()
{
}

void QtMaterialSlider::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSlider);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool QtMaterialSlider::useThemeColors() const
{
    Q_D(const QtMaterialSlider);

    return d->useThemeColors;
}

void QtMaterialSlider::setThumbColor(const QColor &color)
{
    Q_D(QtMaterialSlider);

    d->thumbColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
    update();
}

QColor QtMaterialSlider::thumbColor() const
{
    Q_D(const QtMaterialSlider);

    if (d->useThemeColors || !d->thumbColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->thumbColor;
    }
}

void QtMaterialSlider::setTrackColor(const QColor &color)
{
    Q_D(QtMaterialSlider);

    d->trackColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
    update();
}

QColor QtMaterialSlider::trackColor() const
{
    Q_D(const QtMaterialSlider);

    if (d->useThemeColors || !d->trackColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent3");
    } else {
        return d->trackColor;
    }
}

void QtMaterialSlider::setDisabledColor(const QColor &color)
{
    Q_D(QtMaterialSlider);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
    update();
}

QColor QtMaterialSlider::disabledColor() const
{
    Q_D(const QtMaterialSlider);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("disabled");
    } else {
        return d->disabledColor;
    }
}

void QtMaterialSlider::setPageStepMode(bool pageStep)
{
    Q_D(QtMaterialSlider);

    d->pageStepMode = pageStep;
}

bool QtMaterialSlider::pageStepMode() const
{
    Q_D(const QtMaterialSlider);

    return d->pageStepMode;
}

/*!
 *  \remip
 */
QSize QtMaterialSlider::minimumSizeHint() const
{
    return Qt::Horizontal == orientation()
            ? QSize(130, 34)
            : QSize(34, 130);
}

void QtMaterialSlider::setInvertedAppearance(bool value)
{
    QAbstractSlider::setInvertedAppearance(value);

    updateThumbOffset();
}

/*!
 *  \remip
 */
void QtMaterialSlider::sliderChange(SliderChange change)
{
    Q_D(QtMaterialSlider);

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
            d->stateMachine->postEvent(new QtMaterialStateTransitionEvent(SliderChangedToMinimum));
        } else if (maximum() == value()) {
            triggerAction(SliderToMaximum);
        }
        if (minimum() == d->oldValue) {
            d->stateMachine->postEvent(new QtMaterialStateTransitionEvent(SliderChangedFromMinimum));
        }
        d->oldValue = value();
    }

    updateThumbOffset();

    QAbstractSlider::sliderChange(change);
}

/*!
 *  \remip
 */
void QtMaterialSlider::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(QtMaterialSlider);

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
void QtMaterialSlider::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialSlider);

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
void QtMaterialSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QtMaterialSlider);

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
void QtMaterialSlider::leaveEvent(QEvent *event)
{
    Q_D(QtMaterialSlider);

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

void QtMaterialSlider::updateThumbOffset()
{
    Q_D(QtMaterialSlider);

    const int offset = QtMaterialStyle::sliderPositionFromValue(
        minimum(),
        maximum(),
        sliderPosition(),
        Qt::Horizontal == orientation()
            ? width() - QT_MATERIAL_SLIDER_MARGIN*2
            : height() - QT_MATERIAL_SLIDER_MARGIN*2,
        invertedAppearance());

    d->thumb->setOffset(offset);
}
