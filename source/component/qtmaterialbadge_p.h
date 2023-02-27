#ifndef QTMATERIALBADGE_P_H
#define QTMATERIALBADGE_P_H

#include <QtGlobal>
#include <QSize>
#include <QIcon>
#include <QColor>

class QtMaterialBadge;

class QtMaterialBadgePrivate
{
    Q_DISABLE_COPY(QtMaterialBadgePrivate)
    Q_DECLARE_PUBLIC(QtMaterialBadge)

public:
    QtMaterialBadgePrivate(QtMaterialBadge *q);
    ~QtMaterialBadgePrivate();

    void init();

    QtMaterialBadge *const q_ptr;
    QString                text;
    QColor                 textColor;
    QColor                 backgroundColor;
    QSize                  size;
    QIcon                  icon;
    qreal                  x;
    qreal                  y;
    int                    padding;
    bool                   useThemeColors;
};

#endif // QTMATERIALBADGE_P_H
