#ifndef QTMATERIALCIRCULARPROGRESS_P_H
#define QTMATERIALCIRCULARPROGRESS_P_H

#include <QtGlobal>
#include "lib/qtmaterialtheme.h"
namespace md
{

class CircularProgress;
class CircularProgressDelegate;

class CircularProgressPrivate
{
    Q_DISABLE_COPY(CircularProgressPrivate)
    Q_DECLARE_PUBLIC(CircularProgress)

public:
    CircularProgressPrivate(CircularProgress *q);
    ~CircularProgressPrivate();

    void init();

    CircularProgress         *const q_ptr;
    CircularProgressDelegate *delegate;
    Material::ProgressType              progressType;
    QColor                              color;
    qreal                               penWidth;
    int                                 size;
    bool                                useThemeColors;
};

}

#endif // QTMATERIALCIRCULARPROGRESS_P_H
