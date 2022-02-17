#ifndef QTMATERIALCIRCULARPROGRESS_INTERNAL_H
#define QTMATERIALCIRCULARPROGRESS_INTERNAL_H

#include <QObject>
#include "qtmaterialcircularprogress.h"
namespace md
{

class CircularProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
    Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
    Q_PROPERTY(int angle WRITE setAngle READ angle)

public:
    CircularProgressDelegate(CircularProgress *parent);
    ~CircularProgressDelegate();

    inline void setDashOffset(qreal offset);
    inline qreal dashOffset() const;

    inline void setDashLength(qreal length);
    inline qreal dashLength() const;

    inline void setAngle(int angle);
    inline int angle() const;

private:
    Q_DISABLE_COPY(CircularProgressDelegate)

    CircularProgress *const m_progress;
    qreal                             m_dashOffset;
    qreal                             m_dashLength;
    int                               m_angle;
};

inline void CircularProgressDelegate::setDashOffset(qreal offset)
{
    m_dashOffset = offset;
    m_progress->update();
}

inline qreal CircularProgressDelegate::dashOffset() const
{
    return m_dashOffset;
}

inline void CircularProgressDelegate::setDashLength(qreal length)
{
    m_dashLength = length;
    m_progress->update();
}

inline qreal CircularProgressDelegate::dashLength() const
{
    return m_dashLength;
}

inline void CircularProgressDelegate::setAngle(int angle)
{
    m_angle = angle;
    m_progress->update();
}

inline int CircularProgressDelegate::angle() const
{
    return m_angle;
}

}

#endif // QTMATERIALCIRCULARPROGRESS_INTERNAL_H
