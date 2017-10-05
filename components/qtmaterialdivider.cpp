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

    size = 0;

    QSizePolicy policy(QSizePolicy::MinimumExpanding,
                       QSizePolicy::Fixed);
    q->setMinimumHeight( 1 );
    q->setMaximumHeight( 1 );
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

/*!
 *  \reimp
 */

void QtMaterialDivider::setInsetSize(int size)
{
    Q_D(QtMaterialDivider);

    d->size = size;

    update();
}

int QtMaterialDivider::insetSize() const
{
    Q_D(const QtMaterialDivider);

    return d->size;
}

/*!
 *  \reimp
 */
void QtMaterialDivider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialDivider);

    QPainter painter(this);
    // TODO: QtMaterialText doesn't use Antialiasing. Usng it the line is more "heavy"
    // painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setWidth(1);
    /*
     * DEBUG: to paint in blue the full widget
     *
    */
    //  painter.fillRect( rect() ,QColor(0,0,255));

    // TODO: is this the right color to use?
    pen.setColor(QtMaterialStyle::instance().themeColor("border"));

    painter.setPen(pen);
    painter.setOpacity(1);
    // TODO: implementing inset, 0 will be changed to a calculated point.
    // Normally, line should go from 0 to the end
    painter.drawLine( d->size, height()/2, width(), height()/2);
}
