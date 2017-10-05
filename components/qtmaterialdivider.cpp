#include "qtmaterialdivider.h"
#include "qtmaterialdivider_p.h"
#include <QPainter>
#include "lib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialDividerPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialDividerPrivate::QtMaterialDividerPrivate(QtMaterialDivider *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialDividerPrivate::~QtMaterialDividerPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialDividerPrivate::init()
{
    Q_Q(QtMaterialDivider);

    size           = 40;
    useThemeColors = true;

    QSizePolicy policy(QSizePolicy::Ignored,
    // QSizePolicy policy(QSizePolicy::Expanding,
                       QSizePolicy::Fixed);
    q->setSizePolicy(policy);
}

/*!
 *  \class QtMaterialDivider
 */

QtMaterialDivider::QtMaterialDivider(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialDividerPrivate(this))
{
    d_func()->init();
}

QtMaterialDivider::~QtMaterialDivider()
{
}

void QtMaterialDivider::setUseThemeColors(bool value)
{
    Q_D(QtMaterialDivider);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialDivider::useThemeColors() const
{
    Q_D(const QtMaterialDivider);

    return d->useThemeColors;
}


/*!
 *  \reimp
 */
QSize QtMaterialDivider::sizeHint() const
{
    Q_D(const QtMaterialDivider);

    return QSize(d->size, 2+2);
}

void QtMaterialDivider::setSize(int size)
{
    Q_D(QtMaterialDivider);

    d->size = size;

    update();
}

int QtMaterialDivider::size() const
{
    Q_D(const QtMaterialDivider);

    return d->size;
}

/*!
 *  \reimp
 */
void QtMaterialDivider::resizeEvent(QResizeEvent *event)
{
    Q_D(QtMaterialDivider);

    QWidget::resizeEvent(event);
    QSize sz = event->size();
    d->size = width();
    update();
}


/*!
 *  \reimp
 */
void QtMaterialDivider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialDivider);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int wd = d->size; // width();
    QPen pen;
    pen.setWidth(2);
    // pen.setColor(QtMaterialStyle::instance().themeColor("border"));
    pen.setColor(QColor(255,0,0));
    painter.setPen(pen);
    painter.setOpacity(1);
    painter.drawLine(0, 1, wd, 1);
    
}
