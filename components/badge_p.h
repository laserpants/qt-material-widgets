#ifndef BADGE_P_H
#define BADGE_P_H

#include <QtGlobal>
#include <QSize>
#include <QIcon>
#include <QColor>
#include <QPainter>

namespace md
{
class Badge;

class BadgePrivate
{
    Q_DISABLE_COPY(BadgePrivate)
    Q_DECLARE_PUBLIC(Badge)

public:
    BadgePrivate(Badge *q);
    ~BadgePrivate();

    void init();

    Badge *const q_ptr;
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
}

#endif // BADGE_P_H
