#ifndef AUTOCOMPLETE_P_H
#define AUTOCOMPLETE_P_H

#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QVBoxLayout>
#include <QEvent>
#include <QTimer>
#include <QPainter>
#include <QDebug>

#include "autocomplete.h"
#include "autocomplete_internal.h"
#include "flatbutton.h"
#include "textfield_p.h"

namespace md
{

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

#endif // AUTOCOMPLETE_P_H
