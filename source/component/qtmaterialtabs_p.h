#ifndef QTMATERIALTABS_P_H
#define QTMATERIALTABS_P_H

#include <QtGlobal>
#include "lib/qtmaterialtheme.h"

class QHBoxLayout;
class QtMaterialTabs;
class QtMaterialTabsInkBar;

class QtMaterialTabsPrivate
{
    Q_DISABLE_COPY(QtMaterialTabsPrivate)
    Q_DECLARE_PUBLIC(QtMaterialTabs)

public:
    QtMaterialTabsPrivate(QtMaterialTabs *q);
    ~QtMaterialTabsPrivate();

    void init();

    QtMaterialTabs       *const q_ptr;
    QtMaterialTabsInkBar *inkBar;
    QHBoxLayout          *tabLayout;
    Material::RippleStyle rippleStyle;
    QColor                inkColor;
    QColor                backgroundColor;
    QColor                textColor;
    int                   tab;
    bool                  showHalo;
    bool                  useThemeColors;
};

#endif // QTMATERIALTABS_P_H
