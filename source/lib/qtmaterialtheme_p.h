#ifndef QTMATERIALTHEME_P_H
#define QTMATERIALTHEME_P_H

#include <QHash>
#include <QColor>

class QtMaterialTheme;

class QtMaterialThemePrivate
{
    Q_DISABLE_COPY(QtMaterialThemePrivate)
    Q_DECLARE_PUBLIC(QtMaterialTheme)

public:
    QtMaterialThemePrivate(QtMaterialTheme *q);
    ~QtMaterialThemePrivate();

    QColor rgba(int r, int g, int b, qreal a) const;

    QtMaterialTheme *const q_ptr;
    QHash<QString, QColor> colors;
};

#endif // QTMATERIALTHEME_P_H
