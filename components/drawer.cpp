#include "drawer.h"

namespace md
{

/*!
 *  \class QtMaterialDrawerPrivate
 *  \internal
 */

/*!
 *  \internal
 */
DrawerPrivate::DrawerPrivate(Drawer *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
DrawerPrivate::~DrawerPrivate()
{
}

/*!
 *  \internal
 */
void DrawerPrivate::init()
{
    Q_Q(Drawer);

    widget       = new DrawerWidget;
    stateMachine = new DrawerStateMachine(widget, q);
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

Drawer::Drawer(QWidget *parent)
    : OverlayWidget(parent),
      d_ptr(new DrawerPrivate(this))
{
    d_func()->init();
}

Drawer::~Drawer()
{
}

void Drawer::setDrawerWidth(int width)
{
    Q_D(Drawer);

    d->width = width;
    d->stateMachine->updatePropertyAssignments();
    d->widget->setFixedWidth(width+16);
}

int Drawer::drawerWidth() const
{
    Q_D(const Drawer);

    return d->width;
}

void Drawer::setDrawerLayout(QLayout *layout)
{
    Q_D(Drawer);

    d->window->setLayout(layout);
}

QLayout *Drawer::drawerLayout() const
{
    Q_D(const Drawer);

    return d->window->layout();
}

void Drawer::setClickOutsideToClose(bool state)
{
    Q_D(Drawer);

    d->clickToClose = state;
}

bool Drawer::clickOutsideToClose() const
{
    Q_D(const Drawer);

    return d->clickToClose;
}

void Drawer::setAutoRaise(bool state)
{
    Q_D(Drawer);

    d->autoRaise = state;
}

bool Drawer::autoRaise() const
{
    Q_D(const Drawer);

    return d->autoRaise;
}

void Drawer::setOverlayMode(bool value)
{
    Q_D(Drawer);

    d->overlay = value;
    update();
}

bool Drawer::overlayMode() const
{
    Q_D(const Drawer);

    return d->overlay;
}

void Drawer::openDrawer()
{
    Q_D(Drawer);

    emit d->stateMachine->signalOpen();

    if (d->autoRaise) {
        raise();
    }
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setAttribute(Qt::WA_NoSystemBackground, false);
}

void Drawer::closeDrawer()
{
    Q_D(Drawer);

    emit d->stateMachine->signalClose();

    if (d->overlay) {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);
    }
}

bool Drawer::event(QEvent *event)
{
    Q_D(Drawer);

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
    return OverlayWidget::event(event);
}

bool Drawer::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(Drawer);

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
    return OverlayWidget::eventFilter(obj, event);
}

void Drawer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Drawer);

    if (!d->overlay || d->stateMachine->isInClosedState()) {
        return;
    }
    QPainter painter(this);
    painter.setOpacity(d->stateMachine->opacity());
    painter.fillRect(rect(), Qt::SolidPattern);
}

}
