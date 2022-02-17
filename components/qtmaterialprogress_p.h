#ifndef QTMATERIALPROGRESS_P_H
#define QTMATERIALPROGRESS_P_H

#include <QtGlobal>
#include <QColor>
#include "lib/qtmaterialtheme.h"
namespace md
{

class ProgressBar;
class ProgressBarDelegate;

class ProgressBarPrivate
{
    Q_DISABLE_COPY(ProgressBarPrivate)
    Q_DECLARE_PUBLIC(ProgressBar)

public:
    ProgressBarPrivate(ProgressBar *q);
    ~ProgressBarPrivate();

    void init();

    ProgressBar         *const q_ptr;
    ProgressBarDelegate *delegate;
    Material::ProgressType      progressType;
    QColor                      progressColor;
    QColor                      backgroundColor;
    bool                        useThemeColors;
};
}
#endif // QTMATERIALPROGRESS_P_H
