#ifndef QTMATERIALTABS_H
#define QTMATERIALTABS_H

#include <QtWidgets/QWidget>
#include <QIcon>
#include "lib/qtmaterialtheme.h"

class QtMaterialTabsPrivate;
class QtMaterialTab;

class QtMaterialTabs : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialTabs(QWidget *parent = 0);
    ~QtMaterialTabs();

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

    void setCurrentTab(QtMaterialTab *tab);
    void setCurrentTab(int index);

    int currentIndex() const;

signals:
    void currentChanged(int);

protected:
    void setTabActive(int index, bool active = true);
    void updateTabs();

    const QScopedPointer<QtMaterialTabsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTabs)
    Q_DECLARE_PRIVATE(QtMaterialTabs)
};

#endif // QTMATERIALTABS_H
