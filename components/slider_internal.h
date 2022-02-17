#ifndef SLIDER_INTERNAL_H
#define SLIDER_INTERNAL_H

#include <QStateMachine>
#include "lib/overlaywidget.h"
namespace md
{

class Slider;
class SliderThumb;
class SliderTrack;

class SliderStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    SliderStateMachine(Slider *slider,
                                 SliderThumb *thumb,
                                 SliderTrack *track);
    ~SliderStateMachine();

    void setupProperties();

private:
    Q_DISABLE_COPY(SliderStateMachine)

    Slider      *const m_slider;
    SliderThumb *const m_thumb;
    SliderTrack *const m_track;
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

class SliderThumb : public OverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal diameter WRITE setDiameter READ diameter)
    Q_PROPERTY(qreal borderWidth WRITE setBorderWidth READ borderWidth)
    Q_PROPERTY(QColor borderColor WRITE setBorderColor READ borderColor)
    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)
    Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)
    Q_PROPERTY(QColor haloColor WRITE setHaloColor READ haloColor)

public:
    explicit SliderThumb(Slider *slider);
    ~SliderThumb();

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
    Q_DISABLE_COPY(SliderThumb)

    const Slider *const m_slider;
    QColor                        m_borderColor;
    QColor                        m_fillColor;
    QColor                        m_haloColor;
    qreal                         m_diameter;
    qreal                         m_borderWidth;
    qreal                         m_haloSize;
    int                           m_offset;
};

inline void SliderThumb::setDiameter(qreal diameter)
{
    m_diameter = diameter;
    update();
}

inline qreal SliderThumb::diameter() const
{
    return m_diameter;
}

inline void SliderThumb::setBorderWidth(qreal width)
{
    m_borderWidth = width;
    update();
}

inline qreal SliderThumb::borderWidth() const
{
    return m_borderWidth;
}

inline void SliderThumb::setBorderColor(const QColor &color)
{
    m_borderColor = color;
    update();
}

inline QColor SliderThumb::borderColor() const
{
    return m_borderColor;
}

inline void SliderThumb::setFillColor(const QColor &color)
{
    m_fillColor = color;
    update();
}

inline QColor SliderThumb::fillColor() const
{
    return m_fillColor;
}

inline void SliderThumb::setHaloSize(qreal size)
{
    m_haloSize = size;
    update();
}

inline qreal SliderThumb::haloSize() const
{
    return m_haloSize;
}

inline void SliderThumb::setHaloColor(const QColor &color)
{
    m_haloColor = color;
    update();
}

inline QColor SliderThumb::haloColor() const
{
    return m_haloColor;
}

inline void SliderThumb::setOffset(int offset)
{
    m_offset = offset;
    update();
}

inline int SliderThumb::offset() const
{
    return m_offset;
}

class SliderTrack : public OverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)

public:
    explicit SliderTrack(SliderThumb *thumb, Slider *slider);
    ~SliderTrack();

    inline void setFillColor(const QColor &color);
    inline QColor fillColor() const;

    inline void setTrackWidth(int width);
    inline int trackWidth() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(SliderTrack)

    const Slider *const m_slider;
    SliderThumb  *const m_thumb;
    QColor                        m_fillColor;
    int                           m_trackWidth;
};

inline void SliderTrack::setFillColor(const QColor &color)
{
    m_fillColor = color;
    update();
}

inline QColor SliderTrack::fillColor() const
{
    return m_fillColor;
}

void SliderTrack::setTrackWidth(int width)
{
    m_trackWidth = width;
    update();
}

int SliderTrack::trackWidth() const
{
    return m_trackWidth;
}
}
#endif // SLIDER_INTERNAL_H
