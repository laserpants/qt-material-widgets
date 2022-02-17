#include "qtmaterialflatbutton.h"
#include "qtmaterialflatbutton_p.h"
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QBitmap>
#include <QPainterPath>
#include <QIcon>
#include "lib/qtmaterialrippleoverlay.h"
#include "lib/qtmaterialripple.h"
#include "lib/qtmaterialstyle.h"
#include "qtmaterialflatbutton_internal.h"

namespace md
{
/*!
 *  \class QtMaterialFlatButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
FlatButtonPrivate::FlatButtonPrivate(FlatButton *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
FlatButtonPrivate::~FlatButtonPrivate()
{
}

/*!
 *  \internal
 */
void FlatButtonPrivate::init()
{
    Q_Q(FlatButton);

    rippleOverlay        = new RippleOverlay(q);
    stateMachine         = new FlatButtonStateMachine(q);
    role                 = Material::Default;
    rippleStyle          = Material::PositionedRipple;
    iconPlacement        = Material::LeftIcon;
    overlayStyle         = Material::GrayOverlay;
    bgMode               = Qt::TransparentMode;
    textAlignment        = Qt::AlignHCenter;
    fixedRippleRadius    = 64;
    cornerRadius         = 3;
    baseOpacity          = 0.13;
    fontSize             = 10;        // 10.5;
    useThemeColors       = true;
    useFixedRippleRadius = false;
    haloVisible          = true;

    q->setStyle(&Style::instance());
    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);

    QFont font("Roboto", fontSize, QFont::Medium);
    font.setCapitalization(QFont::AllUppercase);
    q->setFont(font);

    QPainterPath path;
    path.addRoundedRect(q->rect(), cornerRadius, cornerRadius);
    rippleOverlay->setClipPath(path);
    rippleOverlay->setClipping(true);

    stateMachine->setupProperties();
    stateMachine->startAnimations();
}

/*!
 *  \class QtMaterialFlatButton
 */

FlatButton::FlatButton(QWidget *parent, Material::ButtonPreset preset)
    : QPushButton(parent),
      d_ptr(new FlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
}

FlatButton::FlatButton(const QString &text, QWidget *parent, Material::ButtonPreset preset)
    : QPushButton(text, parent),
      d_ptr(new FlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
}

FlatButton::FlatButton(const QString &text, Material::Role role, QWidget *parent, Material::ButtonPreset preset)
    : QPushButton(text, parent),
      d_ptr(new FlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
    setRole(role);
}

FlatButton::~FlatButton()
{
}

void FlatButton::applyPreset(Material::ButtonPreset preset)
{
    switch (preset)
    {
    case Material::FlatPreset:
        setOverlayStyle(Material::NoOverlay);
        break;
    case Material::CheckablePreset:
        setOverlayStyle(Material::NoOverlay);
        setCheckable(true);
        setHaloVisible(false);
        break;
    default:
        break;
    }
}

void FlatButton::setUseThemeColors(bool value)
{
    Q_D(FlatButton);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool FlatButton::useThemeColors() const
{
    Q_D(const FlatButton);

    return d->useThemeColors;
}

void FlatButton::setRole(Material::Role role)
{
    Q_D(FlatButton);

    d->role = role;
    d->stateMachine->setupProperties();
}

Material::Role FlatButton::role() const
{
    Q_D(const FlatButton);

    return d->role;
}

void FlatButton::setForegroundColor(const QColor &color)
{
    Q_D(FlatButton);

    d->foregroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor FlatButton::foregroundColor() const
{
    Q_D(const FlatButton);

    if (d->useThemeColors || !d->foregroundColor.isValid())
    {
        if (Qt::OpaqueMode == d->bgMode) {
            return Style::instance().themeColor("canvas");
        }
        switch (d->role)
        {
        case Material::Primary:
            return Style::instance().themeColor("primary1");
        case Material::Secondary:
            return Style::instance().themeColor("accent1");
        case Material::Default:
        default:
            return Style::instance().themeColor("text");
        }
    }
    return d->foregroundColor;
}

void FlatButton::setBackgroundColor(const QColor &color)
{
    Q_D(FlatButton);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor FlatButton::backgroundColor() const
{
    Q_D(const FlatButton);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        switch (d->role)
        {
        case Material::Primary:
            return Style::instance().themeColor("primary1");
        case Material::Secondary:
            return Style::instance().themeColor("accent1");
        case Material::Default:
        default:
            return Style::instance().themeColor("text");
        }
    }
    return d->backgroundColor;
}

void FlatButton::setOverlayColor(const QColor &color)
{
    Q_D(FlatButton);

    d->overlayColor = color;

    MATERIAL_DISABLE_THEME_COLORS

    setOverlayStyle(Material::TintedOverlay);
    update();
}

QColor FlatButton::overlayColor() const
{
    Q_D(const FlatButton);

    if (d->useThemeColors || !d->overlayColor.isValid()) {
        return foregroundColor();
    }
    return d->overlayColor;
}

void FlatButton::setDisabledForegroundColor(const QColor &color)
{
    Q_D(FlatButton);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor FlatButton::disabledForegroundColor() const
{
    Q_D(const FlatButton);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return Style::instance().themeColor("disabled");
    } else {
        return d->disabledColor;
    }
}

void FlatButton::setDisabledBackgroundColor(const QColor &color)
{
    Q_D(FlatButton);

    d->disabledBackgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor FlatButton::disabledBackgroundColor() const
{
    Q_D(const FlatButton);

    if (d->useThemeColors || !d->disabledBackgroundColor.isValid()) {
        return Style::instance().themeColor("disabled3");
    } else {
        return d->disabledBackgroundColor;
    }
}

void FlatButton::setFontSize(qreal size)
{
    Q_D(FlatButton);

    d->fontSize = size;

    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal FlatButton::fontSize() const
{
    Q_D(const FlatButton);

    return d->fontSize;
}

void FlatButton::setHaloVisible(bool visible)
{
    Q_D(FlatButton);

    d->haloVisible = visible;
    update();
}

bool FlatButton::isHaloVisible() const
{
    Q_D(const FlatButton);

    return d->haloVisible;
}

void FlatButton::setOverlayStyle(Material::OverlayStyle style)
{
    Q_D(FlatButton);

    d->overlayStyle = style;
    update();
}

Material::OverlayStyle FlatButton::overlayStyle() const
{
    Q_D(const FlatButton);

    return d->overlayStyle;
}

void FlatButton::setRippleStyle(Material::RippleStyle style)
{
    Q_D(FlatButton);

    d->rippleStyle = style;
}

Material::RippleStyle FlatButton::rippleStyle() const
{
    Q_D(const FlatButton);

    return d->rippleStyle;
}

void FlatButton::setIconPlacement(Material::ButtonIconPlacement placement)
{
    Q_D(FlatButton);

    d->iconPlacement = placement;
    update();
}

Material::ButtonIconPlacement FlatButton::iconPlacement() const
{
    Q_D(const FlatButton);

    return d->iconPlacement;
}

void FlatButton::setCornerRadius(qreal radius)
{
    Q_D(FlatButton);

    d->cornerRadius = radius;
    updateClipPath();
    update();
}

qreal FlatButton::cornerRadius() const
{
    Q_D(const FlatButton);

    return d->cornerRadius;
}

void FlatButton::setBackgroundMode(Qt::BGMode mode)
{
    Q_D(FlatButton);

    d->bgMode = mode;
    d->stateMachine->setupProperties();
}

Qt::BGMode FlatButton::backgroundMode() const
{
    Q_D(const FlatButton);

    return d->bgMode;
}

void FlatButton::setBaseOpacity(qreal opacity)
{
    Q_D(FlatButton);

    d->baseOpacity = opacity;
    d->stateMachine->setupProperties();
}

qreal FlatButton::baseOpacity() const
{
    Q_D(const FlatButton);

    return d->baseOpacity;
}

void FlatButton::setCheckable(bool value)
{
    Q_D(FlatButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::setCheckable(value);
}

void FlatButton::setHasFixedRippleRadius(bool value)
{
    Q_D(FlatButton);

    d->useFixedRippleRadius = value;
}

bool FlatButton::hasFixedRippleRadius() const
{
    Q_D(const FlatButton);

    return d->useFixedRippleRadius;
}

void FlatButton::setFixedRippleRadius(qreal radius)
{
    Q_D(FlatButton);

    d->fixedRippleRadius = radius;
    setHasFixedRippleRadius(true);
}

void FlatButton::setTextAlignment(Qt::Alignment alignment)
{
    Q_D(FlatButton);

    d->textAlignment = alignment;
}

Qt::Alignment FlatButton::textAlignment() const
{
    Q_D(const FlatButton);

    return d->textAlignment;
}

/*!
 *  \reimp
 */
QSize FlatButton::sizeHint() const
{
    ensurePolished();

    QSize label(fontMetrics().size(Qt::TextSingleLine, text()));

    int w = 20 + label.width();
    int h = label.height();
    if (!icon().isNull()) {
        w += iconSize().width() + FlatButton::IconPadding;
        h = qMax(h, iconSize().height());
    }
    return QSize(w, 20 + h);
}

FlatButton::FlatButton(FlatButtonPrivate &d,QWidget *parent, Material::ButtonPreset preset)
    : QPushButton(parent),
      d_ptr(&d)
{
    d_func()->init();

    applyPreset(preset);
}

/*!
 *  \reimp
 */
void FlatButton::checkStateSet()
{
    Q_D(FlatButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::checkStateSet();
}

/*!
 *  \reimp
 */
void FlatButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(FlatButton);

    if (Material::NoRipple != d->rippleStyle)
    {
        QPoint pos;
        qreal radiusEndValue;

        if (Material::CenteredRipple == d->rippleStyle) {
            pos = rect().center();
        } else {
            pos = event->pos();
        }

        if (d->useFixedRippleRadius) {
            radiusEndValue = d->fixedRippleRadius;
        } else {
            radiusEndValue = static_cast<qreal>(width())/2;
        }

        Ripple *ripple = new Ripple(pos);

        ripple->setRadiusEndValue(radiusEndValue);
        ripple->setOpacityStartValue(0.35);
        ripple->setColor(foregroundColor());
        ripple->radiusAnimation()->setDuration(600);
        ripple->opacityAnimation()->setDuration(1300);

        d->rippleOverlay->addRipple(ripple);
    }

    QPushButton::mousePressEvent(event);
}

/*!
 *  \reimp
 */
void FlatButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(FlatButton);

    QPushButton::mouseReleaseEvent(event);

    d->stateMachine->updateCheckedStatus();
}

void FlatButton::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);

    updateClipPath();
}

/*!
 *  \reimp
 */
void FlatButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(FlatButton);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const qreal cr = d->cornerRadius;

    if (cr > 0)
    {
        QPainterPath path;
        path.addRoundedRect(rect(), cr, cr);

        painter.setClipPath(path);
        painter.setClipping(true);
    }

    paintBackground(&painter);
    paintHalo(&painter);

    painter.setOpacity(1);
    painter.setClipping(false);

    paintForeground(&painter);
}

/*!
 *  \internal
 */
void FlatButton::paintBackground(QPainter *painter)
{
    Q_D(FlatButton);

    const qreal overlayOpacity = d->stateMachine->overlayOpacity();
    const qreal checkedProgress = d->stateMachine->checkedOverlayProgress();

    if (Qt::OpaqueMode == d->bgMode) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        if (isEnabled()) {
            brush.setColor(backgroundColor());
        } else {
            brush.setColor(disabledBackgroundColor());
        }
        painter->setOpacity(1);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        painter->drawRect(rect());
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(Qt::NoPen);

    if (!isEnabled()) {
        return;
    }

    if ((Material::NoOverlay != d->overlayStyle) && (overlayOpacity > 0)) {
        if (Material::TintedOverlay == d->overlayStyle) {
            brush.setColor(overlayColor());
        } else {
            brush.setColor(Qt::gray);
        }
        painter->setOpacity(overlayOpacity);
        painter->setBrush(brush);
        painter->drawRect(rect());
    }

    if (isCheckable() && checkedProgress > 0) {
        const qreal q = Qt::TransparentMode == d->bgMode ? 0.45 : 0.7;
        brush.setColor(foregroundColor());
        painter->setOpacity(q*checkedProgress);
        painter->setBrush(brush);
        QRect r(rect());
        r.setHeight(static_cast<qreal>(r.height())*checkedProgress);
        painter->drawRect(r);
    }
}

/*!
 *  \internal
 */
void FlatButton::paintHalo(QPainter *painter)
{
    Q_D(FlatButton);

    if (!d->haloVisible) {
        return;
    }

    const qreal opacity = d->stateMachine->haloOpacity();
    const qreal s = d->stateMachine->haloScaleFactor()*d->stateMachine->haloSize();
    const qreal radius = static_cast<qreal>(width())*s;

    if (isEnabled() && opacity > 0) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(foregroundColor());
        painter->setOpacity(opacity);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        const QPointF center = rect().center();
        painter->drawEllipse(center, radius, radius);
    }
}

#define COLOR_INTERPOLATE(CH) (1-progress)*source.CH() + progress*dest.CH()

/*!
 *  \internal
 */
void FlatButton::paintForeground(QPainter *painter)
{
    Q_D(FlatButton);

    if (isEnabled()) {
        painter->setPen(foregroundColor());
        const qreal progress = d->stateMachine->checkedOverlayProgress();
        if (isCheckable() && progress > 0) {
            QColor source = foregroundColor();
            QColor dest = Qt::TransparentMode == d->bgMode ? Qt::white
                                                           : backgroundColor();
            if (qFuzzyCompare(1, progress)) {
                painter->setPen(dest);
            } else {
                painter->setPen(QColor(COLOR_INTERPOLATE(red),
                                       COLOR_INTERPOLATE(green),
                                       COLOR_INTERPOLATE(blue),
                                       COLOR_INTERPOLATE(alpha)));
            }
        }
    } else {
        painter->setPen(disabledForegroundColor());
    }

    if (icon().isNull())  {
        if (Qt::AlignLeft == d->textAlignment) {
            painter->drawText(rect().adjusted(12, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text());
        } else {
            painter->drawText(rect(), Qt::AlignCenter, text());
        }
        return;
    }

    QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
    QSize base(size()-textSize);

    const int iw = iconSize().width() + IconPadding;
    QPoint pos(Qt::AlignLeft == d->textAlignment ? 12 : (base.width()-iw)/2, 0);

    QRect textGeometry(pos + QPoint(0, base.height()/2), textSize);
    QRect iconGeometry(pos + QPoint(0, (height()-iconSize().height())/2), iconSize());

    if (Material::LeftIcon == d->iconPlacement) {
        textGeometry.translate(iw, 0);
    } else {
        iconGeometry.translate(textSize.width() + IconPadding, 0);
    }

    painter->drawText(textGeometry, Qt::AlignCenter, text());

    QPixmap pixmap = icon().pixmap(iconSize());
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    icon.fillRect(pixmap.rect(), painter->pen().color());
    painter->drawPixmap(iconGeometry, pixmap);
}

/*!
 *  \internal
 */
void FlatButton::updateClipPath()
{
    Q_D(FlatButton);

    const qreal radius = d->cornerRadius;

    QPainterPath path;
    path.addRoundedRect(rect(), radius, radius);
    d->rippleOverlay->setClipPath(path);
}
}
