#ifndef QTMATERIALCIRCULARPROGRESS_INTERNAL_H
#define QTMATERIALCIRCULARPROGRESS_INTERNAL_H

#include <QObject>
#include "qtmaterialcircularprogress.h"

class QtMaterialCircularProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
    Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
    Q_PROPERTY(int angle WRITE setAngle READ angle)

public:
    QtMaterialCircularProgressDelegate(QtMaterialCircularProgress *parent);
    ~QtMaterialCircularProgressDelegate();

    inline void setDashOffset(qreal offset);
    inline qreal dashOffset() const;

    inline void setDashLength(qreal length);
    inline qreal dashLength() const;

    inline void setAngle(int angle);
    inline int angle() const;

private:
    Q_DISABLE_COPY(QtMaterialCircularProgressDelegate)

    QtMaterialCircularProgress *const m_progress;
    qreal                             m_dashOffset;
    qreal                             m_dashLength;
    int                               m_angle;
};

inline void QtMaterialCircularProgressDelegate::setDashOffset(qreal offset)
{
    m_dashOffset = offset;
    m_progress->update();
}

inline qreal QtMaterialCircularProgressDelegate::dashOffset() const
{
    return m_dashOffset;
}

inline void QtMaterialCircularProgressDelegate::setDashLength(qreal length)
{
    m_dashLength = length;
    m_progress->update();
}

inline qreal QtMaterialCircularProgressDelegate::dashLength() const
{
    return m_dashLength;
}

inline void QtMaterialCircularProgressDelegate::setAngle(int angle)
{
    m_angle = angle;
    m_progress->update();
}

inline int QtMaterialCircularProgressDelegate::angle() const
{
    return m_angle;
}

#endif // QTMATERIALCIRCULARPROGRESS_INTERNAL_H
