#ifndef QTMATERIALAUTOCOMPLETE_P_H
#define QTMATERIALAUTOCOMPLETE_P_H

#include "qtmaterialtextfield_p.h"

namespace md
{

class QWidget;
class QVBoxLayout;
class AutoCompleteOverlay;
class AutoCompleteStateMachine;

class AutoCompletePrivate : public TextFieldPrivate
{
    Q_DISABLE_COPY(AutoCompletePrivate)
    Q_DECLARE_PUBLIC(AutoComplete)

public:
    AutoCompletePrivate(AutoComplete *q);
    virtual ~AutoCompletePrivate();

    void init();

    QWidget                            *menu;
    QWidget                            *frame;
    AutoCompleteStateMachine *stateMachine;
    QVBoxLayout                        *menuLayout;
    QStringList                         dataSource;
    int                                 maxWidth;
};

}

#endif // QTMATERIALAUTOCOMPLETE_P_H
