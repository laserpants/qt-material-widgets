#include "qtmaterialappbar.h"
#include "qtmaterialappbar_p.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QPainter>
#include "lib/qtmaterialstyle.h"

namespace md {
/*!
 *  \class QtMaterialAppBarPrivate
 *  \internal
 */

/*!
 *  \internal
 */
AppBarPrivate::AppBarPrivate(AppBar *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
AppBarPrivate::~AppBarPrivate()
{
}

/*!
 *  \internal
 */
void AppBarPrivate::init()
{
    Q_Q(AppBar);

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

AppBar::AppBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new AppBarPrivate(this))
{
    d_func()->init();
}

AppBar::~AppBar()
{
}

QSize AppBar::sizeHint() const
{
    return QSize(-1, 64);
}

void AppBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.fillRect(rect(), backgroundColor());
}

void AppBar::setUseThemeColors(bool value)
{
    Q_D(AppBar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool AppBar::useThemeColors() const
{
    Q_D(const AppBar);

    return d->useThemeColors;
}

void AppBar::setForegroundColor(const QColor &color)
{
    Q_D(AppBar);

    d->foregroundColor = color;

    if (d->useThemeColors == true) {
        d->useThemeColors = false;
    }
    update();
}

QColor AppBar::foregroundColor() const
{
    Q_D(const AppBar);

    if (d->useThemeColors || !d->foregroundColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->foregroundColor;
    }
}

void AppBar::setBackgroundColor(const QColor &color)
{
    Q_D(AppBar);

    d->backgroundColor = color;

    if (d->useThemeColors == true) {
        d->useThemeColors = false;
    }
    update();
}

QColor AppBar::backgroundColor() const
{
    Q_D(const AppBar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

}
