#include "ripple.h"
#include "lib/rippleoverlay.h"

namespace md
{
/*!
 *  \class QtMaterialRipple
 *  \internal
 */

Ripple::Ripple(const QPoint &center, QObject *parent)
    : QParallelAnimationGroup(parent),
      m_overlay(0),
      m_radiusAnimation(animate("radius")),
      m_opacityAnimation(animate("opacity")),
      m_radius(0),
      m_opacity(0),
      m_center(center)
{
    init();
}

Ripple::Ripple(const QPoint &center,
                                   RippleOverlay *overlay,
                                   QObject *parent)
    : QParallelAnimationGroup(parent),
      m_overlay(overlay),
      m_radiusAnimation(animate("radius")),
      m_opacityAnimation(animate("opacity")),
      m_radius(0),
      m_opacity(0),
      m_center(center)
{
    init();
}

Ripple::~Ripple()
{
}

void Ripple::setRadius(qreal radius)
{
    Q_ASSERT(m_overlay);

    if (m_radius == radius) {
        return;
    }
    m_radius = radius;
    m_overlay->update();
}

void Ripple::setOpacity(qreal opacity)
{
    Q_ASSERT(m_overlay);

    if (m_opacity == opacity) {
        return;
    }
    m_opacity = opacity;
    m_overlay->update();
}

void Ripple::setColor(const QColor &color)
{
    if (m_brush.color() == color) {
        return;
    }
    m_brush.setColor(color);

    if (m_overlay) {
        m_overlay->update();
    }
}

void Ripple::setBrush(const QBrush &brush)
{
    m_brush = brush;

    if (m_overlay) {
        m_overlay->update();
    }
}

void Ripple::destroy()
{
    Q_ASSERT(m_overlay);

    m_overlay->removeRipple(this);
}

/*!
 *  \internal
 */
QPropertyAnimation *Ripple::animate(const QByteArray &property,
                                              const QEasingCurve &easing,
                                              int duration)
{
    QPropertyAnimation *animation = new QPropertyAnimation;
    animation->setTargetObject(this);
    animation->setPropertyName(property);
    animation->setEasingCurve(easing);
    animation->setDuration(duration);
    addAnimation(animation);
    return animation;
}

/*!
 *  \internal
 */
void Ripple::init()
{
    setOpacityStartValue(0.5);
    setOpacityEndValue(0);
    setRadiusStartValue(0);
    setRadiusEndValue(300);

    m_brush.setColor(Qt::black);
    m_brush.setStyle(Qt::SolidPattern);

    connect(this, SIGNAL(finished()), this, SLOT(destroy()));
}

}
