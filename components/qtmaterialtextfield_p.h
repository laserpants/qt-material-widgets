#ifndef QTMATERIALTEXTFIELD_P_H
#define QTMATERIALTEXTFIELD_P_H

#include <QtGlobal>
#include <QColor>

namespace md
{
class TextField;
class TextFieldStateMachine;
class TextFieldLabel;

class TextFieldPrivate
{
    Q_DISABLE_COPY(TextFieldPrivate)
    Q_DECLARE_PUBLIC(TextField)

public:
    TextFieldPrivate(TextField *q);
    virtual ~TextFieldPrivate();

    void init();

    TextField             *const q_ptr;
    TextFieldStateMachine *stateMachine;
    TextFieldLabel        *label;
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
}

#endif // QTMATERIALTEXTFIELD_P_H
