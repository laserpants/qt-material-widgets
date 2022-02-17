#ifndef QTMATERIALSCROLLBAR_INTERNAL_H
#define QTMATERIALSCROLLBAR_INTERNAL_H

#include <QStateMachine>
#include "qtmaterialscrollbar.h"
namespace md
{

class ScrollBarStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    ScrollBarStateMachine(ScrollBar *parent);
    ~ScrollBarStateMachine();

    inline void setOpacity(qreal opacity);
    inline qreal opacity() const;

private:
    Q_DISABLE_COPY(ScrollBarStateMachine)

    ScrollBar *const m_scrollBar;
    QState              *const m_focusState;
    QState              *const m_blurState;
    qreal                m_opacity;
};

inline void ScrollBarStateMachine::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    m_scrollBar->update();
}

inline qreal ScrollBarStateMachine::opacity() const
{
    return m_opacity;
}
}
#endif // QTMATERIALSCROLLBAR_INTERNAL_H
