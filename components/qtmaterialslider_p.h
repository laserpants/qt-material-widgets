#ifndef QTMATERIALSLIDER_P_H
#define QTMATERIALSLIDER_P_H

#include <QtGlobal>
#include <QColor>
#include <QRectF>

namespace md
{

class Slider;
class SliderThumb;
class SliderTrack;
class SliderStateMachine;

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
    Q_DECLARE_PUBLIC(Slider)

public:
    SliderPrivate(Slider *q);
    ~SliderPrivate();

    void init();

    QRectF trackBoundingRect() const;
    QRectF thumbBoundingRect() const;

    int valueFromPosition(const QPoint &pos) const;

    void setHovered(bool status);

    Slider             *const q_ptr;
    SliderThumb        *thumb;
    SliderTrack        *track;
    SliderStateMachine *stateMachine;
    QColor                        thumbColor;
    QColor                        trackColor;
    QColor                        disabledColor;
    int                           stepTo;
    int                           oldValue;
    int                           trackWidth;
    bool                          hoverTrack;
    bool                          hoverThumb;
    bool                          hover;
    bool                          step;
    bool                          pageStepMode;
    bool                          useThemeColors;
};
}
#endif // QTMATERIALSLIDER_P_H
