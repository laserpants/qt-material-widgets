#include "qtmaterialavatar.h"
#include "qtmaterialavatar_p.h"
#include <QPainter>
#include <QPainterPath>
#include "lib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialAvatarPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialAvatarPrivate::QtMaterialAvatarPrivate(QtMaterialAvatar *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialAvatarPrivate::~QtMaterialAvatarPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialAvatarPrivate::init()
{
    Q_Q(QtMaterialAvatar);

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

QtMaterialAvatar::QtMaterialAvatar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialAvatarPrivate(this))
{
    d_func()->init();
}

QtMaterialAvatar::QtMaterialAvatar(const QIcon &icon, QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialAvatarPrivate(this))
{
    d_func()->init();

    setIcon(icon);
}

QtMaterialAvatar::QtMaterialAvatar(const QChar &letter, QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialAvatarPrivate(this))
{
    d_func()->init();

    setLetter(letter);
}

QtMaterialAvatar::QtMaterialAvatar(const QImage &image, QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialAvatarPrivate(this))
{
    d_func()->init();

    setImage(image);
}

QtMaterialAvatar::~QtMaterialAvatar()
{
}

void QtMaterialAvatar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialAvatar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialAvatar::useThemeColors() const
{
    Q_D(const QtMaterialAvatar);

    return d->useThemeColors;
}

void QtMaterialAvatar::setTextColor(const QColor &color)
{
    Q_D(QtMaterialAvatar);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialAvatar::textColor() const
{
    Q_D(const QtMaterialAvatar);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void QtMaterialAvatar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialAvatar);

    d->backgroundColor = color;
    
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialAvatar::backgroundColor() const
{
    Q_D(const QtMaterialAvatar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

/*!
 *  \reimp
 */
QSize QtMaterialAvatar::sizeHint() const
{
    Q_D(const QtMaterialAvatar);

    return QSize(d->size+2, d->size+2);
}

void QtMaterialAvatar::setSize(int size)
{
    Q_D(QtMaterialAvatar);

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

int QtMaterialAvatar::size() const
{
    Q_D(const QtMaterialAvatar);

    return d->size;
}

void QtMaterialAvatar::setLetter(const QChar &letter)
{
    Q_D(QtMaterialAvatar);

    d->letter = letter;
    d->type = Material::LetterAvatar;
    update();
}

void QtMaterialAvatar::setImage(const QImage &image)
{
    Q_D(QtMaterialAvatar);

    d->image = image;
    d->type = Material::ImageAvatar;

    d->pixmap = QPixmap::fromImage(image.scaled(d->size, d->size,
                                                Qt::IgnoreAspectRatio,
                                                Qt::SmoothTransformation));
    update();
}

void QtMaterialAvatar::setIcon(const QIcon &icon)
{
    Q_D(QtMaterialAvatar);

    d->icon = icon;
    d->type = Material::IconAvatar;
    update();
}

Material::AvatarType QtMaterialAvatar::type() const
{
    Q_D(const QtMaterialAvatar);

    return d->type;
}

/*!
 *  \reimp
 */
void QtMaterialAvatar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialAvatar);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    const qreal hs = d->size/2.0;

    if (!isEnabled())
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QtMaterialStyle::instance().themeColor("disabled"));
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
