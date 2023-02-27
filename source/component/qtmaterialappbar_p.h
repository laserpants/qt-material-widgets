#ifndef QTMATERIALAPPBAR_P_H
#define QTMATERIALAPPBAR_P_H

#include <QtGlobal>
#include <QColor>

class QtMaterialAppBar;

class QtMaterialAppBarPrivate
{
    Q_DISABLE_COPY(QtMaterialAppBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialAppBar)

public:
    QtMaterialAppBarPrivate(QtMaterialAppBar *q);
    ~QtMaterialAppBarPrivate();

    void init();

    QtMaterialAppBar *const q_ptr;
    bool                    useThemeColors;
    QColor                  foregroundColor;
    QColor                  backgroundColor;
};

#endif // QTMATERIALAPPBAR_P_H
