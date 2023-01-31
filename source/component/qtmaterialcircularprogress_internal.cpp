#include "qtmaterialcircularprogress_internal.h"

/*!
 *  \class QtMaterialCircularProgressDelegate
 *  \internal
 */

QtMaterialCircularProgressDelegate::QtMaterialCircularProgressDelegate(QtMaterialCircularProgress *parent)
    : QObject(parent),
      m_progress(parent),
      m_dashOffset(0),
      m_dashLength(89),
      m_angle(0)
{
    Q_ASSERT(parent);
}

QtMaterialCircularProgressDelegate::~QtMaterialCircularProgressDelegate()
{
}
