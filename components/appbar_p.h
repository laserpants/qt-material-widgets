#ifndef APPBAR_P_H
#define APPBAR_P_H

#include <QtGlobal>
#include <QColor>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QPainter>

namespace md
{

class AppBar;

class AppBarPrivate
{
    Q_DISABLE_COPY(AppBarPrivate)
    Q_DECLARE_PUBLIC(AppBar)

public:
    AppBarPrivate(AppBar *q);
    ~AppBarPrivate();

    void init();

    AppBar *const q_ptr;
    bool                    useThemeColors;
    QColor                  foregroundColor;
    QColor                  backgroundColor;
};

}

#endif // APPBAR_P_H
