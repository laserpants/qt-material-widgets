#ifndef QTMATERIALPROGRESS_INTERNAL_H
#define QTMATERIALPROGRESS_INTERNAL_H

#include <QObject>
#include "qtmaterialprogress.h"

namespace md
{

class ProgressBarDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
    ProgressBarDelegate(ProgressBar *parent);
    ~ProgressBarDelegate();

    inline void setOffset(qreal offset);
    inline qreal offset() const;

private:
    Q_DISABLE_COPY(ProgressBarDelegate)

    ProgressBar *const m_progress;
    qreal                     m_offset;
};

inline void ProgressBarDelegate::setOffset(qreal offset)
{
    m_offset = offset;
    m_progress->update();
}

inline qreal ProgressBarDelegate::offset() const
{
    return m_offset;
}
}
#endif // QTMATERIALPROGRESS_INTERNAL_H
