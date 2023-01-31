#include "qtmaterialappbar.h"
#include "qtmaterialappbar_p.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QPainter>
#include "lib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialAppBarPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialAppBarPrivate::QtMaterialAppBarPrivate(QtMaterialAppBar *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialAppBarPrivate::~QtMaterialAppBarPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialAppBarPrivate::init()
{
    Q_Q(QtMaterialAppBar);

    useThemeColors = true;

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    effect->setOffset(0, 3);

    q->setGraphicsEffect(effect);

    QHBoxLayout *layout = new QHBoxLayout;
    q->setLayout(layout);
}

/*!
 *  \class QtMaterialAppBar
 */

QtMaterialAppBar::QtMaterialAppBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialAppBarPrivate(this))
{
    d_func()->init();
}

QtMaterialAppBar::~QtMaterialAppBar()
{
}

QSize QtMaterialAppBar::sizeHint() const
{
    return QSize(-1, 64);
}

void QtMaterialAppBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.fillRect(rect(), backgroundColor());
}

void QtMaterialAppBar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialAppBar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialAppBar::useThemeColors() const
{
    Q_D(const QtMaterialAppBar);

    return d->useThemeColors;
}

void QtMaterialAppBar::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialAppBar);

    d->foregroundColor = color;

    if (d->useThemeColors == true) {
        d->useThemeColors = false;
    }
    update();
}

QColor QtMaterialAppBar::foregroundColor() const
{
    Q_D(const QtMaterialAppBar);

    if (d->useThemeColors || !d->foregroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->foregroundColor;
    }
}

void QtMaterialAppBar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialAppBar);

    d->backgroundColor = color;

    if (d->useThemeColors == true) {
        d->useThemeColors = false;
    }
    update();
}

QColor QtMaterialAppBar::backgroundColor() const
{
    Q_D(const QtMaterialAppBar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}
