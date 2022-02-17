#ifndef QTMATERIALCHECKABLE_INTERNAL_H
#define QTMATERIALCHECKABLE_INTERNAL_H

#include <QtWidgets/QWidget>
#include <QColor>
#include <QIcon>

namespace md
{
class Checkable;

class CheckableIcon : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(qreal iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    CheckableIcon(const QIcon &icon, Checkable *parent);
    ~CheckableIcon();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    inline void setIcon(const QIcon &icon);
    inline QIcon icon() const;

    inline void setColor(const QColor &color);
    inline QColor color() const;

    inline void setIconSize(qreal size);
    inline qreal iconSize() const;

    inline void setOpacity(qreal opacity);
    inline qreal opacity() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(CheckableIcon)

    Checkable *const m_checkable;
    QColor                     m_color;
    QIcon                      m_icon;
    qreal                      m_iconSize;
    qreal                      m_opacity;
};

inline void CheckableIcon::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
}

inline QIcon CheckableIcon::icon() const
{
    return m_icon;
}

inline void CheckableIcon::setColor(const QColor &color)
{
    m_color = color;
    update();
}

inline QColor CheckableIcon::color() const
{
    return m_color;
}

inline void CheckableIcon::setIconSize(qreal size)
{
    m_iconSize = size;
    update();
}

inline qreal CheckableIcon::iconSize() const
{
    return m_iconSize;
}

inline void CheckableIcon::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    update();
}

inline qreal CheckableIcon::opacity() const
{
    return m_opacity;
}
}

#endif // QTMATERIALCHECKABLE_INTERNAL_H
