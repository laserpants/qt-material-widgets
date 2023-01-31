#ifndef QTMATERIALSTATETRANSITIONEVENT_H
#define QTMATERIALSTATETRANSITIONEVENT_H

#include <QEvent>

enum QtMaterialStateTransitionType {
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

struct QtMaterialStateTransitionEvent : public QEvent
{
    QtMaterialStateTransitionEvent(QtMaterialStateTransitionType type)
        : QEvent(QEvent::Type(QEvent::User + 1)),
          type(type)
    {
    }

    QtMaterialStateTransitionType type;
};

#endif // QTMATERIALSTATETRANSITIONEVENT_H
