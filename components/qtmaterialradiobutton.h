#ifndef QTMATERIALRADIOBUTTON_H
#define QTMATERIALRADIOBUTTON_H

#include "qtmaterialradiobutton_p.h"
#include "lib/qtmaterialcheckable_internal.h"
#include "lib/qtmaterialcheckable.h"

namespace md
{

class RadioButtonPrivate;

class RadioButton : public Checkable
{
    Q_OBJECT

public:
    explicit RadioButton(QWidget *parent = 0);
    ~RadioButton();

protected:
    void setupProperties();

private:
    Q_DISABLE_COPY(RadioButton)
    Q_DECLARE_PRIVATE(RadioButton)
};
}
#endif // QTMATERIALRADIOBUTTON_H
