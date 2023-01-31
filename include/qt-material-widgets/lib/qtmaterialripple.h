#ifndef QTMATERIALRIPPLE_H
#define QTMATERIALRIPPLE_H

#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QPoint>
#include <QBrush>

class QtMaterialRippleOverlay;

class QtMaterialRipple : public QParallelAnimationGroup
{
    Q_OBJECT

    Q_PROPERTY(qreal radius WRITE setRadius READ radius)
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    explicit QtMaterialRipple(const QPoint &center, QObject *parent = 0);
    QtMaterialRipple(const QPoint &center, QtMaterialRippleOverlay *overlay, QObject *parent = 0);
    ~QtMaterialRipple();

    inline void setOverlay(QtMaterialRippleOverlay *overlay);

    void setRadius(qreal radius);
    inline qreal radius() const;

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

    void setColor(const QColor &color);
    inline QColor color() const;

    void setBrush(const QBrush &brush);
    inline QBrush brush() const;

    inline QPoint center() const;

    inline QPropertyAnimation *radiusAnimation() const;
    inline QPropertyAnimation *opacityAnimation() const;

    inline void setOpacityStartValue(qreal value);
    inline void setOpacityEndValue(qreal value);
    inline void setRadiusStartValue(qreal value);
    inline void setRadiusEndValue(qreal value);
    inline void setDuration(int msecs);

protected slots:
    void destroy();

private:
    Q_DISABLE_COPY(QtMaterialRipple)

    QPropertyAnimation *animate(const QByteArray &property,
                                const QEasingCurve &easing = QEasingCurve::OutQuad,
                                int duration = 800);

    void init();

    QtMaterialRippleOverlay  *m_overlay;
    QPropertyAnimation *const m_radiusAnimation;
    QPropertyAnimation *const m_opacityAnimation;
    qreal                     m_radius;
    qreal                     m_opacity;
    QPoint                    m_center;
    QBrush                    m_brush;
};

inline void QtMaterialRipple::setOverlay(QtMaterialRippleOverlay *overlay)
{
    m_overlay = overlay;
}

inline qreal QtMaterialRipple::radius() const
{
    return m_radius;
}

inline qreal QtMaterialRipple::opacity() const
{
    return m_opacity;
}

inline QColor QtMaterialRipple::color() const
{
    return m_brush.color();
}

inline QBrush QtMaterialRipple::brush() const
{
    return m_brush;
}

inline QPoint QtMaterialRipple::center() const
{
    return m_center;
}

inline QPropertyAnimation *QtMaterialRipple::radiusAnimation() const
{
    return m_radiusAnimation;
}

inline QPropertyAnimation *QtMaterialRipple::opacityAnimation() const
{
    return m_opacityAnimation;
}

inline void QtMaterialRipple::setOpacityStartValue(qreal value)
{
    m_opacityAnimation->setStartValue(value);
}

inline void QtMaterialRipple::setOpacityEndValue(qreal value)
{
    m_opacityAnimation->setEndValue(value);
}

inline void QtMaterialRipple::setRadiusStartValue(qreal value)
{
    m_radiusAnimation->setStartValue(value);
}

inline void QtMaterialRipple::setRadiusEndValue(qreal value)
{
    m_radiusAnimation->setEndValue(value);
}

inline void QtMaterialRipple::setDuration(int msecs)
{
    m_radiusAnimation->setDuration(msecs);
    m_opacityAnimation->setDuration(msecs);
}

#endif // QTMATERIALRIPPLE_H
