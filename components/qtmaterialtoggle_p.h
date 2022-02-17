#ifndef QTMATERIALTOGGLE_P_H
#define QTMATERIALTOGGLE_P_H

#include <QtWidgets/QApplication>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QColor>

namespace md
{

class Toggle;
class ToggleTrack;
class ToggleThumb;
class ToggleRippleOverlay;

class TogglePrivate
{
    Q_DISABLE_COPY(TogglePrivate)
    Q_DECLARE_PUBLIC(Toggle)

public:
    TogglePrivate(Toggle *q);
    ~TogglePrivate();

    void init();
    void setupProperties();

    Toggle              *const q_ptr;
    ToggleTrack         *track;
    ToggleThumb         *thumb;
    ToggleRippleOverlay *rippleOverlay;
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
}
#endif // QTMATERIALTOGGLE_P_H
