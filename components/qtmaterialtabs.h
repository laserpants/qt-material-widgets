#ifndef QTMATERIALTABS_H
#define QTMATERIALTABS_H

#include <QtWidgets/QWidget>
#include <QIcon>
#include "lib/qtmaterialtheme.h"
#include "qtmaterial_global.h"

class QtMaterialTabsPrivate;
class QtMaterialTab;

class QT_MATERIAL_EXPORT QtMaterialTabs : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool haloVisible WRITE setHaloVisible READ isHaloVisible)
    Q_PROPERTY(MaterialConst::RippleStyle rippleStyle WRITE setRippleStyle READ rippleStyle)
    Q_PROPERTY(QColor inkColor WRITE setInkColor READ inkColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)

public:
    explicit QtMaterialTabs(QWidget *parent = 0);
    ~QtMaterialTabs();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setHaloVisible(bool value);
    bool isHaloVisible() const;

    void setRippleStyle(MaterialConst::RippleStyle style);
    MaterialConst::RippleStyle rippleStyle() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void insertTab(int index, const QString &text, const QIcon &icon = QIcon());
    void addTab(const QString &text, const QIcon &icon = QIcon());
    void removeTab(int index);
    int count() const;

    void setCurrentTab(QtMaterialTab *tab);
    void setCurrentTab(int index);
    void setTabText(int index, const QString &text);

    int currentIndex() const;

Q_SIGNALS:
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
