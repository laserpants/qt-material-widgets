#ifndef QTMATERIALAUTOCOMPLETE_P_H
#define QTMATERIALAUTOCOMPLETE_P_H

#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QVBoxLayout>
#include <QEvent>
#include <QTimer>
#include <QPainter>
#include <QDebug>

#include "qtmaterialautocomplete.h"
#include "qtmaterialautocomplete_internal.h"
#include "qtmaterialflatbutton.h"
#include "qtmaterialtextfield_p.h"

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

#endif // QTMATERIALAUTOCOMPLETE_P_H
