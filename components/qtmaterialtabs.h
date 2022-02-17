#ifndef QTMATERIALTABS_H
#define QTMATERIALTABS_H

#include <QtWidgets/QWidget>
#include <QIcon>
#include "lib/qtmaterialtheme.h"
namespace md
{

class TabsPrivate;
class Tab;

class Tabs : public QWidget
{
    Q_OBJECT

public:
    explicit Tabs(QWidget *parent = 0);
    ~Tabs();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setHaloVisible(bool value);
    bool isHaloVisible() const;

    void setRippleStyle(Material::RippleStyle style);
    Material::RippleStyle rippleStyle() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void addTab(const QString &text, const QIcon &icon = QIcon());

    void setCurrentTab(Tab *tab);
    void setCurrentTab(int index);

    int currentIndex() const;

signals:
    void currentChanged(int);

protected:
    void setTabActive(int index, bool active = true);
    void updateTabs();

    const QScopedPointer<TabsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Tabs)
    Q_DECLARE_PRIVATE(Tabs)
};
}
#endif // QTMATERIALTABS_H
