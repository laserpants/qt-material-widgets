#include "fab.h"
#include "fab_p.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QState>
#include <QEvent>
#include <QPainter>
#include "lib/rippleoverlay.h"
namespace md
{

/*!
 *  \class QtMaterialFloatingActionButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
FloatingActionButtonPrivate::FloatingActionButtonPrivate(FloatingActionButton *q)
    : RaisedButtonPrivate(q)
{
}

/*!
 *  \internal
 */
FloatingActionButtonPrivate::~FloatingActionButtonPrivate()
{
}

/*!
 *  \internal
 */
void FloatingActionButtonPrivate::init()
{
    Q_Q(FloatingActionButton);

    corner = Qt::BottomRightCorner;
    mini   = false;
    offsX  = 34;
    offsY  = 36;

    q->setRole(Material::Primary);
    q->setFixedSize(DefaultDiameter, DefaultDiameter);
    q->setGeometry(fabGeometry());

    setupProperties();

    if (q->parentWidget()) {
        q->parentWidget()->installEventFilter(q);
    }

    q->setFixedRippleRadius(50);
}

/*!
 *  \internal
 */
QRect FloatingActionButtonPrivate::fabGeometry() const
{
    Q_Q(const FloatingActionButton);

    QWidget *parent = q->parentWidget();
    if (!parent) {
        return QRect();
    }

    const int s = mini ? MiniDiameter : DefaultDiameter;

    switch (corner)
    {
    case Qt::TopLeftCorner:
        return QRect(offsX, offsY, s, s);
    case Qt::TopRightCorner:
        return QRect(parent->width()-(offsX+s), offsY, s, s);
    case Qt::BottomLeftCorner:
        return QRect(offsX, parent->height()-(offsY+s), s, s);
    case Qt::BottomRightCorner:
    default:
        break;
    }
    return QRect(parent->width()-(offsX+s), parent->height()-(offsY+s), s, s);
}

/*!
 *  \internal
 */
void FloatingActionButtonPrivate::setupProperties()
{
    if (mini) {
        effect->setColor(QColor(0, 0, 0, 80));
        normalState->assignProperty(effect, "offset", QPointF(0, 3));
        normalState->assignProperty(effect, "blurRadius", 13);
        pressedState->assignProperty(effect, "offset", QPointF(0, 7));
        pressedState->assignProperty(effect, "blurRadius", 20);
    } else {
        effect->setColor(QColor(0, 0, 0, 105));
        normalState->assignProperty(effect, "offset", QPointF(0, 6));
        normalState->assignProperty(effect, "blurRadius", 16);
        pressedState->assignProperty(effect, "offset", QPointF(0, 11));
        pressedState->assignProperty(effect, "blurRadius", 28);
    }
}

/*!
 *  \class QtMaterialFloatingActionButton
 */

FloatingActionButton::FloatingActionButton(const QIcon &icon, QWidget *parent)
    : RaisedButton(*new FloatingActionButtonPrivate(this), parent)
{
    d_func()->init();

    setIcon(icon);
}

FloatingActionButton::~FloatingActionButton()
{
}

/*!
 *  \reimp
 */
QSize FloatingActionButton::sizeHint() const
{
    Q_D(const FloatingActionButton);

    if (d->mini) {
        return QSize(FloatingActionButtonPrivate::MiniDiameter,
                     FloatingActionButtonPrivate::MiniDiameter);
    } else {
        return QSize(FloatingActionButtonPrivate::DefaultDiameter,
                     FloatingActionButtonPrivate::DefaultDiameter);
    }
}

void FloatingActionButton::setMini(bool state)
{
    Q_D(FloatingActionButton);

    if (d->mini == state) {
        return;
    }

    d->mini = state;

    setFixedSize(d->diameter(), d->diameter());
    setFixedRippleRadius(state ? 30 : 50);

    d->setupProperties();
    updateClipPath();
    setGeometry(d->fabGeometry());
    update();
}

bool FloatingActionButton::isMini() const
{
    Q_D(const FloatingActionButton);

    return d->mini;
}

void FloatingActionButton::setCorner(Qt::Corner corner)
{
    Q_D(FloatingActionButton);

    if (d->corner == corner) {
        return;
    }

    d->corner = corner;
    setGeometry(d->fabGeometry());
    update();
}

Qt::Corner FloatingActionButton::corner() const
{
    Q_D(const FloatingActionButton);

    return d->corner;
}

void FloatingActionButton::setOffset(int x, int y)
{
    Q_D(FloatingActionButton);

    d->offsX = x;
    d->offsY = y;
    setGeometry(d->fabGeometry());
    update();
}

QSize FloatingActionButton::offset() const
{
    Q_D(const FloatingActionButton);

    return QSize(d->offsX, d->offsY);
}

void FloatingActionButton::setXOffset(int x)
{
    Q_D(FloatingActionButton);

    d->offsX = x;
    setGeometry(d->fabGeometry());
    update();
}

int FloatingActionButton::xOffset() const
{
    Q_D(const FloatingActionButton);

    return d->offsX;
}

void FloatingActionButton::setYOffset(int y)
{
    Q_D(FloatingActionButton);

    d->offsY = y;
    setGeometry(d->fabGeometry());
    update();
}

int FloatingActionButton::yOffset() const
{
    Q_D(const FloatingActionButton);

    return d->offsY;
}

/*!
 *  \reimp
 */
bool FloatingActionButton::event(QEvent *event)
{
    Q_D(FloatingActionButton);

    if (!parent()) {
        return RaisedButton::event(event);
    }
    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        parent()->installEventFilter(this);
        setGeometry(d->fabGeometry());
        break;
    }
    case QEvent::ParentAboutToChange:
    {
        parent()->removeEventFilter(this);
        break;
    }
    default:
        break;
    }
    return RaisedButton::event(event);
}

/*!
 *  \reimp
 */
bool FloatingActionButton::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type)
    {
        Q_D(FloatingActionButton);
        setGeometry(d->fabGeometry());
    }

    return RaisedButton::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void FloatingActionButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(FloatingActionButton);

    QRect square = QRect(0, 0, d->diameter(), d->diameter());
    square.moveCenter(rect().center());

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    if (isEnabled()) {
        brush.setColor(backgroundColor());
    } else {
        brush.setColor(disabledBackgroundColor());
    }

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(square);

    QRect iconGeometry(0, 0, d->iconSize(), d->iconSize());
    iconGeometry.moveCenter(square.center());

    QPixmap pixmap = icon().pixmap(QSize(d->iconSize(), d->iconSize()));
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    icon.fillRect(pixmap.rect(), isEnabled() ? foregroundColor()
                                             : disabledForegroundColor());
    painter.drawPixmap(iconGeometry, pixmap);
}

void FloatingActionButton::updateClipPath()
{
    Q_D(FloatingActionButton);

    QPainterPath path;
    path.addEllipse(0, 0, d->diameter(), d->diameter());
    d->rippleOverlay->setClipPath(path);
}

}
