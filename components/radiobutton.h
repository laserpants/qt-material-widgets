#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "lib/checkable.h"

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
#endif // RADIOBUTTON_H
