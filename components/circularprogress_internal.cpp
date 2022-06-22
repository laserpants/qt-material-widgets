#include "circularprogress_internal.h"

namespace md
{

/*!
 *  \class QtMaterialCircularProgressDelegate
 *  \internal
 */

CircularProgressDelegate::CircularProgressDelegate(CircularProgress *parent)
    : QObject(parent),
      m_progress(parent),
      m_dashOffset(0),
      m_dashLength(89),
      m_angle(0)
{
    Q_ASSERT(parent);
}

CircularProgressDelegate::~CircularProgressDelegate()
{
}

}
