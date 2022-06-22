#include "textfield.h"
#include "textfield_p.h"
#include <QtWidgets/QApplication>
#include <QPainter>
#include "textfield_internal.h"
#include "lib/style.h"
#include <QDebug>
namespace md
{

/*!
 *  \class QtMaterialTextFieldPrivate
 *  \internal
 */

TextFieldPrivate::TextFieldPrivate(TextField *q)
    : q_ptr(q)
{
}

TextFieldPrivate::~TextFieldPrivate()
{
}

void TextFieldPrivate::init()
{
    Q_Q(TextField);

    stateMachine   = new TextFieldStateMachine(q);
    label          = 0;
    labelFontSize  = 9.5;
    showLabel      = false;
    showInputLine  = true;
    useThemeColors = true;

    q->setFrame(false);
    q->setStyle(&Style::instance());
    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setTextMargins(0, 2, 0, 4);

    q->setFont(QFont("Roboto", 11, QFont::Normal));

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class QtMaterialTextField
 */

TextField::TextField(QWidget *parent)
    : QLineEdit(parent),
      d_ptr(new TextFieldPrivate(this))
{
    d_func()->init();
}

TextField::~TextField()
{
}

void TextField::setUseThemeColors(bool value)
{
    Q_D(TextField);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool TextField::useThemeColors() const
{
    Q_D(const TextField);

    return d->useThemeColors;
}

void TextField::setShowLabel(bool value)
{
    Q_D(TextField);

    if (d->showLabel == value) {
        return;
    }

    d->showLabel = value;

    if (!d->label && value) {
        d->label = new TextFieldLabel(this);
        d->stateMachine->setLabel(d->label);
    }

    if (value) {
        setContentsMargins(0, 23, 0, 0);
    } else {
        setContentsMargins(0, 0, 0, 0);
    }
}

bool TextField::hasLabel() const
{
    Q_D(const TextField);

    return d->showLabel;
}

void TextField::setLabelFontSize(qreal size)
{
    Q_D(TextField);

    d->labelFontSize = size;

    if (d->label)
    {
        QFont font(d->label->font());
        font.setPointSizeF(size);
        d->label->setFont(font);
        d->label->update();
    }
}

qreal TextField::labelFontSize() const
{
    Q_D(const TextField);

    return d->labelFontSize;
}

void TextField::setLabel(const QString &label)
{
    Q_D(TextField);

    d->labelString = label;
    setShowLabel(true);
    d->label->update();
}

QString TextField::label() const
{
    Q_D(const TextField);

    return d->labelString;
}

void TextField::setTextColor(const QColor &color)
{
    Q_D(TextField);

    d->textColor = color;
    setStyleSheet(QString("QLineEdit { color: %1; }").arg(color.name()));

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor TextField::textColor() const
{
    Q_D(const TextField);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void TextField::setLabelColor(const QColor &color)
{
    Q_D(TextField);

    d->labelColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor TextField::labelColor() const
{
    Q_D(const TextField);

    if (d->useThemeColors || !d->labelColor.isValid()) {
        return Style::instance().themeColor("accent3");
    } else {
        return d->labelColor;
    }
}

void TextField::setInkColor(const QColor &color)
{
    Q_D(TextField);

    d->inkColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor TextField::inkColor() const
{
    Q_D(const TextField);

    if (d->useThemeColors || !d->inkColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->inkColor;
    }
}

void TextField::setInputLineColor(const QColor &color)
{
    Q_D(TextField);

    d->inputLineColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor TextField::inputLineColor() const
{
    Q_D(const TextField);

    if (d->useThemeColors || !d->inputLineColor.isValid()) {
        return Style::instance().themeColor("border");
    } else {
        return d->inputLineColor;
    }
}

void TextField::setShowInputLine(bool value)
{
    Q_D(TextField);

    if (d->showInputLine == value) {
        return;
    }

    d->showInputLine = value;
    update();
}

bool TextField::hasInputLine() const
{
    Q_D(const TextField);

    return d->showInputLine;
}

TextField::TextField(TextFieldPrivate &d, QWidget *parent)
    : QLineEdit(parent),
      d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
bool TextField::event(QEvent *event)
{
    Q_D(TextField);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move: {
        if (d->label) {
            d->label->setGeometry(rect());
        }
    }
    default:
        break;
    }
    return QLineEdit::event(event);
}

/*!
 *  \reimp
 */
void TextField::paintEvent(QPaintEvent *event)
{
    Q_D(TextField);

    QLineEdit::paintEvent(event);

    QPainter painter(this);

    const qreal progress = d->stateMachine->progress();

    if (text().isEmpty() && progress < 1)
    {
        painter.setOpacity(1-progress);
        painter.fillRect(rect(), parentWidget()->palette().color(backgroundRole()));
    }

    const int y = height()-1;
    const int wd = width()-5;

    if (d->showInputLine)
    {
        QPen pen;
        pen.setWidth(1);
        pen.setColor(inputLineColor());

        if (!isEnabled()) 
            pen.setStyle(Qt::DashLine);

        painter.setPen(pen);
        painter.setOpacity(1);
        painter.drawLine(QLineF(2.5, y, wd, y));

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(inkColor());

        if (progress > 0)
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(brush);
            const int w = (1-progress)*static_cast<qreal>(wd/2);
            painter.drawRect(w+2.5, height()-2, wd-w*2, 2);
        }
    }
}
}
