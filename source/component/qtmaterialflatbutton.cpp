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

/*!
 *  \class QtMaterialFlatButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialFlatButtonPrivate::QtMaterialFlatButtonPrivate(QtMaterialFlatButton *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialFlatButtonPrivate::~QtMaterialFlatButtonPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialFlatButtonPrivate::init()
{
    Q_Q(QtMaterialFlatButton);

    rippleOverlay        = new QtMaterialRippleOverlay(q);
    stateMachine         = new QtMaterialFlatButtonStateMachine(q);
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

    q->setStyle(&QtMaterialStyle::instance());
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

QtMaterialFlatButton::QtMaterialFlatButton(QWidget *parent, Material::ButtonPreset preset)
    : QPushButton(parent),
      d_ptr(new QtMaterialFlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
}

QtMaterialFlatButton::QtMaterialFlatButton(const QString &text, QWidget *parent, Material::ButtonPreset preset)
    : QPushButton(text, parent),
      d_ptr(new QtMaterialFlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
}

QtMaterialFlatButton::QtMaterialFlatButton(const QString &text, Material::Role role, QWidget *parent, Material::ButtonPreset preset)
    : QPushButton(text, parent),
      d_ptr(new QtMaterialFlatButtonPrivate(this))
{
    d_func()->init();

    applyPreset(preset);
    setRole(role);
}

QtMaterialFlatButton::~QtMaterialFlatButton()
{
}

void QtMaterialFlatButton::applyPreset(Material::ButtonPreset preset)
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

void QtMaterialFlatButton::setUseThemeColors(bool value)
{
    Q_D(QtMaterialFlatButton);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool QtMaterialFlatButton::useThemeColors() const
{
    Q_D(const QtMaterialFlatButton);

    return d->useThemeColors;
}

void QtMaterialFlatButton::setRole(Material::Role role)
{
    Q_D(QtMaterialFlatButton);

    d->role = role;
    d->stateMachine->setupProperties();
}

Material::Role QtMaterialFlatButton::role() const
{
    Q_D(const QtMaterialFlatButton);

    return d->role;
}

void QtMaterialFlatButton::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialFlatButton);

    d->foregroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialFlatButton::foregroundColor() const
{
    Q_D(const QtMaterialFlatButton);

    if (d->useThemeColors || !d->foregroundColor.isValid())
    {
        if (Qt::OpaqueMode == d->bgMode) {
            return QtMaterialStyle::instance().themeColor("canvas");
        }
        switch (d->role)
        {
        case Material::Primary:
            return QtMaterialStyle::instance().themeColor("primary1");
        case Material::Secondary:
            return QtMaterialStyle::instance().themeColor("accent1");
        case Material::Default:
        default:
            return QtMaterialStyle::instance().themeColor("text");
        }
    }
    return d->foregroundColor;
}

void QtMaterialFlatButton::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialFlatButton);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialFlatButton::backgroundColor() const
{
    Q_D(const QtMaterialFlatButton);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        switch (d->role)
        {
        case Material::Primary:
            return QtMaterialStyle::instance().themeColor("primary1");
        case Material::Secondary:
            return QtMaterialStyle::instance().themeColor("accent1");
        case Material::Default:
        default:
            return QtMaterialStyle::instance().themeColor("text");
        }
    }
    return d->backgroundColor;
}

void QtMaterialFlatButton::setOverlayColor(const QColor &color)
{
    Q_D(QtMaterialFlatButton);

    d->overlayColor = color;

    MATERIAL_DISABLE_THEME_COLORS

    setOverlayStyle(Material::TintedOverlay);
    update();
}

QColor QtMaterialFlatButton::overlayColor() const
{
    Q_D(const QtMaterialFlatButton);

    if (d->useThemeColors || !d->overlayColor.isValid()) {
        return foregroundColor();
    }
    return d->overlayColor;
}

void QtMaterialFlatButton::setDisabledForegroundColor(const QColor &color)
{
    Q_D(QtMaterialFlatButton);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialFlatButton::disabledForegroundColor() const
{
    Q_D(const QtMaterialFlatButton);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("disabled");
    } else {
        return d->disabledColor;
    }
}

void QtMaterialFlatButton::setDisabledBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialFlatButton);

    d->disabledBackgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialFlatButton::disabledBackgroundColor() const
{
    Q_D(const QtMaterialFlatButton);

    if (d->useThemeColors || !d->disabledBackgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("disabled3");
    } else {
        return d->disabledBackgroundColor;
    }
}

void QtMaterialFlatButton::setFontSize(qreal size)
{
    Q_D(QtMaterialFlatButton);

    d->fontSize = size;

    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal QtMaterialFlatButton::fontSize() const
{
    Q_D(const QtMaterialFlatButton);

    return d->fontSize;
}

void QtMaterialFlatButton::setHaloVisible(bool visible)
{
    Q_D(QtMaterialFlatButton);

    d->haloVisible = visible;
    update();
}

bool QtMaterialFlatButton::isHaloVisible() const
{
    Q_D(const QtMaterialFlatButton);

    return d->haloVisible;
}

void QtMaterialFlatButton::setOverlayStyle(Material::OverlayStyle style)
{
    Q_D(QtMaterialFlatButton);

    d->overlayStyle = style;
    update();
}

Material::OverlayStyle QtMaterialFlatButton::overlayStyle() const
{
    Q_D(const QtMaterialFlatButton);

    return d->overlayStyle;
}

void QtMaterialFlatButton::setRippleStyle(Material::RippleStyle style)
{
    Q_D(QtMaterialFlatButton);

    d->rippleStyle = style;
}

Material::RippleStyle QtMaterialFlatButton::rippleStyle() const
{
    Q_D(const QtMaterialFlatButton);

    return d->rippleStyle;
}

void QtMaterialFlatButton::setIconPlacement(Material::ButtonIconPlacement placement)
{
    Q_D(QtMaterialFlatButton);

    d->iconPlacement = placement;
    update();
}

Material::ButtonIconPlacement QtMaterialFlatButton::iconPlacement() const
{
    Q_D(const QtMaterialFlatButton);

    return d->iconPlacement;
}

void QtMaterialFlatButton::setCornerRadius(qreal radius)
{
    Q_D(QtMaterialFlatButton);

    d->cornerRadius = radius;
    updateClipPath();
    update();
}

qreal QtMaterialFlatButton::cornerRadius() const
{
    Q_D(const QtMaterialFlatButton);

    return d->cornerRadius;
}

void QtMaterialFlatButton::setBackgroundMode(Qt::BGMode mode)
{
    Q_D(QtMaterialFlatButton);

    d->bgMode = mode;
    d->stateMachine->setupProperties();
}

Qt::BGMode QtMaterialFlatButton::backgroundMode() const
{
    Q_D(const QtMaterialFlatButton);

    return d->bgMode;
}

void QtMaterialFlatButton::setBaseOpacity(qreal opacity)
{
    Q_D(QtMaterialFlatButton);

    d->baseOpacity = opacity;
    d->stateMachine->setupProperties();
}

qreal QtMaterialFlatButton::baseOpacity() const
{
    Q_D(const QtMaterialFlatButton);

    return d->baseOpacity;
}

void QtMaterialFlatButton::setCheckable(bool value)
{
    Q_D(QtMaterialFlatButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::setCheckable(value);
}

void QtMaterialFlatButton::setHasFixedRippleRadius(bool value)
{
    Q_D(QtMaterialFlatButton);

    d->useFixedRippleRadius = value;
}

bool QtMaterialFlatButton::hasFixedRippleRadius() const
{
    Q_D(const QtMaterialFlatButton);

    return d->useFixedRippleRadius;
}

void QtMaterialFlatButton::setFixedRippleRadius(qreal radius)
{
    Q_D(QtMaterialFlatButton);

    d->fixedRippleRadius = radius;
    setHasFixedRippleRadius(true);
}

void QtMaterialFlatButton::setTextAlignment(Qt::Alignment alignment)
{
    Q_D(QtMaterialFlatButton);

    d->textAlignment = alignment;
}

Qt::Alignment QtMaterialFlatButton::textAlignment() const
{
    Q_D(const QtMaterialFlatButton);

    return d->textAlignment;
}

/*!
 *  \reimp
 */
QSize QtMaterialFlatButton::sizeHint() const
{
    ensurePolished();

    QSize label(fontMetrics().size(Qt::TextSingleLine, text()));

    int w = 20 + label.width();
    int h = label.height();
    if (!icon().isNull()) {
        w += iconSize().width() + QtMaterialFlatButton::IconPadding;
        h = qMax(h, iconSize().height());
    }
    return QSize(w, 20 + h);
}

QtMaterialFlatButton::QtMaterialFlatButton(QtMaterialFlatButtonPrivate &d,QWidget *parent, Material::ButtonPreset preset)
    : QPushButton(parent),
      d_ptr(&d)
{
    d_func()->init();

    applyPreset(preset);
}

/*!
 *  \reimp
 */
void QtMaterialFlatButton::checkStateSet()
{
    Q_D(QtMaterialFlatButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::checkStateSet();
}

/*!
 *  \reimp
 */
void QtMaterialFlatButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialFlatButton);

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

        QtMaterialRipple *ripple = new QtMaterialRipple(pos);

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
void QtMaterialFlatButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QtMaterialFlatButton);

    QPushButton::mouseReleaseEvent(event);

    d->stateMachine->updateCheckedStatus();
}

void QtMaterialFlatButton::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);

    updateClipPath();
}

/*!
 *  \reimp
 */
void QtMaterialFlatButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialFlatButton);

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
void QtMaterialFlatButton::paintBackground(QPainter *painter)
{
    Q_D(QtMaterialFlatButton);

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
void QtMaterialFlatButton::paintHalo(QPainter *painter)
{
    Q_D(QtMaterialFlatButton);

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
void QtMaterialFlatButton::paintForeground(QPainter *painter)
{
    Q_D(QtMaterialFlatButton);

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
void QtMaterialFlatButton::updateClipPath()
{
    Q_D(QtMaterialFlatButton);

    const qreal radius = d->cornerRadius;

    QPainterPath path;
    path.addRoundedRect(rect(), radius, radius);
    d->rippleOverlay->setClipPath(path);
}
