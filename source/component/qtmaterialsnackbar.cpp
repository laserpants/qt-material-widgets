#include "qtmaterialsnackbar.h"
#include "qtmaterialsnackbar_p.h"
#include <QtWidgets/QApplication>
#include <QPainter>
#include "qtmaterialsnackbar_internal.h"
#include "lib/qtmaterialstyle.h"
#include "lib/qtmaterialstatetransition.h"
#include <QDebug>

/*!
 *  \class QtMaterialSnackbarPrivate
 *  \internal
 */

QtMaterialSnackbarPrivate::QtMaterialSnackbarPrivate(QtMaterialSnackbar *q)
    : q_ptr(q)
{
}

QtMaterialSnackbarPrivate::~QtMaterialSnackbarPrivate()
{
}

void QtMaterialSnackbarPrivate::init()
{
    Q_Q(QtMaterialSnackbar);

    stateMachine   = new QtMaterialSnackbarStateMachine(q);
    bgOpacity      = 0.9;
    duration       = 3000;
    boxWidth       = 300;
    clickDismiss   = false;
    useThemeColors = true;

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QFont font("Roboto", 10, QFont::Medium);
    font.setCapitalization(QFont::AllUppercase);
    q->setFont(font);

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class QtMaterialSnackbar
 */

QtMaterialSnackbar::QtMaterialSnackbar(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      d_ptr(new QtMaterialSnackbarPrivate(this))
{
    d_func()->init();
}

QtMaterialSnackbar::~QtMaterialSnackbar()
{
}

void QtMaterialSnackbar::setAutoHideDuration(int duration)
{
    Q_D(QtMaterialSnackbar);

    d->duration = duration;
}

int QtMaterialSnackbar::autoHideDuration() const
{
    Q_D(const QtMaterialSnackbar);

    return d->duration;
}

void QtMaterialSnackbar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSnackbar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialSnackbar::useThemeColors() const
{
    Q_D(const QtMaterialSnackbar);

    return d->useThemeColors;
}

void QtMaterialSnackbar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSnackbar);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialSnackbar::backgroundColor() const
{
    Q_D(const QtMaterialSnackbar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->backgroundColor;
    }
}

void QtMaterialSnackbar::setBackgroundOpacity(qreal opacity)
{
    Q_D(QtMaterialSnackbar);

    d->bgOpacity = opacity;
    update();
}

qreal QtMaterialSnackbar::backgroundOpacity() const
{
    Q_D(const QtMaterialSnackbar);

    return d->bgOpacity;
}

void QtMaterialSnackbar::setTextColor(const QColor &color)
{
    Q_D(QtMaterialSnackbar);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialSnackbar::textColor() const
{
    Q_D(const QtMaterialSnackbar);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void QtMaterialSnackbar::setFontSize(qreal size)
{
    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal QtMaterialSnackbar::fontSize() const
{
    return font().pointSizeF();
}

void QtMaterialSnackbar::setBoxWidth(int width)
{
    Q_D(QtMaterialSnackbar);

    d->boxWidth = width;
    update();
}

int QtMaterialSnackbar::boxWidth() const
{
    Q_D(const QtMaterialSnackbar);

    return d->boxWidth;
}

void QtMaterialSnackbar::setClickToDismissMode(bool value)
{
    Q_D(QtMaterialSnackbar);

    d->clickDismiss = value;
}

bool QtMaterialSnackbar::clickToDismissMode() const
{
    Q_D(const QtMaterialSnackbar);

    return d->clickDismiss;
}

void QtMaterialSnackbar::addMessage(const QString &message)
{
    Q_D(QtMaterialSnackbar);

    d->messages.push_back(message);
    d->stateMachine->postEvent(new QtMaterialStateTransitionEvent(SnackbarShowTransition));
    raise();
}

void QtMaterialSnackbar::addInstantMessage(const QString &message)
{
    Q_D(QtMaterialSnackbar);

    if (d->messages.isEmpty()) {
        d->messages.push_back(message);
    } else {
        d->messages.insert(1, message);
    }

    d->stateMachine->progress();
}

void QtMaterialSnackbar::dequeue()
{
    Q_D(QtMaterialSnackbar);

    if (d->messages.isEmpty()) {
        return;
    }

    d->messages.removeFirst();

    if (!d->messages.isEmpty()) {
        d->stateMachine->postEvent(new QtMaterialStateTransitionEvent(SnackbarNextTransition));
    } else {
        d->stateMachine->postEvent(new QtMaterialStateTransitionEvent(SnackbarWaitTransition));
    }
}

void QtMaterialSnackbar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialSnackbar);

    if (d->messages.isEmpty()) {
        return;
    }

    QString message = d->messages.first();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());
    painter.setBrush(brush);
    painter.setOpacity(d->bgOpacity);

    QRect r(0, 0, d->boxWidth, 40);

    painter.setPen(Qt::white);
    QRect br = painter.boundingRect(r, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, message);

    painter.setPen(Qt::NoPen);
    r = br.united(r).adjusted(-10, -10, 10, 20);

    const qreal s = 1-d->stateMachine->offset();

    painter.translate((width()-(r.width()-20))/2,
                      height()+10-s*(r.height()));

    br.moveCenter(r.center());
    painter.drawRoundedRect(r.adjusted(0, 0, 0, 3), 3, 3);
    painter.setPen(textColor());
    painter.drawText(br, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, message);
}
