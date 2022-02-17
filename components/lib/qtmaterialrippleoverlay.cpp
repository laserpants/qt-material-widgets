#include "lib/qtmaterialrippleoverlay.h"
#include <QPainter>
#include "lib/qtmaterialripple.h"

namespace md
{
/*!
 *  \class QtMaterialRippleOverlay
 *  \internal
 */

RippleOverlay::RippleOverlay(QWidget *parent)
    : OverlayWidget(parent),
      m_useClip(false)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

RippleOverlay::~RippleOverlay()
{
}

void RippleOverlay::addRipple(Ripple *ripple)
{
    ripple->setOverlay(this);
    m_ripples.push_back(ripple);
    ripple->start();

    connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(stop()));
    connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(deleteLater()));
}

void RippleOverlay::addRipple(const QPoint &position, qreal radius)
{
    Ripple *ripple = new Ripple(position);
    ripple->setRadiusEndValue(radius);
    addRipple(ripple);
}

void RippleOverlay::removeRipple(Ripple *ripple)
{
    if (m_ripples.removeOne(ripple)) {
        delete ripple;
        update();
    }
}

/*!
 *  \reimp
 */
void RippleOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if (m_useClip) {
        painter.setClipPath(m_clipPath);
    }

    QList<Ripple *>::const_iterator i;
    for (i = m_ripples.begin(); i != m_ripples.end(); ++i) {
        paintRipple(&painter, *i);
    }
}

void RippleOverlay::paintRipple(QPainter *painter, Ripple *ripple)
{
    const qreal radius = ripple->radius();
    const QPointF center = ripple->center();
    painter->setOpacity(ripple->opacity());
    painter->setBrush(ripple->brush());
    painter->drawEllipse(center, radius, radius);
}

}
