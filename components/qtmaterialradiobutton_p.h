#ifndef QTMATERIALRADIOBUTTON_P_H
#define QTMATERIALRADIOBUTTON_P_H

#include "lib/qtmaterialcheckable_p.h"
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
#endif // QTMATERIALRADIOBUTTON_P_H
