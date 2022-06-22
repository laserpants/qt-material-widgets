#ifndef TABS_P_H
#define TABS_P_H

#include <QtGlobal>
#include <QtWidgets/QHBoxLayout>

#include "lib/theme.h"

namespace md
{

class Tabs;
class TabsInkBar;

class TabsPrivate
{
    Q_DISABLE_COPY(TabsPrivate)
    Q_DECLARE_PUBLIC(Tabs)

public:
    TabsPrivate(Tabs *q);
    ~TabsPrivate();

    void init();

    Tabs       *const q_ptr;
    TabsInkBar *inkBar;
    QHBoxLayout          *tabLayout;
    Material::RippleStyle rippleStyle;
    QColor                inkColor;
    QColor                backgroundColor;
    QColor                textColor;
    int                   tab;
    bool                  showHalo;
    bool                  useThemeColors;
};
}
#endif // TABS_P_H
