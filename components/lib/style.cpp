#include "lib/style.h"
#include "lib/theme.h"

namespace md
{
/*!
 *  \class StylePrivate
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

    QFontDatabase::addApplicationFont(QDir::currentPath()+"/../fonts/roboto_regular");
    QFontDatabase::addApplicationFont(QDir::currentPath()+"/../fonts/roboto_medium");
    QFontDatabase::addApplicationFont(QDir::currentPath()+"/../fonts/roboto_bold");

    q->setTheme(new Theme);
}

/*!
 *  \class Style
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
