#ifndef QTMATERIALAUTOCOMPLETESTATEMACHINE_H
#define QTMATERIALAUTOCOMPLETESTATEMACHINE_H

#include <QStateMachine>
#include "qtmaterialautocomplete.h"

namespace md
{

class AutoCompleteStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    explicit AutoCompleteStateMachine(QWidget *menu);
    ~AutoCompleteStateMachine();

signals:
    void shouldOpen();
    void shouldClose();
    void shouldFade();

private:
    Q_DISABLE_COPY(AutoCompleteStateMachine)

    QWidget *const m_menu;
    QState  *const m_closedState;
    QState  *const m_openState;
    QState  *const m_closingState;
};

}

#endif // QTMATERIALAUTOCOMPLETESTATEMACHINE_H
