#include "lib/qtmaterialstyle.h"
#include <QFontDatabase>
#include "lib/qtmaterialtheme.h"

namespace md
{
/*!
 *  \class QtMaterialStylePrivate
 *  \internal
 */

StylePrivate::StylePrivate(Style *q)
    : q_ptr(q)
{
}

StylePrivate::~StylePrivate()
{
}

void StylePrivate::init()
{
    Q_Q(Style);

    QFontDatabase::addApplicationFont(":/fonts/roboto_regular");
    QFontDatabase::addApplicationFont(":/fonts/roboto_medium");
    QFontDatabase::addApplicationFont(":/fonts/roboto_bold");

    q->setTheme(new Theme);
}

/*!
 *  \class QtMaterialStyle
 *  \internal
 */

void Style::setTheme(Theme *theme)
{
    Q_D(Style);

    d->theme = theme;
    theme->setParent(this);
}

QColor Style::themeColor(const QString &key) const
{
    Q_D(const Style);

    Q_ASSERT(d->theme);

    return d->theme->getColor(key);
}

Style::Style()
    : QCommonStyle(),
      d_ptr(new StylePrivate(this))
{
    d_func()->init();
}

}
