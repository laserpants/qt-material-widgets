#ifndef RADIOBUTTON_P_H
#define RADIOBUTTON_P_H

#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QColor>

#include "radiobutton.h"
#include "lib/checkable_p.h"

namespace md
{

class RadioButton;

class RadioButtonPrivate : public CheckablePrivate
{
    Q_DISABLE_COPY(RadioButtonPrivate)
    Q_DECLARE_PUBLIC(RadioButton)

public:
    RadioButtonPrivate(RadioButton *q);
    ~RadioButtonPrivate();

    void init();
};
}
#endif // RADIOBUTTON_P_H
