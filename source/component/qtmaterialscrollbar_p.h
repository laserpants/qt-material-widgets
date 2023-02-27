#ifndef QTMATERIALSCROLLBAR_P_H
#define QTMATERIALSCROLLBAR_P_H

#include <QtGlobal>
#include <QColor>

class QtMaterialScrollBar;
class QtMaterialScrollBarStateMachine;

class QtMaterialScrollBarPrivate
{
    Q_DISABLE_COPY(QtMaterialScrollBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialScrollBar)

public:
    QtMaterialScrollBarPrivate(QtMaterialScrollBar *q);
    ~QtMaterialScrollBarPrivate();

    void init();

    QtMaterialScrollBar             *const q_ptr;
    QtMaterialScrollBarStateMachine *stateMachine;
    QColor                           backgroundColor;
    QColor                           sliderColor;
    QColor                           canvasColor;
    bool                             hideOnMouseOut;
    bool                             useThemeColors;
};

#endif // QTMATERIALSCROLLBAR_P_H
