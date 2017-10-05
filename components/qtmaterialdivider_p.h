#ifndef QTMATERIALDIVIDER_P_H
#define QTMATERIALDIVIDER_P_H

#include <QtGlobal>
#include <QColor>
#include "lib/qtmaterialtheme.h"

class QtMaterialDivider;

class QtMaterialDividerPrivate
{
    Q_DISABLE_COPY(QtMaterialDividerPrivate)
    Q_DECLARE_PUBLIC(QtMaterialDivider)

public:
    QtMaterialDividerPrivate(QtMaterialDivider *q);
    ~QtMaterialDividerPrivate();

    void init();

    QtMaterialDivider *const q_ptr;
    int                     size;
};

#endif // QTMATERIALDIVIDER_P_H
