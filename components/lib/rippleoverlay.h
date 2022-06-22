#ifndef RIPPLEOVERLAY_H
#define RIPPLEOVERLAY_H

#include <QPainterPath>
#include "lib/overlaywidget.h"

namespace md
{
class Ripple;

class RippleOverlay : public OverlayWidget
{
    Q_OBJECT

public:
    explicit RippleOverlay(QWidget *parent = 0);
    ~RippleOverlay();

    void addRipple(Ripple *ripple);
    void addRipple(const QPoint &position, qreal radius = 300);

    void removeRipple(Ripple *ripple);

    inline void setClipping(bool enable);
    inline bool hasClipping() const;

    inline void setClipPath(const QPainterPath &path);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    inline QList<Ripple *> ripples() const;

private:
    Q_DISABLE_COPY(RippleOverlay)

    void paintRipple(QPainter *painter, Ripple *ripple);

    QList<Ripple *> m_ripples;
    QPainterPath              m_clipPath;
    bool                      m_useClip;
};

inline void RippleOverlay::setClipping(bool enable)
{
    m_useClip = enable;
    update();
}

inline bool RippleOverlay::hasClipping() const
{
    return m_useClip;
}

inline void RippleOverlay::setClipPath(const QPainterPath &path)
{
    m_clipPath = path;
    update();
}

inline QList<Ripple *> RippleOverlay::ripples() const
{
    return m_ripples;
}
}

#endif // RIPPLEOVERLAY_H
