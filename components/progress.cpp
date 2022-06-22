#include "progress.h"
#include "progress_p.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QPainterPath>
#include "progress_internal.h"
#include "lib/style.h"
namespace md
{

/*!
 *  \class ProgressBarPrivate
 *  \internal
 */

ProgressBarPrivate::ProgressBarPrivate(ProgressBar *q)
    : q_ptr(q)
{
}

ProgressBarPrivate::~ProgressBarPrivate()
{
}

void ProgressBarPrivate::init()
{
    Q_Q(ProgressBar);

    delegate       = new ProgressBarDelegate(q);
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

ProgressBar::ProgressBar(QWidget *parent)
    : QProgressBar(parent),
      d_ptr(new ProgressBarPrivate(this))
{
    d_func()->init();
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::setProgressType(Material::ProgressType type)
{
    Q_D(ProgressBar);

    d->progressType = type;
    update();
}

Material::ProgressType ProgressBar::progressType() const
{
    Q_D(const ProgressBar);

    return d->progressType;
}

void ProgressBar::setUseThemeColors(bool state)
{
    Q_D(ProgressBar);

    if (d->useThemeColors == state) {
        return;
    }

    d->useThemeColors = state;
    update();
}

bool ProgressBar::useThemeColors() const
{
    Q_D(const ProgressBar);

    return d->useThemeColors;
}

void ProgressBar::setProgressColor(const QColor &color)
{
    Q_D(ProgressBar);

    d->progressColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor ProgressBar::progressColor() const
{
    Q_D(const ProgressBar);

    if (d->useThemeColors || !d->progressColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->progressColor;
    }
}

void ProgressBar::setBackgroundColor(const QColor &color)
{
    Q_D(ProgressBar);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor ProgressBar::backgroundColor() const
{
    Q_D(const ProgressBar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return Style::instance().themeColor("border");
    } else {
        return d->backgroundColor;
    }
}

/*!
 *  \reimp
 */
void ProgressBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(ProgressBar);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled() ? backgroundColor()
                               : Style::instance().themeColor("disabled"));
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
}
