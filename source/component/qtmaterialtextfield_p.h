#ifndef QTMATERIALTEXTFIELD_P_H
#define QTMATERIALTEXTFIELD_P_H

#include <QtGlobal>
#include <QColor>

class QtMaterialTextField;
class QtMaterialTextFieldStateMachine;
class QtMaterialTextFieldLabel;

class QtMaterialTextFieldPrivate
{
    Q_DISABLE_COPY(QtMaterialTextFieldPrivate)
    Q_DECLARE_PUBLIC(QtMaterialTextField)

public:
    QtMaterialTextFieldPrivate(QtMaterialTextField *q);
    virtual ~QtMaterialTextFieldPrivate();

    void init();

    QtMaterialTextField             *const q_ptr;
    QtMaterialTextFieldStateMachine *stateMachine;
    QtMaterialTextFieldLabel        *label;
    QColor                           textColor;
    QColor                           labelColor;
    QColor                           inkColor;
    QColor                           inputLineColor;
    QString                          labelString;
    qreal                            labelFontSize;
    bool                             showLabel;
    bool                             showInputLine;
    bool                             useThemeColors;
};

#endif // QTMATERIALTEXTFIELD_P_H
