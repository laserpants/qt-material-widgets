#ifndef QTMATERIALCHECKABLE_P_H
#define QTMATERIALCHECKABLE_P_H

#include <QtGlobal>
#include "lib/qtmaterialcheckable.h"

class QStateMachine;
class QState;
class QSignalTransition;
class QtMaterialRippleOverlay;
class QtMaterialCheckableIcon;

class QtMaterialCheckablePrivate
{
    Q_DISABLE_COPY(QtMaterialCheckablePrivate)
    Q_DECLARE_PUBLIC(QtMaterialCheckable)

public:
    QtMaterialCheckablePrivate(QtMaterialCheckable *q);
    virtual ~QtMaterialCheckablePrivate();

    void init();

    QtMaterialCheckable                *const q_ptr;
    QtMaterialRippleOverlay            *rippleOverlay;
    QtMaterialCheckableIcon            *checkedIcon;
    QtMaterialCheckableIcon            *uncheckedIcon;
    QStateMachine                      *stateMachine;
    QState                             *uncheckedState;
    QState                             *checkedState;
    QState                             *disabledUncheckedState;
    QState                             *disabledCheckedState;
    QSignalTransition                  *uncheckedTransition;
    QSignalTransition                  *checkedTransition;
    QtMaterialCheckable::LabelPosition  labelPosition;
    QColor                              checkedColor;
    QColor                              uncheckedColor;
    QColor                              textColor;
    QColor                              disabledColor;
    bool                                useThemeColors;
};

#endif // QTMATERIALCHECKABLE_P_H
