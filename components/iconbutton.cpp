#include "iconbutton.h"
#include "iconbutton_p.h"
#include <QPainter>
#include <QEvent>
#include "lib/style.h"
#include "lib/rippleoverlay.h"

namespace md
{
/*!
 *  \class QtMaterialIconButtonPrivate
 *  \internal
 */

IconButtonPrivate::IconButtonPrivate(IconButton *q)
    : q_ptr(q)
{
}

IconButtonPrivate::~IconButtonPrivate()
{
}

void IconButtonPrivate::init()
{
    Q_Q(IconButton);

    rippleOverlay  = new RippleOverlay(q->parentWidget());
    useThemeColors = true;

    rippleOverlay->installEventFilter(q);

    q->setStyle(&Style::instance());

    QSizePolicy policy;
    policy.setWidthForHeight(true);
    q->setSizePolicy(policy);
}

void IconButtonPrivate::updateRipple()
{
    Q_Q(IconButton);

    QRect r(q->rect());
    r.setSize(QSize(q->width()*2, q->height()*2));
    r.moveCenter(q->geometry().center());
    rippleOverlay->setGeometry(r);
}

/*!
 *  \class QtMaterialIconButton
 */

IconButton::IconButton(const QIcon &icon, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new IconButtonPrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

IconButton::~IconButton()
{
}

/*!
 *  \reimp
 */
QSize IconButton::sizeHint() const
{
    return iconSize();
}

void IconButton::setUseThemeColors(bool value)
{
    Q_D(IconButton);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool IconButton::useThemeColors() const
{
    Q_D(const IconButton);

    return d->useThemeColors;
}

void IconButton::setColor(const QColor &color)
{
    Q_D(IconButton);

    d->color = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor IconButton::color() const
{
    Q_D(const IconButton);

    if (d->useThemeColors || !d->color.isValid()) {
        return Style::instance().themeColor("text");
    }
    return d->color;
}

void IconButton::setDisabledColor(const QColor &color)
{
    Q_D(IconButton);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor IconButton::disabledColor() const
{
    Q_D(const IconButton);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return Style::instance().themeColor("disabled");
    }
    return d->disabledColor;
}

IconButton::IconButton(IconButtonPrivate &d, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
bool IconButton::event(QEvent *event)
{
    Q_D(IconButton);

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
        d->updateRipple();
        break;
    case QEvent::ParentChange: {
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->rippleOverlay->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QAbstractButton::event(event);
}

/*!
 *  \reimp
 */
bool IconButton::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(IconButton);

        d->updateRipple();
    }
    return QAbstractButton::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void IconButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(IconButton);

    d->rippleOverlay->addRipple(QPoint(d->rippleOverlay->width(),
                                       d->rippleOverlay->height())/2,
                                iconSize().width());
    emit clicked();

    QAbstractButton::mousePressEvent(event);
}

/*!
 *  \reimp
 */
void IconButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QPixmap pixmap = icon().pixmap(iconSize());
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    icon.fillRect(pixmap.rect(), isEnabled() ? color() : disabledColor());

    QRect r(rect());
    const qreal w = pixmap.width();
    const qreal h = pixmap.height();
    painter.drawPixmap(QRect((r.width()-w)/2, (r.height()-h)/2, w, h), pixmap);
}

}
