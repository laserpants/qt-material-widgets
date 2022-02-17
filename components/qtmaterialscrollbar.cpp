#include "qtmaterialscrollbar.h"

namespace md
{

/*!
 *  \class QtMaterialScrollBarPrivate
 *  \internal
 */

ScrollBarPrivate::ScrollBarPrivate(ScrollBar *q)
    : q_ptr(q)
{
}

ScrollBarPrivate::~ScrollBarPrivate()
{
}

void ScrollBarPrivate::init()
{
    Q_Q(ScrollBar);

    stateMachine   = new ScrollBarStateMachine(q);
    hideOnMouseOut = true;
    useThemeColors = true;

    q->setMouseTracking(true);
    q->setStyle(&Style::instance());
    q->setStyleSheet("QScrollBar:vertical { margin: 0; }"
                     "QScrollBar::add-line:vertical { height: 0; margin: 0; }"
                     "QScrollBar::sub-line:vertical { height: 0; margin: 0; }");

    stateMachine->start();
}

/*!
 *  \class QtMaterialScrollBar
 */

ScrollBar::ScrollBar(QWidget *parent)
    : QScrollBar(parent),
      d_ptr(new ScrollBarPrivate(this))
{
    d_func()->init();
}

ScrollBar::~ScrollBar()
{
}

/*!
 *  \reimp
 */
QSize ScrollBar::sizeHint() const
{
    if (Qt::Horizontal == orientation()) {
        return QSize(1, 10);
    } else {
        return QSize(10, 1);
    }
}

void ScrollBar::setUseThemeColors(bool value)
{
    Q_D(ScrollBar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool ScrollBar::useThemeColors() const
{
    Q_D(const ScrollBar);

    return d->useThemeColors;
}

void ScrollBar::setCanvasColor(const QColor &color)
{
    Q_D(ScrollBar);

    d->canvasColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor ScrollBar::canvasColor() const
{
    Q_D(const ScrollBar);

    if (d->useThemeColors || !d->canvasColor.isValid()) {
        return parentWidget()->palette().color(backgroundRole());
    } else {
        return d->canvasColor;
    }
}

void ScrollBar::setBackgroundColor(const QColor &color)
{
    Q_D(ScrollBar);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor ScrollBar::backgroundColor() const
{
    Q_D(const ScrollBar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return Style::instance().themeColor("border");
    } else {
        return d->backgroundColor;
    }
}

void ScrollBar::setSliderColor(const QColor &color)
{
    Q_D(ScrollBar);

    d->sliderColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor ScrollBar::sliderColor() const
{
    Q_D(const ScrollBar);

    if (d->useThemeColors || !d->sliderColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->sliderColor;
    }
}

void ScrollBar::setHideOnMouseOut(bool value)
{
    Q_D(ScrollBar);

    d->hideOnMouseOut = value;
    update();
}

bool ScrollBar::hideOnMouseOut() const
{
    Q_D(const ScrollBar);

    return d->hideOnMouseOut;
}

/*!
 *  \reimp
 */
void ScrollBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(ScrollBar);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), canvasColor());

    int x, y, w, h;
    rect().getRect(&x, &y, &w, &h);

    QMargins margins(2, 2, 2, 2);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (d->hideOnMouseOut) {
        painter.setOpacity(d->stateMachine->opacity());
    }

    QRect trimmed(rect().marginsRemoved(margins));

    QPainterPath path;
    path.addRoundedRect(trimmed, 3, 3);
    painter.setClipPath(path);

    painter.drawRect(trimmed);

    const qreal q = (Qt::Horizontal == orientation() ? w : h) /
            static_cast<qreal>(maximum()-minimum()+pageStep()-1);

    QRect handle = Qt::Horizontal == orientation()
            ? QRect(sliderPosition()*q, y, pageStep()*q, h)
            : QRect(x, sliderPosition()*q, w, pageStep()*q);

    brush.setColor(sliderColor());
    painter.setBrush(brush);

    painter.drawRoundedRect(handle, 9, 9);
}
}
