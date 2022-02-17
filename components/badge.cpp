#include "badge.h"
#include "badge_p.h"
#include "lib/style.h"

namespace md
{

/*!
 *  \class BadgePrivate
 *  \internal
 */

/*!
 *  \internal
 */
BadgePrivate::BadgePrivate(Badge *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
BadgePrivate::~BadgePrivate()
{
}

/*!
 *  \internal
 */
void BadgePrivate::init()
{
    Q_Q(Badge);

    x              = 0;
    y              = 0;
    padding        = 10;
    useThemeColors = true;

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QFont font(q->font());
    font.setPointSizeF(10);
    font.setStyleName("Bold");
    q->setFont(font);

    q->setText("+1");
}

/*!
 *  \class QtMaterialBadge
 */

Badge::Badge(QWidget *parent)
    : OverlayWidget(parent),
      d_ptr(new BadgePrivate(this))
{
    d_func()->init();
}

Badge::Badge(const QIcon &icon, QWidget *parent)
    : OverlayWidget(parent),
      d_ptr(new BadgePrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

Badge::Badge(const QString &text, QWidget *parent)
    : OverlayWidget(parent),
      d_ptr(new BadgePrivate(this))
{
    d_func()->init();

    setText(text);
}

Badge::~Badge()
{
}

void Badge::setUseThemeColors(bool value)
{
    Q_D(Badge);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool Badge::useThemeColors() const
{
    Q_D(const Badge);

    return d->useThemeColors;
}

void Badge::setTextColor(const QColor &color)
{
    Q_D(Badge);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor Badge::textColor() const
{
    Q_D(const Badge);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void Badge::setBackgroundColor(const QColor &color)
{
    Q_D(Badge);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor Badge::backgroundColor() const
{
    Q_D(const Badge);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return Style::instance().themeColor("accent1");
    } else {
        return d->backgroundColor;
    }
}

void Badge::setRelativePosition(const QPointF &pos)
{
    setRelativePosition(pos.x(), pos.y());
}

void Badge::setRelativePosition(qreal x, qreal y)
{
    Q_D(Badge);

    d->x = x;
    d->y = y;
    update();
}

QPointF Badge::relativePosition() const
{
    Q_D(const Badge);

    return QPointF(d->x, d->y);
}

void Badge::setRelativeXPosition(qreal x)
{
    Q_D(Badge);

    d->x = x;
    update();
}

qreal Badge::relativeXPosition() const
{
    Q_D(const Badge);

    return d->x;
}

void Badge::setRelativeYPosition(qreal y)
{
    Q_D(Badge);

    d->y = y;
    update();
}

qreal Badge::relativeYPosition() const
{
    Q_D(const Badge);

    return d->y;
}

/*!
 *  \reimp
 */
QSize Badge::sizeHint() const
{
    const int s = getDiameter();
    return QSize(s+4, s+4);
}

void Badge::setIcon(const QIcon &icon)
{
    Q_D(Badge);

    d->icon = icon;
    update();
}

QIcon Badge::icon() const
{
    Q_D(const Badge);

    return d->icon;
}

void Badge::setText(const QString &text)
{
    Q_D(Badge);

    d->text = text;

    if (!d->icon.isNull()) {
        d->icon = QIcon();
    }

    d->size = fontMetrics().size(Qt::TextShowMnemonic, text);

    update();
}

QString Badge::text() const
{
    Q_D(const Badge);

    return d->text;
}

/*!
 *  \reimp
 */
void Badge::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Badge);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(d->x, d->y);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled() ? backgroundColor()
                               : Style::instance().themeColor("disabled"));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    const int s = getDiameter();

    QRectF r(0, 0, s, s);
    r.translate(QPointF((width()-s), (height()-s))/2);

    if (d->icon.isNull())
    {
        painter.drawEllipse(r);
        painter.setPen(textColor());
        painter.setBrush(Qt::NoBrush);
        painter.drawText(r.translated(0, -0.5), Qt::AlignCenter, d->text);
    }
    else
    {
        painter.drawEllipse(r);
        QRectF q(0, 0, 16, 16);
        q.moveCenter(r.center());
        QPixmap pixmap = icon().pixmap(16, 16);
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), textColor());
        painter.drawPixmap(q.toRect(), pixmap);
    }
}

int Badge::getDiameter() const
{
    Q_D(const Badge);

    if (d->icon.isNull()) {
        return qMax(d->size.width(), d->size.height()) + d->padding;
    } else {
        return 24;
    }
}

}
