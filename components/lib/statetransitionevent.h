#ifndef STATETRANSITIONEVENT_H
#define STATETRANSITIONEVENT_H

#include <QEvent>

namespace md
{
enum StateTransitionType {
    // Snackbar
    SnackbarShowTransition = 1,
    SnackbarHideTransition,
    SnackbarWaitTransition,
    SnackbarNextTransition,
    // FlatButton
    FlatButtonPressedTransition,
    FlatButtonCheckedTransition,
    FlatButtonUncheckedTransition,
    // CollapsibleMenu
    CollapsibleMenuExpand,
    CollapsibleMenuCollapse,
    // Slider
    SliderChangedToMinimum,
    SliderChangedFromMinimum,
    SliderNoFocusMouseEnter,
    SliderNoFocusMouseLeave,
    // Dialog
    DialogShowTransition,
    DialogHideTransition,
    //
    MaxTransitionType = 65535
};

struct StateTransitionEvent : public QEvent
{
    StateTransitionEvent(StateTransitionType type)
        : QEvent(QEvent::Type(QEvent::User + 1)),
          type(type)
    {
    }

    StateTransitionType type;
};
}

#endif // STATETRANSITIONEVENT_H
