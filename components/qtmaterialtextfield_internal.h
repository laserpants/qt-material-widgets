#ifndef QTMATERIALTEXTFIELD_INTERNAL_H
#define QTMATERIALTEXTFIELD_INTERNAL_H

#include <QtWidgets/QWidget>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QEventTransition>
#include <QPainter>

#include "qtmaterialtextfield.h"

namespace md
{

class TextFieldLabel;

class TextFieldStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal progress WRITE setProgress READ progress)

public:
    TextFieldStateMachine(TextField *parent);
    ~TextFieldStateMachine();

    void setLabel(TextFieldLabel *label);

    inline void setProgress(qreal progress);
    inline qreal progress() const;

public slots:
    void setupProperties();

private:
    Q_DISABLE_COPY(TextFieldStateMachine)

    TextField *const m_textField;
    QState              *const m_normalState;
    QState              *const m_focusedState;
    TextFieldLabel  *m_label;
    QPropertyAnimation        *m_offsetAnimation;
    QPropertyAnimation        *m_colorAnimation;
    qreal                      m_progress;
};

inline void TextFieldStateMachine::setProgress(qreal progress)
{
    m_progress = progress;
    m_textField->update();
}

inline qreal TextFieldStateMachine::progress() const
{
    return m_progress;
}

class TextFieldLabel : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal scale WRITE setScale READ scale)
    Q_PROPERTY(QPointF offset WRITE setOffset READ offset)
    Q_PROPERTY(QColor color WRITE setColor READ color)

public:
    TextFieldLabel(TextField *parent);
    ~TextFieldLabel();

    inline void setScale(qreal scale);
    inline qreal scale() const;

    inline void setOffset(const QPointF &pos);
    inline QPointF offset() const;

    inline void setColor(const QColor &color);
    inline QColor color() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(TextFieldLabel)

    TextField *const m_textField;
    qreal                      m_scale;
    qreal                      m_posX;
    qreal                      m_posY;
    QColor                     m_color;
};

inline void TextFieldLabel::setScale(qreal scale)
{
    m_scale = scale;
    update();
}

inline qreal TextFieldLabel::scale() const
{
    return m_scale;
}

inline void TextFieldLabel::setOffset(const QPointF &pos)
{
    m_posX = pos.x();
    m_posY = pos.y();
    update();
}

inline QPointF TextFieldLabel::offset() const
{
    return QPointF(m_posX, m_posY);
}

inline void TextFieldLabel::setColor(const QColor &color)
{
    m_color = color;
    update();
}

inline QColor TextFieldLabel::color() const
{
    return m_color;
}
}
#endif // QTMATERIALTEXTFIELD_INTERNAL_H
