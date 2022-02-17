#include "qtmaterialsnackbar.h"
#include "qtmaterialsnackbar_p.h"
#include <QtWidgets/QApplication>
#include <QPainter>
#include "qtmaterialsnackbar_internal.h"
#include "lib/qtmaterialstyle.h"
#include "lib/qtmaterialstatetransition.h"
#include <QDebug>
namespace md
{

/*!
 *  \class QtMaterialSnackbarPrivate
 *  \internal
 */

SnackBarPrivate::SnackBarPrivate(SnackBar *q)
    : q_ptr(q)
{
}

SnackBarPrivate::~SnackBarPrivate()
{
}

void SnackBarPrivate::init()
{
    Q_Q(SnackBar);

    stateMachine   = new SnackBarStateMachine(q);
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

SnackBar::SnackBar(QWidget *parent)
    : OverlayWidget(parent),
      d_ptr(new SnackBarPrivate(this))
{
    d_func()->init();
}

SnackBar::~SnackBar()
{
}

void SnackBar::setAutoHideDuration(int duration)
{
    Q_D(SnackBar);

    d->duration = duration;
}

int SnackBar::autoHideDuration() const
{
    Q_D(const SnackBar);

    return d->duration;
}

void SnackBar::setUseThemeColors(bool value)
{
    Q_D(SnackBar);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool SnackBar::useThemeColors() const
{
    Q_D(const SnackBar);

    return d->useThemeColors;
}

void SnackBar::setBackgroundColor(const QColor &color)
{
    Q_D(SnackBar);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor SnackBar::backgroundColor() const
{
    Q_D(const SnackBar);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return Style::instance().themeColor("text");
    } else {
        return d->backgroundColor;
    }
}

void SnackBar::setBackgroundOpacity(qreal opacity)
{
    Q_D(SnackBar);

    d->bgOpacity = opacity;
    update();
}

qreal SnackBar::backgroundOpacity() const
{
    Q_D(const SnackBar);

    return d->bgOpacity;
}

void SnackBar::setTextColor(const QColor &color)
{
    Q_D(SnackBar);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor SnackBar::textColor() const
{
    Q_D(const SnackBar);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void SnackBar::setFontSize(qreal size)
{
    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal SnackBar::fontSize() const
{
    return font().pointSizeF();
}

void SnackBar::setBoxWidth(int width)
{
    Q_D(SnackBar);

    d->boxWidth = width;
    update();
}

int SnackBar::boxWidth() const
{
    Q_D(const SnackBar);

    return d->boxWidth;
}

void SnackBar::setClickToDismissMode(bool value)
{
    Q_D(SnackBar);

    d->clickDismiss = value;
}

bool SnackBar::clickToDismissMode() const
{
    Q_D(const SnackBar);

    return d->clickDismiss;
}

void SnackBar::addMessage(const QString &message)
{
    Q_D(SnackBar);

    d->messages.push_back(message);
    d->stateMachine->postEvent(new StateTransitionEvent(SnackbarShowTransition));
    raise();
}

void SnackBar::addInstantMessage(const QString &message)
{
    Q_D(SnackBar);

    if (d->messages.isEmpty()) {
        d->messages.push_back(message);
    } else {
        d->messages.insert(1, message);
    }

    d->stateMachine->progress();
}

void SnackBar::dequeue()
{
    Q_D(SnackBar);

    if (d->messages.isEmpty()) {
        return;
    }

    d->messages.removeFirst();

    if (!d->messages.isEmpty()) {
        d->stateMachine->postEvent(new StateTransitionEvent(SnackbarNextTransition));
    } else {
        d->stateMachine->postEvent(new StateTransitionEvent(SnackbarWaitTransition));
    }
}

void SnackBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(SnackBar);

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
}
