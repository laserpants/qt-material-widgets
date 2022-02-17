#ifndef QTMATERIALAPPBAR_P_H
#define QTMATERIALAPPBAR_P_H

#include <QtGlobal>
#include <QColor>

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

#endif // QTMATERIALAPPBAR_P_H
