#ifndef QTMATERIALSTATETRANSITIONEVENT_H
#define QTMATERIALSTATETRANSITIONEVENT_H

#include <QEvent>

#include <qt-material-widgets/qt-material-widgets_export.hpp>

enum QtMaterialStateTransitionType
{
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

struct QT_MATERIAL_WIDGETS_EXPORT QtMaterialStateTransitionEvent : public QEvent
{
  QtMaterialStateTransitionEvent(QtMaterialStateTransitionType type)
      : QEvent(QEvent::Type(QEvent::User + 1))
      , type(type)
  {
  }

  QtMaterialStateTransitionType type;
};

#endif  // QTMATERIALSTATETRANSITIONEVENT_H
