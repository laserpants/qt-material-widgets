#ifndef QTMATERIALSLIDER_P_H
#define QTMATERIALSLIDER_P_H

#include <QtGlobal>
#include <QColor>
#include <QRectF>

class QtMaterialSlider;
class QtMaterialSliderThumb;
class QtMaterialSliderTrack;
class QtMaterialSliderStateMachine;

class QtMaterialSliderPrivate
{
    Q_DISABLE_COPY(QtMaterialSliderPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSlider)

public:
    QtMaterialSliderPrivate(QtMaterialSlider *q);
    ~QtMaterialSliderPrivate();

    void init();

    QRectF trackBoundingRect() const;
    QRectF thumbBoundingRect() const;

    int valueFromPosition(const QPoint &pos) const;

    void setHovered(bool status);

    QtMaterialSlider             *const q_ptr;
    QtMaterialSliderThumb        *thumb;
    QtMaterialSliderTrack        *track;
    QtMaterialSliderStateMachine *stateMachine;
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

#endif // QTMATERIALSLIDER_P_H
