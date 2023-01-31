#include "qtmaterialbadge.h"
#include "qtmaterialbadge_p.h"
#include <QPainter>
#include "lib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialBadgePrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialBadgePrivate::QtMaterialBadgePrivate(QtMaterialBadge *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialBadgePrivate::~QtMaterialBadgePrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialBadgePrivate::init()
{
    Q_Q(QtMaterialBadge);

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

QtMaterialBadge::QtMaterialBadge(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      d_ptr(new QtMaterialBadgePrivate(this))
{
    d_func()->init();
}

QtMaterialBadge::QtMaterialBadge(const QIcon &icon, QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      d_ptr(new QtMaterialBadgePrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

QtMaterialBadge::QtMaterialBadge(const QString &text, QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      d_ptr(new QtMaterialBadgePrivate(this))
{
    d_func()->init();

    setText(text);
}

QtMaterialBadge::~QtMaterialBadge()
{
}

void QtMaterialBadge::setUseThemeColors(bool value)
{
    Q_D(QtMaterialBadge);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialBadge::useThemeColors() const
{
    Q_D(const QtMaterialBadge);

    return d->useThemeColors;
}

void QtMaterialBadge::setTextColor(const QColor &color)
{
    Q_D(QtMaterialBadge);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialBadge::textColor() const
{
    Q_D(const QtMaterialBadge);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void QtMaterialBadge::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialBadge);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialBadge::backgroundColor() const
{
    Q_D(const QtMaterialBadge);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent1");
    } else {
        return d->backgroundColor;
    }
}

void QtMaterialBadge::setRelativePosition(const QPointF &pos)
{
    setRelativePosition(pos.x(), pos.y());
}

void QtMaterialBadge::setRelativePosition(qreal x, qreal y)
{
    Q_D(QtMaterialBadge);

    d->x = x;
    d->y = y;
    update();
}

QPointF QtMaterialBadge::relativePosition() const
{
    Q_D(const QtMaterialBadge);

    return QPointF(d->x, d->y);
}

void QtMaterialBadge::setRelativeXPosition(qreal x)
{
    Q_D(QtMaterialBadge);

    d->x = x;
    update();
}

qreal QtMaterialBadge::relativeXPosition() const
{
    Q_D(const QtMaterialBadge);

    return d->x;
}

void QtMaterialBadge::setRelativeYPosition(qreal y)
{
    Q_D(QtMaterialBadge);

    d->y = y;
    update();
}

qreal QtMaterialBadge::relativeYPosition() const
{
    Q_D(const QtMaterialBadge);

    return d->y;
}

/*!
 *  \reimp
 */
QSize QtMaterialBadge::sizeHint() const
{
    const int s = getDiameter();
    return QSize(s+4, s+4);
}

void QtMaterialBadge::setIcon(const QIcon &icon)
{
    Q_D(QtMaterialBadge);

    d->icon = icon;
    update();
}

QIcon QtMaterialBadge::icon() const
{
    Q_D(const QtMaterialBadge);

    return d->icon;
}

void QtMaterialBadge::setText(const QString &text)
{
    Q_D(QtMaterialBadge);

    d->text = text;

    if (!d->icon.isNull()) {
        d->icon = QIcon();
    }

    d->size = fontMetrics().size(Qt::TextShowMnemonic, text);

    update();
}

QString QtMaterialBadge::text() const
{
    Q_D(const QtMaterialBadge);

    return d->text;
}

/*!
 *  \reimp
 */
void QtMaterialBadge::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialBadge);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(d->x, d->y);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled() ? backgroundColor()
                               : QtMaterialStyle::instance().themeColor("disabled"));
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

int QtMaterialBadge::getDiameter() const
{
    Q_D(const QtMaterialBadge);

    if (d->icon.isNull()) {
        return qMax(d->size.width(), d->size.height()) + d->padding;
    } else {
        return 24;
    }
}
