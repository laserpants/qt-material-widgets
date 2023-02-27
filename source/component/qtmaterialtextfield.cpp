#include "qtmaterialtextfield.h"
#include "qtmaterialtextfield_p.h"
#include <QtWidgets/QApplication>
#include <QPainter>
#include "qtmaterialtextfield_internal.h"
#include "lib/qtmaterialstyle.h"
#include <QDebug>

/*!
 *  \class QtMaterialTextFieldPrivate
 *  \internal
 */

QtMaterialTextFieldPrivate::QtMaterialTextFieldPrivate(QtMaterialTextField *q)
    : q_ptr(q)
{
}

QtMaterialTextFieldPrivate::~QtMaterialTextFieldPrivate()
{
}

void QtMaterialTextFieldPrivate::init()
{
    Q_Q(QtMaterialTextField);

    stateMachine   = new QtMaterialTextFieldStateMachine(q);
    label          = 0;
    labelFontSize  = 9.5;
    showLabel      = false;
    showInputLine  = true;
    useThemeColors = true;

    q->setFrame(false);
    q->setStyle(&QtMaterialStyle::instance());
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

QtMaterialTextField::QtMaterialTextField(QWidget *parent)
    : QLineEdit(parent),
      d_ptr(new QtMaterialTextFieldPrivate(this))
{
    d_func()->init();
}

QtMaterialTextField::~QtMaterialTextField()
{
}

void QtMaterialTextField::setUseThemeColors(bool value)
{
    Q_D(QtMaterialTextField);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool QtMaterialTextField::useThemeColors() const
{
    Q_D(const QtMaterialTextField);

    return d->useThemeColors;
}

void QtMaterialTextField::setShowLabel(bool value)
{
    Q_D(QtMaterialTextField);

    if (d->showLabel == value) {
        return;
    }

    d->showLabel = value;

    if (!d->label && value) {
        d->label = new QtMaterialTextFieldLabel(this);
        d->stateMachine->setLabel(d->label);
    }

    if (value) {
        setContentsMargins(0, 23, 0, 0);
    } else {
        setContentsMargins(0, 0, 0, 0);
    }
}

bool QtMaterialTextField::hasLabel() const
{
    Q_D(const QtMaterialTextField);

    return d->showLabel;
}

void QtMaterialTextField::setLabelFontSize(qreal size)
{
    Q_D(QtMaterialTextField);

    d->labelFontSize = size;

    if (d->label)
    {
        QFont font(d->label->font());
        font.setPointSizeF(size);
        d->label->setFont(font);
        d->label->update();
    }
}

qreal QtMaterialTextField::labelFontSize() const
{
    Q_D(const QtMaterialTextField);

    return d->labelFontSize;
}

void QtMaterialTextField::setLabel(const QString &label)
{
    Q_D(QtMaterialTextField);

    d->labelString = label;
    setShowLabel(true);
    d->label->update();
}

QString QtMaterialTextField::label() const
{
    Q_D(const QtMaterialTextField);

    return d->labelString;
}

void QtMaterialTextField::setTextColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->textColor = color;
    setStyleSheet(QString("QLineEdit { color: %1; }").arg(color.name()));

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::textColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void QtMaterialTextField::setLabelColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->labelColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::labelColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->labelColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent3");
    } else {
        return d->labelColor;
    }
}

void QtMaterialTextField::setInkColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->inkColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::inkColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->inkColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->inkColor;
    }
}

void QtMaterialTextField::setInputLineColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->inputLineColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::inputLineColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->inputLineColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    } else {
        return d->inputLineColor;
    }
}

void QtMaterialTextField::setShowInputLine(bool value)
{
    Q_D(QtMaterialTextField);

    if (d->showInputLine == value) {
        return;
    }

    d->showInputLine = value;
    update();
}

bool QtMaterialTextField::hasInputLine() const
{
    Q_D(const QtMaterialTextField);

    return d->showInputLine;
}

QtMaterialTextField::QtMaterialTextField(QtMaterialTextFieldPrivate &d, QWidget *parent)
    : QLineEdit(parent),
      d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
bool QtMaterialTextField::event(QEvent *event)
{
    Q_D(QtMaterialTextField);

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
void QtMaterialTextField::paintEvent(QPaintEvent *event)
{
    Q_D(QtMaterialTextField);

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
