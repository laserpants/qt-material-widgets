#ifndef QTMATERIALCHECKBOX_P_H
#define QTMATERIALCHECKBOX_P_H

#include "lib/qtmaterialcheckable_p.h"
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
#endif // QTMATERIALCHECKBOX_P_H
