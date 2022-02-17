#ifndef QTMATERIALCHECKBOX_H
#define QTMATERIALCHECKBOX_H

#include "lib/qtmaterialcheckable.h"

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
#endif // QTMATERIALCHECKBOX_H
