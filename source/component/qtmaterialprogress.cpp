#include "qtmaterialprogress.h"
#include "qtmaterialprogress_p.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QPainterPath>
#include "qtmaterialprogress_internal.h"
#include "lib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialProgressPrivate
 *  \internal
 */

QtMaterialProgressPrivate::QtMaterialProgressPrivate(QtMaterialProgress *q)
    : q_ptr(q)
{
}

QtMaterialProgressPrivate::~QtMaterialProgressPrivate()
{
}

void QtMaterialProgressPrivate::init()
{
    Q_Q(QtMaterialProgress);

    delegate       = new QtMaterialProgressDelegate(q);
    progressType   = Material::IndeterminateProgress;
    useThemeColors = true;

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("offset");
    animation->setTargetObject(delegate);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(1000);

    animation->setLoopCount(-1);

    animation->start();
}

/*!
 *  \class QtMaterialProgress
 */

QtMaterialProgress::QtMaterialProgress(QWidget *parent)
    : QProgressBar(parent),
      d_ptr(new QtMaterialProgressPrivate(this))
{
    d_func()->init();
}

QtMaterialProgress::~QtMaterialProgress()
{
}

void QtMaterialProgress::setProgressType(Material::ProgressType type)
{
    Q_D(QtMaterialProgress);

    d->progressType = type;
    update();
}

Material::ProgressType QtMaterialProgress::progressType() const
{
    Q_D(const QtMaterialProgress);

    return d->progressType;
}

void QtMaterialProgress::setUseThemeColors(bool state)
{
    Q_D(QtMaterialProgress);

    if (d->useThemeColors == state) {
        return;
    }

    d->useThemeColors = state;
    update();
}

bool QtMaterialProgress::useThemeColors() const
{
    Q_D(const QtMaterialProgress);

    return d->useThemeColors;
}

void QtMaterialProgress::setProgressColor(const QColor &color)
{
    Q_D(QtMaterialProgress);

    d->progressColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialProgress::progressColor() const
{
    Q_D(const QtMaterialProgress);

    if (d->useThemeColors || !d->progressColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->progressColor;
    }
}

void QtMaterialProgress::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialProgress);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialProgress::backgroundColor() const
{
    Q_D(const QtMaterialProgress);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    } else {
        return d->backgroundColor;
    }
}

/*!
 *  \reimp
 */
void QtMaterialProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialProgress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled() ? backgroundColor()
                               : QtMaterialStyle::instance().themeColor("disabled"));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(0, height()/2-3, width(), 6, 3, 3);
    painter.setClipPath(path);

    painter.drawRect(0, 0, width(), height());

    if (isEnabled())
    {
        brush.setColor(progressColor());
        painter.setBrush(brush);

        if (Material::IndeterminateProgress == d->progressType) {
            painter.drawRect(d->delegate->offset()*width()*2-width(), 0, width(), height());
        } else {
            qreal p = static_cast<qreal>(width())*(value()-minimum())/(maximum()-minimum());
            painter.drawRect(0, 0, p, height());
        }
    }
}
