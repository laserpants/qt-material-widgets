#ifndef QTMATERIALTOGGLE_P_H
#define QTMATERIALTOGGLE_P_H

#include <Qt>

class QStateMachine;
class QState;
class QColor;
class QtMaterialToggle;
class QtMaterialToggleTrack;
class QtMaterialToggleThumb;
class QtMaterialToggleRippleOverlay;

class QtMaterialTogglePrivate
{
    Q_DISABLE_COPY(QtMaterialTogglePrivate)
    Q_DECLARE_PUBLIC(QtMaterialToggle)

public:
    QtMaterialTogglePrivate(QtMaterialToggle *q);
    ~QtMaterialTogglePrivate();

    void init();
    void setupProperties();

    QtMaterialToggle              *const q_ptr;
    QtMaterialToggleTrack         *track;
    QtMaterialToggleThumb         *thumb;
    QtMaterialToggleRippleOverlay *rippleOverlay;
    QStateMachine                 *stateMachine;
    QState                        *offState;
    QState                        *onState;
    Qt::Orientation                orientation;
    QColor                         disabledColor;
    QColor                         activeColor;
    QColor                         inactiveColor;
    QColor                         trackColor;
    bool                           useThemeColors;
};

#endif // QTMATERIALTOGGLE_P_H
