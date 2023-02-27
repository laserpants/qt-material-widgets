#ifndef QTMATERIALSTATETRANSITION_H
#define QTMATERIALSTATETRANSITION_H

#include <QAbstractTransition>

#include "qtmaterialstatetransitionevent.h"

class QT_MATERIAL_WIDGETS_EXPORT QtMaterialStateTransition
    : public QAbstractTransition
{
  Q_OBJECT

public:
  QtMaterialStateTransition(QtMaterialStateTransitionType type);

protected:
  virtual bool eventTest(QEvent* event);
  virtual void onTransition(QEvent*);

private:
  QtMaterialStateTransitionType m_type;
};

#endif  // QTMATERIALSTATETRANSITION_H
