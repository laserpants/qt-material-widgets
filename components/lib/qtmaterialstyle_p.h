#ifndef QTMATERIALSTYLE_P_H
#define QTMATERIALSTYLE_P_H

#include <QtGlobal>

namespace md
{
class Style;
class Theme;

class StylePrivate
{
    Q_DISABLE_COPY(StylePrivate)
    Q_DECLARE_PUBLIC(Style)

public:
    StylePrivate(Style *q);
    ~StylePrivate();

    void init();

    Style *const q_ptr;
    Theme *theme;
};
}

#endif // QTMATERIALSTYLE_P_H
