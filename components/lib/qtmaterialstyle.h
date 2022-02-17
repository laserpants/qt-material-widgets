#ifndef QTMATERIALSTYLE_H
#define QTMATERIALSTYLE_H

#include <QtWidgets/QCommonStyle>
#include "lib/qtmaterialstyle_p.h"

#define MATERIAL_DISABLE_THEME_COLORS \
    if (d->useThemeColors == true) { d->useThemeColors = false; }

namespace md
{
class Theme;

class Style : public QCommonStyle
{
    Q_OBJECT

public:
    inline static Style &instance();

    void setTheme(Theme *theme);
    QColor themeColor(const QString &key) const;

protected:
    const QScopedPointer<StylePrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(Style)

    Style();

    Style(Style const &);
    void operator=(Style const &);
};

inline Style &Style::instance()
{
    static Style instance;
    return instance;
}
}

#endif // QTMATERIALSTYLE_H
