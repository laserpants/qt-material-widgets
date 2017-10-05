#include "qtmaterialdrawer.h"
#include "qtmaterialdrawer_p.h"
#include <QPainter>
#include <QEvent>
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

    stateMachine = new QtMaterialDrawerStateMachine(q);
    window       = new QWidget;
    width        = 250;
    clickToClose = false;
    autoRaise    = true;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(window);

    q->setLayout(layout);
    q->setFixedWidth(width+16);

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
    setFixedWidth(width+16);
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

void QtMaterialDrawer::openDrawer()
{
    Q_D(QtMaterialDrawer);

    emit d->stateMachine->enterOpenedState();

    if (d->autoRaise) {
        raise();
    }
}

void QtMaterialDrawer::closeDrawer()
{
    Q_D(QtMaterialDrawer);

    emit d->stateMachine->enterClosedState();
}

bool QtMaterialDrawer::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(QtMaterialDrawer);

    switch (event->type())
    {
    case QEvent::MouseButtonPress: {
        QMouseEvent *mouseEvent;
        if ((mouseEvent = static_cast<QMouseEvent *>(event))) {
            if (!geometry().contains(mouseEvent->pos()) && d->clickToClose) {
                closeDrawer();
            }
        }
        break;
    }
    case QEvent::Move:
    case QEvent::Resize: {
        QLayout *lyut = layout();
        if (lyut && 16 != lyut->contentsMargins().right()) {
            lyut->setContentsMargins(0, 0, 16, 0);
        }
    }
    default:
        break;
    }
    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void QtMaterialDrawer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawRect(rect().adjusted(0, 0, -16, 0));

    QLinearGradient gradient(QPointF(width()-16, 0), QPointF(width(), 0));
    gradient.setColorAt(0, QColor(0, 0, 0, 80));
    gradient.setColorAt(0.5, QColor(0, 0, 0, 20));
    gradient.setColorAt(1, QColor(0, 0, 0, 0));
    painter.setBrush(QBrush(gradient));

    painter.drawRect(width()-16, 0, 16, height());
}

QRect QtMaterialDrawer::overlayGeometry() const
{
    Q_D(const QtMaterialDrawer);

    return QtMaterialOverlayWidget::overlayGeometry().translated(d->stateMachine->offset(), 0);
}
