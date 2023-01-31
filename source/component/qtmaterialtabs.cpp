#include "qtmaterialtabs.h"
#include "qtmaterialtabs_p.h"
#include <QtWidgets/QHBoxLayout>
#include "qtmaterialtabs_internal.h"
#include "lib/qtmaterialstyle.h"

/*!
 *  \QtMaterialTabsPrivate
 *  \internal
 */

QtMaterialTabsPrivate::QtMaterialTabsPrivate(QtMaterialTabs *q)
    : q_ptr(q)
{
}

QtMaterialTabsPrivate::~QtMaterialTabsPrivate()
{
}

void QtMaterialTabsPrivate::QtMaterialTabsPrivate::init()
{
    Q_Q(QtMaterialTabs);

    inkBar         = new QtMaterialTabsInkBar(q);
    tabLayout      = new QHBoxLayout;
    rippleStyle    = Material::CenteredRipple;
    tab            = -1;
    showHalo       = true;
    useThemeColors = true;

    q->setLayout(tabLayout);
    q->setStyle(&QtMaterialStyle::instance());

    tabLayout->setSpacing(0);
    tabLayout->setMargin(0);
}

/*!
 *  \QtMaterialTabs
 */

QtMaterialTabs::QtMaterialTabs(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialTabsPrivate(this))
{
    d_func()->init();
}

QtMaterialTabs::~QtMaterialTabs()
{
}

void QtMaterialTabs::setUseThemeColors(bool value)
{
    Q_D(QtMaterialTabs);

    d->useThemeColors = value;
}

bool QtMaterialTabs::useThemeColors() const
{
    Q_D(const QtMaterialTabs);

    return d->useThemeColors;
}

void QtMaterialTabs::setHaloVisible(bool value)
{
    Q_D(QtMaterialTabs);

    d->showHalo = value;
    updateTabs();
}

bool QtMaterialTabs::isHaloVisible() const
{
    Q_D(const QtMaterialTabs);

    return d->showHalo;
}

void QtMaterialTabs::setRippleStyle(Material::RippleStyle style)
{
    Q_D(QtMaterialTabs);

    d->rippleStyle = style;
    updateTabs();
}

Material::RippleStyle QtMaterialTabs::rippleStyle() const
{
    Q_D(const QtMaterialTabs);

    return d->rippleStyle;
}

void QtMaterialTabs::setInkColor(const QColor &color)
{
    Q_D(QtMaterialTabs);

    d->inkColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->inkBar->update();
    update();
}

QColor QtMaterialTabs::inkColor() const
{
    Q_D(const QtMaterialTabs);

    if (d->useThemeColors || !d->inkColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent1");
    } else {
        return d->inkColor;
    }
}

void QtMaterialTabs::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialTabs);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    updateTabs();
    update();
}

QColor QtMaterialTabs::backgroundColor() const
{
    Q_D(const QtMaterialTabs);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

void QtMaterialTabs::setTextColor(const QColor &color)
{
    Q_D(QtMaterialTabs);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    updateTabs();
    update();
}

QColor QtMaterialTabs::textColor() const
{
    Q_D(const QtMaterialTabs);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void QtMaterialTabs::setCurrentTab(QtMaterialTab *tab)
{
    Q_D(QtMaterialTabs);

    setCurrentTab(d->tabLayout->indexOf(tab));
}

void QtMaterialTabs::setCurrentTab(int index)
{
    Q_D(QtMaterialTabs);

    setTabActive(d->tab, false);
    d->tab = index;
    setTabActive(index, true);
    d->inkBar->animate();

    emit currentChanged(index);
}

void QtMaterialTabs::addTab(const QString &text, const QIcon &icon)
{
    Q_D(QtMaterialTabs);

    QtMaterialTab *tab = new QtMaterialTab(this);
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

int QtMaterialTabs::currentIndex() const
{
    Q_D(const QtMaterialTabs);

    return d->tab;
}

void QtMaterialTabs::setTabActive(int index, bool active)
{
    Q_D(QtMaterialTabs);

    QtMaterialTab *tab;

    if (index > -1) {
        tab = static_cast<QtMaterialTab *>(d->tabLayout->itemAt(index)->widget());
        if (tab) {
            tab->setActive(active);
        }
    }
}

void QtMaterialTabs::updateTabs()
{
    Q_D(QtMaterialTabs);

    QtMaterialTab *tab;
    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if ((tab = static_cast<QtMaterialTab *>(item->widget()))) {
            tab->setRippleStyle(d->rippleStyle);
            tab->setHaloVisible(d->showHalo);
            tab->setBackgroundColor(backgroundColor());
            tab->setForegroundColor(textColor());
        }
    }
}
