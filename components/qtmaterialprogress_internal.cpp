#include "qtmaterialprogress_internal.h"

/*!
 *  \class QtMaterialProgressDelegate
 *  \internal
 */

ProgressBarDelegate::ProgressBarDelegate(ProgressBar *parent)
    : QObject(parent),
      m_progress(parent),
      m_offset(0)
{
    Q_ASSERT(parent);
}

ProgressBarDelegate::~ProgressBarDelegate()
{
}
