#include "qtmaterialdialog_internal.h"
#include <QPainter>
#include <QPixmap>
#include <QEvent>
#include <QtWidgets/QStackedLayout>
#include "qtmaterialdialog.h"
namespace md
{

/*!
 *  \class QtMaterialDialogProxy
 *  \internal
 */

DialogProxy::DialogProxy(
        DialogWindow *source,
        QStackedLayout         *layout,
        Dialog       *dialog,
        QWidget                *parent)
    : QWidget(parent),
      m_source(source),
      m_layout(layout),
      m_dialog(dialog),
      m_opacity(0),
      m_mode(Transparent)
{
}

DialogProxy::~DialogProxy()
{
}

void DialogProxy::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    m_mode = SemiTransparent;
    update();
    m_dialog->update();
}


void DialogProxy::makeOpaque()
{
    m_dialog->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    m_layout->setCurrentIndex(0);
    m_opacity = 1.0;
    m_mode = Opaque;
    update();
}

void DialogProxy::makeTransparent()
{
    m_opacity = 0.0;
    m_mode = Transparent;
    update();
}

QSize DialogProxy::sizeHint() const
{
    return m_source->sizeHint();
}

bool DialogProxy::event(QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type) {
        m_source->setGeometry(geometry());
    }
    return QWidget::event(event);
}

void DialogProxy::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    if (Transparent == m_mode) {
        return;
    } else if (Opaque != m_mode) {
        painter.setOpacity(m_opacity);
    }
    QPixmap pm = m_source->grab(m_source->rect());
    painter.drawPixmap(0, 0, pm);
}

/*!
 *  \class QtMaterialDialogWindow
 *  \internal
 */

DialogWindow::DialogWindow(
        Dialog *dialog,
        QWidget          *parent)
    : QWidget(parent),
      m_dialog(dialog)
{
}

DialogWindow::~DialogWindow()
{
}

void DialogWindow::setOffset(int offset)
{
    QMargins margins = m_dialog->layout()->contentsMargins();
    margins.setBottom(offset);
    m_dialog->layout()->setContentsMargins(margins);
}

int DialogWindow::offset() const
{
    return m_dialog->layout()->contentsMargins().bottom();
}

void DialogWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawRect(rect());
}

}
