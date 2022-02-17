#ifndef STYLE_P_H
#define STYLE_P_H

#include <QtGlobal>
#include <QFontDatabase>
#include <QDir>

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

#endif // STYLE_P_H
