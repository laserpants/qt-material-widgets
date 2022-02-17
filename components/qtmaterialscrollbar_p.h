#ifndef QTMATERIALSCROLLBAR_P_H
#define QTMATERIALSCROLLBAR_P_H

#include <QtGlobal>
#include <QColor>
namespace md
{

class ScrollBar;
class ScrollBarStateMachine;

class ScrollBarPrivate
{
    Q_DISABLE_COPY(ScrollBarPrivate)
    Q_DECLARE_PUBLIC(ScrollBar)

public:
    ScrollBarPrivate(ScrollBar *q);
    ~ScrollBarPrivate();

    void init();

    ScrollBar             *const q_ptr;
    ScrollBarStateMachine *stateMachine;
    QColor                           backgroundColor;
    QColor                           sliderColor;
    QColor                           canvasColor;
    bool                             hideOnMouseOut;
    bool                             useThemeColors;
};
}
#endif // QTMATERIALSCROLLBAR_P_H
