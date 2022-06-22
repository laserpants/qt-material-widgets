#ifndef CHECKBOX_P_H
#define CHECKBOX_P_H

#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>

#include "checkbox.h"
#include "lib/checkable_internal.h"
#include "lib/checkable_p.h"

namespace md
{

class CheckBox;

class CheckBoxPrivate : public CheckablePrivate
{
    Q_DISABLE_COPY(CheckBoxPrivate)
    Q_DECLARE_PUBLIC(CheckBox)

public:
    CheckBoxPrivate(CheckBox *q);
    ~CheckBoxPrivate();

    void init();
};
}
#endif // CHECKBOX_P_H
