#ifndef QTMATERIALTOGGLE_INTERNAL_H
#define QTMATERIALTOGGLE_INTERNAL_H

#include <QtWidgets/QWidget>
#include "lib/qtmaterialrippleoverlay.h"

class QtMaterialToggle;
class QtMaterialToggleThumb;
class QtMaterialToggleTrack;

class QtMaterialToggleRippleOverlay : public QtMaterialRippleOverlay
{
    Q_OBJECT

public:
    QtMaterialToggleRippleOverlay(QtMaterialToggleThumb *thumb,
                                  QtMaterialToggleTrack *track,
                                  QtMaterialToggle *parent);
    ~QtMaterialToggleRippleOverlay();

protected slots:
    void addToggleRipple();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    QRect overlayGeometry() const Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialToggleRippleOverlay)

    QtMaterialToggle      *const m_toggle;
    QtMaterialToggleThumb *const m_thumb;
    QtMaterialToggleTrack *const m_track;
};

class QtMaterialToggleThumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal shift WRITE setShift READ shift)
    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)

public:
    QtMaterialToggleThumb(QtMaterialToggle *parent);
    ~QtMaterialToggleThumb();

    void setShift(qreal shift);
    inline qreal shift() const;

    inline qreal offset() const;

    inline void setThumbColor(const QColor &color);
    inline QColor thumbColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialToggleThumb)

    void updateOffset();

    QtMaterialToggle *const m_toggle;
    QColor                  m_thumbColor;
    qreal                   m_shift;
    qreal                   m_offset;
};

inline qreal QtMaterialToggleThumb::shift() const
{
    return m_shift;
}

inline qreal QtMaterialToggleThumb::offset() const
{
    return m_offset;
}

inline void QtMaterialToggleThumb::setThumbColor(const QColor &color)
{
    m_thumbColor = color;
    update();
}

inline QColor QtMaterialToggleThumb::thumbColor() const
{
    return m_thumbColor;
}

class QtMaterialToggleTrack : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
    QtMaterialToggleTrack(QtMaterialToggle *parent);
    ~QtMaterialToggleTrack();

    void setTrackColor(const QColor &color);
    inline QColor trackColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialToggleTrack)

    QtMaterialToggle *const m_toggle;
    QColor                  m_trackColor;
};

inline QColor QtMaterialToggleTrack::trackColor() const
{
    return m_trackColor;
}

#endif // QTMATERIALTOGGLE_INTERNAL_H
