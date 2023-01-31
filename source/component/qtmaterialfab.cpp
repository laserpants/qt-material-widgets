#include "qtmaterialfab.h"
#include "qtmaterialfab_p.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QState>
#include <QEvent>
#include <QPainter>
#include "lib/qtmaterialrippleoverlay.h"

/*!
 *  \class QtMaterialFloatingActionButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialFloatingActionButtonPrivate::QtMaterialFloatingActionButtonPrivate(QtMaterialFloatingActionButton *q)
    : QtMaterialRaisedButtonPrivate(q)
{
}

/*!
 *  \internal
 */
QtMaterialFloatingActionButtonPrivate::~QtMaterialFloatingActionButtonPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialFloatingActionButtonPrivate::init()
{
    Q_Q(QtMaterialFloatingActionButton);

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
QRect QtMaterialFloatingActionButtonPrivate::fabGeometry() const
{
    Q_Q(const QtMaterialFloatingActionButton);

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
void QtMaterialFloatingActionButtonPrivate::setupProperties()
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

QtMaterialFloatingActionButton::QtMaterialFloatingActionButton(const QIcon &icon, QWidget *parent)
    : QtMaterialRaisedButton(*new QtMaterialFloatingActionButtonPrivate(this), parent)
{
    d_func()->init();

    setIcon(icon);
}

QtMaterialFloatingActionButton::~QtMaterialFloatingActionButton()
{
}

/*!
 *  \reimp
 */
QSize QtMaterialFloatingActionButton::sizeHint() const
{
    Q_D(const QtMaterialFloatingActionButton);

    if (d->mini) {
        return QSize(QtMaterialFloatingActionButtonPrivate::MiniDiameter,
                     QtMaterialFloatingActionButtonPrivate::MiniDiameter);
    } else {
        return QSize(QtMaterialFloatingActionButtonPrivate::DefaultDiameter,
                     QtMaterialFloatingActionButtonPrivate::DefaultDiameter);
    }
}

void QtMaterialFloatingActionButton::setMini(bool state)
{
    Q_D(QtMaterialFloatingActionButton);

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

bool QtMaterialFloatingActionButton::isMini() const
{
    Q_D(const QtMaterialFloatingActionButton);

    return d->mini;
}

void QtMaterialFloatingActionButton::setCorner(Qt::Corner corner)
{
    Q_D(QtMaterialFloatingActionButton);

    if (d->corner == corner) {
        return;
    }

    d->corner = corner;
    setGeometry(d->fabGeometry());
    update();
}

Qt::Corner QtMaterialFloatingActionButton::corner() const
{
    Q_D(const QtMaterialFloatingActionButton);

    return d->corner;
}

void QtMaterialFloatingActionButton::setOffset(int x, int y)
{
    Q_D(QtMaterialFloatingActionButton);

    d->offsX = x;
    d->offsY = y;
    setGeometry(d->fabGeometry());
    update();
}

QSize QtMaterialFloatingActionButton::offset() const
{
    Q_D(const QtMaterialFloatingActionButton);

    return QSize(d->offsX, d->offsY);
}

void QtMaterialFloatingActionButton::setXOffset(int x)
{
    Q_D(QtMaterialFloatingActionButton);

    d->offsX = x;
    setGeometry(d->fabGeometry());
    update();
}

int QtMaterialFloatingActionButton::xOffset() const
{
    Q_D(const QtMaterialFloatingActionButton);

    return d->offsX;
}

void QtMaterialFloatingActionButton::setYOffset(int y)
{
    Q_D(QtMaterialFloatingActionButton);

    d->offsY = y;
    setGeometry(d->fabGeometry());
    update();
}

int QtMaterialFloatingActionButton::yOffset() const
{
    Q_D(const QtMaterialFloatingActionButton);

    return d->offsY;
}

/*!
 *  \reimp
 */
bool QtMaterialFloatingActionButton::event(QEvent *event)
{
    Q_D(QtMaterialFloatingActionButton);

    if (!parent()) {
        return QtMaterialRaisedButton::event(event);
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
    return QtMaterialRaisedButton::event(event);
}

/*!
 *  \reimp
 */
bool QtMaterialFloatingActionButton::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type)
    {
        Q_D(QtMaterialFloatingActionButton);
        setGeometry(d->fabGeometry());
    }

    return QtMaterialRaisedButton::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void QtMaterialFloatingActionButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialFloatingActionButton);

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

void QtMaterialFloatingActionButton::updateClipPath()
{
    Q_D(QtMaterialFloatingActionButton);

    QPainterPath path;
    path.addEllipse(0, 0, d->diameter(), d->diameter());
    d->rippleOverlay->setClipPath(path);
}
