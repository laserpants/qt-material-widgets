#include "lib/qtmaterialrippleoverlay.h"
#include <QPainter>
#include "lib/qtmaterialripple.h"

/*!
 *  \class QtMaterialRippleOverlay
 *  \internal
 */

QtMaterialRippleOverlay::QtMaterialRippleOverlay(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      m_useClip(false)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

QtMaterialRippleOverlay::~QtMaterialRippleOverlay()
{
}

void QtMaterialRippleOverlay::addRipple(QtMaterialRipple *ripple)
{
    ripple->setOverlay(this);
    m_ripples.push_back(ripple);
    ripple->start();

    connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(stop()));
    connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(deleteLater()));
}

void QtMaterialRippleOverlay::addRipple(const QPoint &position, qreal radius)
{
    QtMaterialRipple *ripple = new QtMaterialRipple(position);
    ripple->setRadiusEndValue(radius);
    addRipple(ripple);
}

void QtMaterialRippleOverlay::removeRipple(QtMaterialRipple *ripple)
{
    if (m_ripples.removeOne(ripple)) {
        delete ripple;
        update();
    }
}

/*!
 *  \reimp
 */
void QtMaterialRippleOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if (m_useClip) {
        painter.setClipPath(m_clipPath);
    }

    QList<QtMaterialRipple *>::const_iterator i;
    for (i = m_ripples.begin(); i != m_ripples.end(); ++i) {
        paintRipple(&painter, *i);
    }
}

void QtMaterialRippleOverlay::paintRipple(QPainter *painter, QtMaterialRipple *ripple)
{
    const qreal radius = ripple->radius();
    const QPointF center = ripple->center();
    painter->setOpacity(ripple->opacity());
    painter->setBrush(ripple->brush());
    painter->drawEllipse(center, radius, radius);
}
