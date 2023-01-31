#include "qtmaterialdrawer.h"
#include "qtmaterialdrawer_p.h"
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLayout>
#include <QLinearGradient>
#include <QtWidgets/QVBoxLayout>
#include "qtmaterialdrawer_internal.h"

/*!
 *  \class QtMaterialDrawerPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialDrawerPrivate::QtMaterialDrawerPrivate(QtMaterialDrawer *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialDrawerPrivate::~QtMaterialDrawerPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialDrawerPrivate::init()
{
    Q_Q(QtMaterialDrawer);

    widget       = new QtMaterialDrawerWidget;
    stateMachine = new QtMaterialDrawerStateMachine(widget, q);
    window       = new QWidget;
    width        = 250;
    clickToClose = false;
    autoRaise    = true;
    closed       = true;
    overlay      = false;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(window);

    widget->setLayout(layout);
    widget->setFixedWidth(width+16);

    widget->setParent(q);

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class QtMaterialDrawer
 */

QtMaterialDrawer::QtMaterialDrawer(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      d_ptr(new QtMaterialDrawerPrivate(this))
{
    d_func()->init();
}

QtMaterialDrawer::~QtMaterialDrawer()
{
}

void QtMaterialDrawer::setDrawerWidth(int width)
{
    Q_D(QtMaterialDrawer);

    d->width = width;
    d->stateMachine->updatePropertyAssignments();
    d->widget->setFixedWidth(width+16);
}

int QtMaterialDrawer::drawerWidth() const
{
    Q_D(const QtMaterialDrawer);

    return d->width;
}

void QtMaterialDrawer::setDrawerLayout(QLayout *layout)
{
    Q_D(QtMaterialDrawer);

    d->window->setLayout(layout);
}

QLayout *QtMaterialDrawer::drawerLayout() const
{
    Q_D(const QtMaterialDrawer);

    return d->window->layout();
}

void QtMaterialDrawer::setClickOutsideToClose(bool state)
{
    Q_D(QtMaterialDrawer);

    d->clickToClose = state;
}

bool QtMaterialDrawer::clickOutsideToClose() const
{
    Q_D(const QtMaterialDrawer);

    return d->clickToClose;
}

void QtMaterialDrawer::setAutoRaise(bool state)
{
    Q_D(QtMaterialDrawer);

    d->autoRaise = state;
}

bool QtMaterialDrawer::autoRaise() const
{
    Q_D(const QtMaterialDrawer);

    return d->autoRaise;
}

void QtMaterialDrawer::setOverlayMode(bool value)
{
    Q_D(QtMaterialDrawer);

    d->overlay = value;
    update();
}

bool QtMaterialDrawer::overlayMode() const
{
    Q_D(const QtMaterialDrawer);

    return d->overlay;
}

void QtMaterialDrawer::openDrawer()
{
    Q_D(QtMaterialDrawer);

    emit d->stateMachine->signalOpen();

    if (d->autoRaise) {
        raise();
    }
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setAttribute(Qt::WA_NoSystemBackground, false);
}

void QtMaterialDrawer::closeDrawer()
{
    Q_D(QtMaterialDrawer);

    emit d->stateMachine->signalClose();

    if (d->overlay) {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);
    }
}

bool QtMaterialDrawer::event(QEvent *event)
{
    Q_D(QtMaterialDrawer);

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
        if (!d->overlay) {
            setMask(QRegion(d->widget->rect()));
        }
        break;
    default:
        break;
    }
    return QtMaterialOverlayWidget::event(event);
}

bool QtMaterialDrawer::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(QtMaterialDrawer);

    switch (event->type())
    {
    case QEvent::MouseButtonPress: {
        QMouseEvent *mouseEvent;
        if ((mouseEvent = static_cast<QMouseEvent *>(event))) {
            const bool canClose = d->clickToClose || d->overlay;
            if (!d->widget->geometry().contains(mouseEvent->pos()) && canClose) {
                closeDrawer();
            }
        }
        break;
    }
    case QEvent::Move:
    case QEvent::Resize: {
        QLayout *lw = d->widget->layout();
        if (lw && 16 != lw->contentsMargins().right()) {
            lw->setContentsMargins(0, 0, 16, 0);
        }
        break;
    }
    default:
        break;
    }
    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void QtMaterialDrawer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialDrawer);

    if (!d->overlay || d->stateMachine->isInClosedState()) {
        return;
    }
    QPainter painter(this);
    painter.setOpacity(d->stateMachine->opacity());
    painter.fillRect(rect(), Qt::SolidPattern);
}
