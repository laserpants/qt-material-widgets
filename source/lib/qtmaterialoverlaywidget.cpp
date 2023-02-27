#include "lib/qtmaterialoverlaywidget.h"
#include <QEvent>

/*!
 *  \class QtMaterialOverlayWidget
 *  \internal
 */

QtMaterialOverlayWidget::QtMaterialOverlayWidget(QWidget *parent)
    : QWidget(parent)
{
    if (parent) {
        parent->installEventFilter(this);
    }
}

QtMaterialOverlayWidget::~QtMaterialOverlayWidget()
{
}

/*!
 *  \reimp
 */
bool QtMaterialOverlayWidget::event(QEvent *event)
{
    if (!parent()) {
        return QWidget::event(event);
    }
    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        parent()->installEventFilter(this);
        setGeometry(overlayGeometry());
        break;
    }
    case QEvent::ParentAboutToChange:
    {
        parent()->removeEventFilter(this);
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

/*!
 *  \reimp
 */
bool QtMaterialOverlayWidget::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
        setGeometry(overlayGeometry());
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

QRect QtMaterialOverlayWidget::overlayGeometry() const
{
    QWidget *widget = parentWidget();
    if (!widget) {
        return QRect();
    }
    return widget->rect();
}
