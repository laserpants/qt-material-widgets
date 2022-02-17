#include "qtmaterialtabs.h"

namespace md
{

/*!
 *  \TabsPrivate
 *  \internal
 */

TabsPrivate::TabsPrivate(Tabs *q)
    : q_ptr(q)
{
}

TabsPrivate::~TabsPrivate()
{
}

void TabsPrivate::TabsPrivate::init()
{
    Q_Q(Tabs);

    inkBar         = new TabsInkBar(q);
    tabLayout      = new QHBoxLayout;
    rippleStyle    = Material::CenteredRipple;
    tab            = -1;
    showHalo       = true;
    useThemeColors = true;

    q->setLayout(tabLayout);
    q->setStyle(&Style::instance());

    tabLayout->setSpacing(0);

//    tabLayout->setMargin(0); // FIXME: throwing an error
}

/*!
 *  \QtMaterialTabs
 */

Tabs::Tabs(QWidget *parent)
    : QWidget(parent),
      d_ptr(new TabsPrivate(this))
{
    d_func()->init();
}

Tabs::~Tabs()
{
}

void Tabs::setUseThemeColors(bool value)
{
    Q_D(Tabs);

    d->useThemeColors = value;
}

bool Tabs::useThemeColors() const
{
    Q_D(const Tabs);

    return d->useThemeColors;
}

void Tabs::setHaloVisible(bool value)
{
    Q_D(Tabs);

    d->showHalo = value;
    updateTabs();
}

bool Tabs::isHaloVisible() const
{
    Q_D(const Tabs);

    return d->showHalo;
}

void Tabs::setRippleStyle(Material::RippleStyle style)
{
    Q_D(Tabs);

    d->rippleStyle = style;
    updateTabs();
}

Material::RippleStyle Tabs::rippleStyle() const
{
    Q_D(const Tabs);

    return d->rippleStyle;
}

void Tabs::setInkColor(const QColor &color)
{
    Q_D(Tabs);

    d->inkColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->inkBar->update();
    update();
}

QColor Tabs::inkColor() const
{
    Q_D(const Tabs);

    if (d->useThemeColors || !d->inkColor.isValid()) {
        return Style::instance().themeColor("accent1");
    } else {
        return d->inkColor;
    }
}

void Tabs::setBackgroundColor(const QColor &color)
{
    Q_D(Tabs);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    updateTabs();
    update();
}

QColor Tabs::backgroundColor() const
{
    Q_D(const Tabs);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

void Tabs::setTextColor(const QColor &color)
{
    Q_D(Tabs);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    updateTabs();
    update();
}

QColor Tabs::textColor() const
{
    Q_D(const Tabs);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return Style::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void Tabs::setCurrentTab(Tab *tab)
{
    Q_D(Tabs);

    setCurrentTab(d->tabLayout->indexOf(tab));
}

void Tabs::setCurrentTab(int index)
{
    Q_D(Tabs);

    setTabActive(d->tab, false);
    d->tab = index;
    setTabActive(index, true);
    d->inkBar->animate();

    emit currentChanged(index);
}

void Tabs::addTab(const QString &text, const QIcon &icon)
{
    Q_D(Tabs);

    Tab *tab = new Tab(this);
    tab->setText(text);
    tab->setHaloVisible(isHaloVisible());
    tab->setRippleStyle(rippleStyle());

    if (!icon.isNull()) {
        tab->setIcon(icon);
        tab->setIconSize(QSize(22, 22));
    }

    d->tabLayout->addWidget(tab);

    if (-1 == d->tab) {
        d->tab = 0;
        d->inkBar->refreshGeometry();
        d->inkBar->raise();
        tab->setActive(true);
    }
}

int Tabs::currentIndex() const
{
    Q_D(const Tabs);

    return d->tab;
}

void Tabs::setTabActive(int index, bool active)
{
    Q_D(Tabs);

    Tab *tab;

    if (index > -1) {
        tab = static_cast<Tab *>(d->tabLayout->itemAt(index)->widget());
        if (tab) {
            tab->setActive(active);
        }
    }
}

void Tabs::updateTabs()
{
    Q_D(Tabs);

    Tab *tab;
    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if ((tab = static_cast<Tab *>(item->widget()))) {
            tab->setRippleStyle(d->rippleStyle);
            tab->setHaloVisible(d->showHalo);
            tab->setBackgroundColor(backgroundColor());
            tab->setForegroundColor(textColor());
        }
    }
}
}
