#ifndef QTMATERIALRADIOBUTTON_H
#define QTMATERIALRADIOBUTTON_H

#include "lib/qtmaterialcheckable.h"
#include <QtUiPlugin/QDesignerExportWidget>

class QtMaterialRadioButtonPrivate;

class QDESIGNER_WIDGET_EXPORT QtMaterialRadioButton : public QtMaterialCheckable
{
    Q_OBJECT

public:
    explicit QtMaterialRadioButton(QWidget *parent = 0);
    ~QtMaterialRadioButton();

protected:
    void setupProperties();

private:
    Q_DISABLE_COPY(QtMaterialRadioButton)
    Q_DECLARE_PRIVATE(QtMaterialRadioButton)
};

#endif // QTMATERIALRADIOBUTTON_H
