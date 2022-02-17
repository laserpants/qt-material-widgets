#ifndef QTMATERIALCHECKABLE_P_H
#define QTMATERIALCHECKABLE_P_H

#include <QtGlobal>
#include <QPainter>
#include <QEvent>
#include <QStateMachine>
#include <QSignalTransition>
#include <QEventTransition>
#include <QColor>
#include <QCoreApplication>

#include "lib/qtmaterialcheckable.h"

namespace md
{
class RippleOverlay;
class CheckableIcon;

class CheckablePrivate
{
    Q_DISABLE_COPY(CheckablePrivate)
    Q_DECLARE_PUBLIC(Checkable)

public:
    CheckablePrivate(Checkable *q);
    virtual ~CheckablePrivate();

    void init();

    Checkable                *const q_ptr;
    RippleOverlay            *rippleOverlay;
    CheckableIcon            *checkedIcon;
    CheckableIcon            *uncheckedIcon;
    QStateMachine                      *stateMachine;
    QState                             *uncheckedState;
    QState                             *checkedState;
    QState                             *disabledUncheckedState;
    QState                             *disabledCheckedState;
    QSignalTransition                  *uncheckedTransition;
    QSignalTransition                  *checkedTransition;
    Checkable::LabelPosition  labelPosition;
    QColor                              checkedColor;
    QColor                              uncheckedColor;
    QColor                              textColor;
    QColor                              disabledColor;
    bool                                useThemeColors;
};
}

#endif // QTMATERIALCHECKABLE_P_H
