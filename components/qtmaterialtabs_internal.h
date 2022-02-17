#ifndef QTMATERIALTABS_INTERNAL_H
#define QTMATERIALTABS_INTERNAL_H

#include <QPainter>
#include <QPropertyAnimation>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLayoutItem>
#include <QEvent>
#include <QDebug>

#include "qtmaterialtabs.h"
#include "lib/qtmaterialoverlaywidget.h"
#include "qtmaterialflatbutton.h"

namespace md
{

class Tabs;

class TabsInkBar : public OverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

public:
    TabsInkBar(Tabs *parent);
    ~TabsInkBar();

    inline void setTweenValue(qreal value);
    inline qreal tweenValue() const;

    void refreshGeometry();
    void animate();

protected:
    bool eventFilter(QObject *obj, QEvent *event)  Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(TabsInkBar)

    Tabs     *const m_tabs;
    QPropertyAnimation *const m_animation;
    QRect                     m_geometry;
    QRect                     m_previousGeometry;
    qreal                     m_tween;
};

inline void TabsInkBar::setTweenValue(qreal value)
{
    m_tween = value;
    refreshGeometry();
}

inline qreal TabsInkBar::tweenValue() const
{
    return m_tween;
}

class Tab : public FlatButton
{
    Q_OBJECT

public:
    explicit Tab(Tabs *parent);
    ~Tab();

    inline void setActive(bool state);
    inline bool isActive() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected slots:
    void activateTab();

protected:
    void paintForeground(QPainter *painter) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(Tab)

    Tabs *const m_tabs;
    bool                  m_active;
};

inline void Tab::setActive(bool state)
{
    m_active = state;
    update();
}

inline bool Tab::isActive() const
{
    return m_active;
}
}
#endif // QTMATERIALTABS_INTERNAL_H
