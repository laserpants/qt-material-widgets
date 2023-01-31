#ifndef QTMATERIALSNACKBAR_P_H
#define QTMATERIALSNACKBAR_P_H

#include <QObject>
#include <QColor>

class QtMaterialSnackbar;
class QtMaterialSnackbarStateMachine;

class QtMaterialSnackbarPrivate
{
    Q_DISABLE_COPY(QtMaterialSnackbarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSnackbar)

public:
    QtMaterialSnackbarPrivate(QtMaterialSnackbar *q);
    ~QtMaterialSnackbarPrivate();

    void init();

    QtMaterialSnackbar             *const q_ptr;
    QtMaterialSnackbarStateMachine *stateMachine;
    QColor                          backgroundColor;
    QColor                          textColor;
    qreal                           bgOpacity;
    QList<QString>                  messages;
    int                             duration;
    int                             boxWidth;
    bool                            clickDismiss;
    bool                            useThemeColors;
};

#endif // QTMATERIALSNACKBAR_P_H
