#include "qtmaterialslider_internal.h"
#include <QState>
#include <QAbstractTransition>
#include <QSignalTransition>
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QPainter>
#include "qtmaterialslider.h"
#include "lib/qtmaterialstyle.h"
#include "lib/qtmaterialstatetransition.h"

/*!
 *  \class QtMaterialSliderStateMachine
 *  \internal
 */

QtMaterialSliderStateMachine::QtMaterialSliderStateMachine(
        QtMaterialSlider      *slider,
        QtMaterialSliderThumb *thumb,
        QtMaterialSliderTrack *track)
    : QStateMachine(slider),
      m_slider(slider),
      m_thumb(thumb),
      m_track(track),
      m_topState(new QState(QState::ParallelStates)),
      m_fstState(new QState(m_topState)),
      m_sndState(new QState(m_topState)),
      m_inactiveState(new QState(m_fstState)),
      m_focusState(new QState(m_fstState)),
      m_slidingState(new QState(m_fstState)),
      m_pulseOutState(new QState(m_focusState)),
      m_pulseInState(new QState(m_focusState)),
      m_minState(new QState(m_sndState)),
      m_normalState(new QState(m_sndState))
{
    addState(m_topState);
    setInitialState(m_topState);

    m_fstState->setInitialState(m_inactiveState);
    m_focusState->setInitialState(m_pulseOutState);

    m_inactiveState->assignProperty(thumb, "haloSize", 0);
    m_slidingState->assignProperty(thumb, "haloSize", 0);

    m_pulseOutState->assignProperty(thumb, "haloSize", 35);
    m_pulseInState->assignProperty(thumb, "haloSize", 28);

    m_inactiveState->assignProperty(thumb, "diameter", 11);
    m_focusState->assignProperty(thumb, "diameter", 11);
    m_slidingState->assignProperty(thumb, "diameter", 17);

    QAbstractTransition *transition;
    QtMaterialStateTransition *customTransition;
    QPropertyAnimation *animation;

    // Show halo on mouse enter

    customTransition = new QtMaterialStateTransition(SliderNoFocusMouseEnter);
    customTransition->setTargetState(m_focusState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    customTransition->addAnimation(animation);
    customTransition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    m_inactiveState->addTransition(customTransition);

    // Show halo on focus in

    transition = new QEventTransition(slider, QEvent::FocusIn);
    transition->setTargetState(m_focusState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    m_inactiveState->addTransition(transition);

    // Hide halo on focus out

    transition = new QEventTransition(slider, QEvent::FocusOut);
    transition->setTargetState(m_inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    transition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    m_focusState->addTransition(transition);

    // Hide halo on mouse leave, except if widget has focus

    customTransition = new QtMaterialStateTransition(SliderNoFocusMouseLeave);
    customTransition->setTargetState(m_inactiveState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    customTransition->addAnimation(animation);
    customTransition->addAnimation(new QPropertyAnimation(track, "fillColor", this));
    m_focusState->addTransition(customTransition);

    // Pulse in

    transition = new QSignalTransition(m_pulseOutState, SIGNAL(propertiesAssigned()));
    transition->setTargetState(m_pulseInState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setDuration(1000);
    transition->addAnimation(animation);
    m_pulseOutState->addTransition(transition);

    // Pulse out

    transition = new QSignalTransition(m_pulseInState, SIGNAL(propertiesAssigned()));
    transition->setTargetState(m_pulseOutState);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setDuration(1000);
    transition->addAnimation(animation);
    m_pulseInState->addTransition(transition);

    // Slider pressed

    transition = new QSignalTransition(slider, SIGNAL(sliderPressed()));
    transition->setTargetState(m_slidingState);
    animation = new QPropertyAnimation(thumb, "diameter", this);
    animation->setDuration(70);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    m_focusState->addTransition(transition);

    // Slider released

    transition = new QSignalTransition(slider, SIGNAL(sliderReleased()));
    transition->setTargetState(m_focusState);
    animation = new QPropertyAnimation(thumb, "diameter", this);
    animation->setDuration(70);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloSize", this);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    transition->addAnimation(animation);
    m_slidingState->addTransition(transition);

    // Min. value transitions

    m_minState->assignProperty(thumb, "borderWidth", 2);
    m_normalState->assignProperty(thumb, "borderWidth", 0);

    m_sndState->setInitialState(m_minState);

    customTransition = new QtMaterialStateTransition(SliderChangedFromMinimum);
    customTransition->setTargetState(m_normalState);

    animation = new QPropertyAnimation(thumb, "fillColor", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloColor", this);
    animation->setDuration(300);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderColor", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderWidth", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    m_minState->addTransition(customTransition);

    customTransition = new QtMaterialStateTransition(SliderChangedToMinimum);
    customTransition->setTargetState(m_minState);

    animation = new QPropertyAnimation(thumb, "fillColor", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "haloColor", this);
    animation->setDuration(300);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderColor", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    animation = new QPropertyAnimation(thumb, "borderWidth", this);
    animation->setDuration(200);
    customTransition->addAnimation(animation);

    m_normalState->addTransition(customTransition);

    setupProperties();
}

QtMaterialSliderStateMachine::~QtMaterialSliderStateMachine()
{
}

void QtMaterialSliderStateMachine::setupProperties()
{
    QColor trackColor = m_slider->trackColor();
    QColor thumbColor = m_slider->thumbColor();

    m_inactiveState->assignProperty(m_track, "fillColor", trackColor.lighter(130));
    m_slidingState->assignProperty(m_track, "fillColor", trackColor);
    m_focusState->assignProperty(m_track, "fillColor", trackColor);

    QColor holeColor = m_slider->palette().color(QPalette::Base);

    if (m_slider->parentWidget()) {
        holeColor = m_slider->parentWidget()->palette().color(m_slider->backgroundRole());
    }

    m_minState->assignProperty(m_thumb, "fillColor", holeColor);

    m_minState->assignProperty(m_thumb, "haloColor", trackColor);
    m_minState->assignProperty(m_thumb, "borderColor", trackColor);

    m_normalState->assignProperty(m_thumb, "fillColor", thumbColor);
    m_normalState->assignProperty(m_thumb, "haloColor", thumbColor);
    m_normalState->assignProperty(m_thumb, "borderColor", thumbColor);

    m_slider->update();
}

/*!
 *  \class QtMaterialSliderThumb
 *  \internal
 */

QtMaterialSliderThumb::QtMaterialSliderThumb(QtMaterialSlider *slider)
    : QtMaterialOverlayWidget(slider->parentWidget()),
      m_slider(slider),
      m_diameter(11),
      m_borderWidth(2),
      m_haloSize(0),
      m_offset(0)
{
    slider->installEventFilter(this);

    setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

QtMaterialSliderThumb::~QtMaterialSliderThumb()
{
}

bool QtMaterialSliderThumb::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        setParent(m_slider->parentWidget());
    }

    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void QtMaterialSliderThumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Halo

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(m_haloColor);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QPointF disp = Qt::Horizontal == m_slider->orientation()
        ? QPointF(QT_MATERIAL_SLIDER_MARGIN + m_offset, m_slider->height()/2)
        : QPointF(m_slider->width()/2, QT_MATERIAL_SLIDER_MARGIN + m_offset);

    QRectF halo((m_slider->pos() - QPointF(m_haloSize, m_haloSize)/2) + disp,
                QSizeF(m_haloSize, m_haloSize));

    painter.setOpacity(0.15);
    painter.drawEllipse(halo);

    // Knob

    const bool isMin = m_slider->value() == m_slider->minimum();

    brush.setColor(m_slider->isEnabled()
           ? m_fillColor
           : m_slider->disabledColor());
    painter.setBrush(!m_slider->isEnabled() && isMin
           ? Qt::NoBrush
           : brush);

    if (m_slider->isEnabled() || isMin) {
        QPen pen;
        pen.setColor(m_borderColor);
        pen.setWidthF((isMin && !m_slider->isEnabled()) ? 1.7 : m_borderWidth);
        painter.setPen(pen);
    } else {
        painter.setPen(Qt::NoPen);
    }

    QRectF geometry = Qt::Horizontal == m_slider->orientation()
        ? QRectF(m_offset, m_slider->height()/2 - QT_MATERIAL_SLIDER_MARGIN,
                 QT_MATERIAL_SLIDER_MARGIN*2, QT_MATERIAL_SLIDER_MARGIN*2).translated(m_slider->pos())
        : QRectF(m_slider->width()/2 - QT_MATERIAL_SLIDER_MARGIN, m_offset,
                 QT_MATERIAL_SLIDER_MARGIN*2, QT_MATERIAL_SLIDER_MARGIN*2).translated(m_slider->pos());

    qreal s = m_slider->isEnabled() ? m_diameter : 7;

    QRectF thumb(0, 0, s, s);

    thumb.moveCenter(geometry.center());

    painter.setOpacity(1);
    painter.drawEllipse(thumb);
}

/*!
 *  \class QtMaterialSliderTrack
 *  \internal
 */

QtMaterialSliderTrack::QtMaterialSliderTrack(QtMaterialSliderThumb *thumb, QtMaterialSlider *slider)
    : QtMaterialOverlayWidget(slider->parentWidget()),
      m_slider(slider),
      m_thumb(thumb),
      m_trackWidth(2)
{
    slider->installEventFilter(this);

    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(update()));
}

QtMaterialSliderTrack::~QtMaterialSliderTrack()
{
}

bool QtMaterialSliderTrack::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::ParentChange == event->type()) {
        setParent(m_slider->parentWidget());
    }

    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void QtMaterialSliderTrack::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush fg;
    fg.setStyle(Qt::SolidPattern);
    fg.setColor(m_slider->isEnabled() ? m_slider->thumbColor()
                                      : m_slider->disabledColor());
    QBrush bg;
    bg.setStyle(Qt::SolidPattern);
    bg.setColor(m_slider->isEnabled() ? m_fillColor
                                      : m_slider->disabledColor());

    qreal offset = m_thumb->offset();

    if (Qt::Horizontal == m_slider->orientation()) {
        painter.translate(m_slider->x() + QT_MATERIAL_SLIDER_MARGIN,
                          m_slider->y() + m_slider->height()/2
                                        - static_cast<qreal>(m_trackWidth)/2);
    } else {
        painter.translate(m_slider->x() + m_slider->width()/2
                                        - static_cast<qreal>(m_trackWidth)/2,
                          m_slider->y() + QT_MATERIAL_SLIDER_MARGIN);
    }

    QRectF geometry = Qt::Horizontal == m_slider->orientation()
        ? QRectF(0, 0, m_slider->width() - QT_MATERIAL_SLIDER_MARGIN*2, m_trackWidth)
        : QRectF(0, 0, m_trackWidth, m_slider->height() - QT_MATERIAL_SLIDER_MARGIN*2);

    QRectF bgRect;
    QRectF fgRect;

    if (Qt::Horizontal == m_slider->orientation()) {
        fgRect = QRectF(0, 0, offset, m_trackWidth);
        bgRect = QRectF(offset, 0, m_slider->width(), m_trackWidth).intersected(geometry);
    } else {
        fgRect = QRectF(0, 0, m_trackWidth, offset);
        bgRect = QRectF(0, offset, m_trackWidth, m_slider->height()).intersected(geometry);
    }

    if (!m_slider->isEnabled()) {
        fgRect = fgRect.width() < 9 ? QRectF() : fgRect.adjusted(0, 0, -6, 0);
        bgRect = bgRect.width() < 9 ? QRectF() : bgRect.adjusted(6, 0, 0, 0);
    }

    if (m_slider->invertedAppearance()) {
        qSwap(bgRect, fgRect);
    }

    painter.fillRect(bgRect, bg);
    painter.fillRect(fgRect, fg);
}
