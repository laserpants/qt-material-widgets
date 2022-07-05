#ifndef QTMATERIALSLIDER_INTERNAL_H
#define QTMATERIALSLIDER_INTERNAL_H

#include <QStateMachine>
#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialSlider;
class QtMaterialSliderThumb;
class QtMaterialSliderTrack;

class QtMaterialSliderStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    QtMaterialSliderStateMachine(QtMaterialSlider *slider,
                                 QtMaterialSliderThumb *thumb,
                                 QtMaterialSliderTrack *track);
    ~QtMaterialSliderStateMachine();

    void setupProperties();

private:
    Q_DISABLE_COPY(QtMaterialSliderStateMachine)

    QtMaterialSlider      *const m_slider;
    QtMaterialSliderThumb *const m_thumb;
    QtMaterialSliderTrack *const m_track;
    QState                *const m_topState;
    QState                *const m_fstState;
    QState                *const m_sndState;
    QState                *const m_inactiveState;
    QState                *const m_focusState;
    QState                *const m_slidingState;
    QState                *const m_pulseOutState;
    QState                *const m_pulseInState;
    QState                *const m_minState;
    QState                *const m_normalState;
};

class QtMaterialSliderThumb : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal diameter WRITE setDiameter READ diameter)
    Q_PROPERTY(qreal borderWidth WRITE setBorderWidth READ borderWidth)
    Q_PROPERTY(QColor borderColor WRITE setBorderColor READ borderColor)
    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)
    Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)
    Q_PROPERTY(QColor haloColor WRITE setHaloColor READ haloColor)

public:
    explicit QtMaterialSliderThumb(QtMaterialSlider *slider);
    ~QtMaterialSliderThumb();

    inline void setDiameter(qreal diameter);
    inline qreal diameter() const;

    inline void setBorderWidth(qreal width);
    inline qreal borderWidth() const;

    inline void setBorderColor(const QColor &color);
    inline QColor borderColor() const;

    inline void setFillColor(const QColor &color);
    inline QColor fillColor() const;

    inline void setHaloSize(qreal size);
    inline qreal haloSize() const;

    inline void setHaloColor(const QColor &color);
    inline QColor haloColor() const;

    inline void setOffset(int offset);
    inline int offset() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialSliderThumb)

    const QtMaterialSlider *const m_slider;
    QColor                        m_borderColor;
    QColor                        m_fillColor;
    QColor                        m_haloColor;
    qreal                         m_diameter;
    qreal                         m_borderWidth;
    qreal                         m_haloSize;
    int                           m_offset;
};

inline void QtMaterialSliderThumb::setDiameter(qreal diameter)
{
    m_diameter = diameter;
    update();
}

inline qreal QtMaterialSliderThumb::diameter() const
{
    return m_diameter;
}

inline void QtMaterialSliderThumb::setBorderWidth(qreal width)
{
    m_borderWidth = width;
    update();
}

inline qreal QtMaterialSliderThumb::borderWidth() const
{
    return m_borderWidth;
}

inline void QtMaterialSliderThumb::setBorderColor(const QColor &color)
{
    m_borderColor = color;
    update();
}

inline QColor QtMaterialSliderThumb::borderColor() const
{
    return m_borderColor;
}

inline void QtMaterialSliderThumb::setFillColor(const QColor &color)
{
    m_fillColor = color;
    update();
}

inline QColor QtMaterialSliderThumb::fillColor() const
{
    return m_fillColor;
}

inline void QtMaterialSliderThumb::setHaloSize(qreal size)
{
    m_haloSize = size;
    update();
}

inline qreal QtMaterialSliderThumb::haloSize() const
{
    return m_haloSize;
}

inline void QtMaterialSliderThumb::setHaloColor(const QColor &color)
{
    m_haloColor = color;
    update();
}

inline QColor QtMaterialSliderThumb::haloColor() const
{
    return m_haloColor;
}

inline void QtMaterialSliderThumb::setOffset(int offset)
{
    m_offset = offset;
    update();
}

inline int QtMaterialSliderThumb::offset() const
{
    return m_offset;
}

class QtMaterialSliderTrack : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)

public:
    explicit QtMaterialSliderTrack(QtMaterialSliderThumb *thumb, QtMaterialSlider *slider);
    ~QtMaterialSliderTrack();

    inline void setFillColor(const QColor &color);
    inline QColor fillColor() const;

    inline void setTrackWidth(int width);
    inline int trackWidth() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialSliderTrack)

    const QtMaterialSlider *const m_slider;
    QtMaterialSliderThumb  *const m_thumb;
    QColor                        m_fillColor;
    int                           m_trackWidth;
};

inline void QtMaterialSliderTrack::setFillColor(const QColor &color)
{
    m_fillColor = color;
    update();
}

inline QColor QtMaterialSliderTrack::fillColor() const
{
    return m_fillColor;
}

void QtMaterialSliderTrack::setTrackWidth(int width)
{
    m_trackWidth = width;
    update();
}

int QtMaterialSliderTrack::trackWidth() const
{
    return m_trackWidth;
}

#endif // QTMATERIALSLIDER_INTERNAL_H
