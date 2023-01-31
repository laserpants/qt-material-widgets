#ifndef QTMATERIALPROGRESS_INTERNAL_H
#define QTMATERIALPROGRESS_INTERNAL_H

#include <QObject>
#include "qtmaterialprogress.h"

class QtMaterialProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
    QtMaterialProgressDelegate(QtMaterialProgress *parent);
    ~QtMaterialProgressDelegate();

    inline void setOffset(qreal offset);
    inline qreal offset() const;

private:
    Q_DISABLE_COPY(QtMaterialProgressDelegate)

    QtMaterialProgress *const m_progress;
    qreal                     m_offset;
};

inline void QtMaterialProgressDelegate::setOffset(qreal offset)
{
    m_offset = offset;
    m_progress->update();
}

inline qreal QtMaterialProgressDelegate::offset() const
{
    return m_offset;
}

#endif // QTMATERIALPROGRESS_INTERNAL_H
