#include "avatar.h"
#include "avatar_p.h"
#include <QPainter>
#include <QPainterPath>
#include "lib/style.h"

namespace md
{
/*!
 *  \class QtMaterialAvatarPrivate
 *  \internal
 */

/*!
 *  \internal
 */
AvatarPrivate::AvatarPrivate(Avatar *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
AvatarPrivate::~AvatarPrivate()
{
}

/*!
 *  \internal
 */
void AvatarPrivate::init()
{
    Q_Q(Avatar);

    size           = 40;
    type           = Material::LetterAvatar;
    useThemeColors = true;

    QFont font(q->font());
    font.setPointSizeF(16);
    q->setFont(font);

    QSizePolicy policy(QSizePolicy::MinimumExpanding,
                       QSizePolicy::MinimumExpanding);
    q->setSizePolicy(policy);
}

/*!
 *  \class QtMaterialAvatar
 */

Avatar::Avatar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new AvatarPrivate(this))
{
    d_func()->init();
}

Avatar::Avatar(const QIcon &icon, QWidget *parent)
    : QWidget(parent),
      d_ptr(new AvatarPrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

Avatar::Avatar(const QChar &letter, QWidget *parent)
    : QWidget(parent),
      d_ptr(new AvatarPrivate(this))
{
    d_func()->init();

    setLetter(letter);
}

Avatar::Avatar(const QImage &image, QWidget *parent)
    : QWidget(parent),
      d_ptr(new AvatarPrivate(this))
{
    d_func()->init();

    setImage(image);
}

Avatar::~Avatar()
{
}

void Avatar::setUseThemeColors(bool value)
{
    Q_D(Avatar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool Avatar::useThemeColors() const
{
    Q_D(const Avatar);

    return d->useThemeColors;
}

void Avatar::setTextColor(const QColor &color)
{
    Q_D(Avatar);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor Avatar::textColor() const
{
    Q_D(const Avatar);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void Avatar::setBackgroundColor(const QColor &color)
{
    Q_D(Avatar);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor Avatar::backgroundColor() const
{
    Q_D(const Avatar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

/*!
 *  \reimp
 */
QSize Avatar::sizeHint() const
{
    Q_D(const Avatar);

    return QSize(d->size+2, d->size+2);
}

void Avatar::setSize(int size)
{
    Q_D(Avatar);

    d->size = size;

    if (!d->image.isNull()) {
        d->pixmap = QPixmap::fromImage(d->image.scaled(d->size, d->size,
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation));
    }

    QFont f(font());
    f.setPointSizeF(size*16/40);
    setFont(f);

    update();
}

int Avatar::size() const
{
    Q_D(const Avatar);

    return d->size;
}

void Avatar::setLetter(const QChar &letter)
{
    Q_D(Avatar);

    d->letter = letter;
    d->type = Material::LetterAvatar;
    update();
}

void Avatar::setImage(const QImage &image)
{
    Q_D(Avatar);

    d->image = image;
    d->type = Material::ImageAvatar;

    d->pixmap = QPixmap::fromImage(image.scaled(d->size, d->size,
                                                Qt::IgnoreAspectRatio,
                                                Qt::SmoothTransformation));
    update();
}

void Avatar::setIcon(const QIcon &icon)
{
    Q_D(Avatar);

    d->icon = icon;
    d->type = Material::IconAvatar;
    update();
}

Material::AvatarType Avatar::type() const
{
    Q_D(const Avatar);

    return d->type;
}

/*!
 *  \reimp
 */
void Avatar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Avatar);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    const qreal hs = d->size/2;

    if (!isEnabled())
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Style::instance().themeColor("disabled"));
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(QRectF((width()-d->size)/2, (height()-d->size)/2,
                                   d->size, d->size));
        return;
    }

    if (Material::ImageAvatar != d->type)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(backgroundColor());
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(QRectF((width()-d->size)/2, (height()-d->size)/2,
                                   d->size, d->size));
    }

    switch (d->type)
    {
    case Material::ImageAvatar:
    {
        QPainterPath path;
        path.addEllipse(width()/2-hs, height()/2-hs, d->size, d->size);
        painter.setClipPath(path);

        painter.drawPixmap(QRect(width()/2-hs, height()/2-hs, d->size, d->size),
                           d->pixmap);
        break;
    }
    case Material::IconAvatar:
    {
        QRect iconGeometry((width()-hs)/2, (height()-hs)/2, hs, hs);
        QPixmap pixmap = d->icon.pixmap(hs, hs);
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), textColor());
        painter.drawPixmap(iconGeometry, pixmap);
        break;
    }
    case Material::LetterAvatar:
    {
        painter.setPen(textColor());
        painter.setBrush(Qt::NoBrush);
        painter.drawText(r, Qt::AlignCenter, QString(d->letter));
        break;
    }
    default:
        break;
    }
}

}
