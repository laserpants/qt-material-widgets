#ifndef QTMATERIALSNACKBAR_P_H
#define QTMATERIALSNACKBAR_P_H

#include <QObject>
#include <QColor>

namespace md
{

class SnackBar;
class SnackBarStateMachine;

class SnackBarPrivate
{
    Q_DISABLE_COPY(SnackBarPrivate)
    Q_DECLARE_PUBLIC(SnackBar)

public:
    SnackBarPrivate(SnackBar *q);
    ~SnackBarPrivate();

    void init();

    SnackBar             *const q_ptr;
    SnackBarStateMachine *stateMachine;
    QColor                          backgroundColor;
    QColor                          textColor;
    qreal                           bgOpacity;
    QList<QString>                  messages;
    int                             duration;
    int                             boxWidth;
    bool                            clickDismiss;
    bool                            useThemeColors;
};
}
#endif // QTMATERIALSNACKBAR_P_H
