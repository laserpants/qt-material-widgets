#ifndef PROGRESS_P_H
#define PROGRESS_P_H

#include <QtGlobal>
#include <QColor>
#include "lib/theme.h"
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
#endif // PROGRESS_P_H
