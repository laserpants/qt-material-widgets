#ifndef QTMATERIALPROGRESS_P_H
#define QTMATERIALPROGRESS_P_H

#include <QtGlobal>
#include <QColor>
#include "lib/qtmaterialtheme.h"

class QtMaterialProgress;
class QtMaterialProgressDelegate;

class QtMaterialProgressPrivate
{
    Q_DISABLE_COPY(QtMaterialProgressPrivate)
    Q_DECLARE_PUBLIC(QtMaterialProgress)

public:
    QtMaterialProgressPrivate(QtMaterialProgress *q);
    ~QtMaterialProgressPrivate();

    void init();

    QtMaterialProgress         *const q_ptr;
    QtMaterialProgressDelegate *delegate;
    Material::ProgressType      progressType;
    QColor                      progressColor;
    QColor                      backgroundColor;
    bool                        useThemeColors;
};

#endif // QTMATERIALPROGRESS_P_H
