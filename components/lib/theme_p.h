#ifndef THEME_P_H
#define THEME_P_H

#include <QHash>
#include <QColor>
#include <QString>
#include <QStringBuilder>
#include <QDir>
#include <QDebug>

namespace md
{
class Theme;

class ThemePrivate
{
    Q_DISABLE_COPY(ThemePrivate)
    Q_DECLARE_PUBLIC(Theme)

public:
    ThemePrivate(Theme *q);
    ~ThemePrivate();

    QColor rgba(int r, int g, int b, qreal a) const;

    Theme *const q_ptr;
    QHash<QString, QColor> colors;
};
}

#endif // THEME_P_H
