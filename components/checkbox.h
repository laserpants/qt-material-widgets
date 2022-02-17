#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "lib/checkable.h"

namespace md
{

class CheckBoxPrivate;

class CheckBox : public Checkable
{
    Q_OBJECT

public:
    explicit CheckBox(QWidget *parent = 0);
    ~CheckBox();

private:
    Q_DISABLE_COPY(CheckBox)
    Q_DECLARE_PRIVATE(CheckBox)
};

}
#endif // CHECKBOX_H
