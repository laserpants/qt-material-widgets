#ifndef QTMATERIALTOGGLE_INTERNAL_H
#define QTMATERIALTOGGLE_INTERNAL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QPainter>
#include <QEvent>

#include "lib/qtmaterialrippleoverlay.h"

namespace md
{

class Toggle;
class ToggleThumb;
class ToggleTrack;

class ToggleRippleOverlay : public RippleOverlay
{
    Q_OBJECT

public:
    ToggleRippleOverlay(ToggleThumb *thumb,
                                  ToggleTrack *track,
                                  Toggle *parent);
    ~ToggleRippleOverlay();

protected slots:
    void addToggleRipple();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    QRect overlayGeometry() const Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(ToggleRippleOverlay)

    Toggle      *const m_toggle;
    ToggleThumb *const m_thumb;
    ToggleTrack *const m_track;
};

class ToggleThumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal shift WRITE setShift READ shift)
    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)

public:
    ToggleThumb(Toggle *parent);
    ~ToggleThumb();

    void setShift(qreal shift);
    inline qreal shift() const;

    inline qreal offset() const;

    inline void setThumbColor(const QColor &color);
    inline QColor thumbColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(ToggleThumb)

    void updateOffset();

    Toggle *const m_toggle;
    QColor                  m_thumbColor;
    qreal                   m_shift;
    qreal                   m_offset;
};

inline qreal ToggleThumb::shift() const
{
    return m_shift;
}

inline qreal ToggleThumb::offset() const
{
    return m_offset;
}

inline void ToggleThumb::setThumbColor(const QColor &color)
{
    m_thumbColor = color;
    update();
}

inline QColor ToggleThumb::thumbColor() const
{
    return m_thumbColor;
}

class ToggleTrack : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
    ToggleTrack(Toggle *parent);
    ~ToggleTrack();

    void setTrackColor(const QColor &color);
    inline QColor trackColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(ToggleTrack)

    Toggle *const m_toggle;
    QColor                  m_trackColor;
};

inline QColor ToggleTrack::trackColor() const
{
    return m_trackColor;
}
}
#endif // QTMATERIALTOGGLE_INTERNAL_H
