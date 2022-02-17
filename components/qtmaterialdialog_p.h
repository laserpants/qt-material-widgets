#ifndef QTMATERIALDIALOG_P_H
#define QTMATERIALDIALOG_P_H

#include <QtGlobal>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QGraphicsDropShadowEffect>

#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QPainter>

namespace md
{

class Dialog;
class DialogWindow;
class DialogProxy;

class DialogPrivate
{
    Q_DISABLE_COPY(DialogPrivate)
    Q_DECLARE_PUBLIC(Dialog)

public:
    DialogPrivate(Dialog *q);
    ~DialogPrivate();

    void init();

    Dialog       *const q_ptr;
    DialogWindow *dialogWindow;
    QStackedLayout         *proxyStack;
    QStateMachine          *stateMachine;
    DialogProxy  *proxy;
};
}
#endif // QTMATERIALDIALOG_P_H
