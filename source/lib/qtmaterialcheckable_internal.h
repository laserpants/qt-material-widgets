#ifndef QTMATERIALCHECKABLE_INTERNAL_H
#define QTMATERIALCHECKABLE_INTERNAL_H

#include <QtWidgets/QWidget>
#include <QColor>
#include <QIcon>

class QtMaterialCheckable;

class QtMaterialCheckableIcon : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(qreal iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    QtMaterialCheckableIcon(const QIcon &icon, QtMaterialCheckable *parent);
    ~QtMaterialCheckableIcon();

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
    Q_DISABLE_COPY(QtMaterialCheckableIcon)

    QtMaterialCheckable *const m_checkable;
    QColor                     m_color;
    QIcon                      m_icon;
    qreal                      m_iconSize;
    qreal                      m_opacity;
};

inline void QtMaterialCheckableIcon::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
}

inline QIcon QtMaterialCheckableIcon::icon() const
{
    return m_icon;
}

inline void QtMaterialCheckableIcon::setColor(const QColor &color)
{
    m_color = color;
    update();
}

inline QColor QtMaterialCheckableIcon::color() const
{
    return m_color;
}

inline void QtMaterialCheckableIcon::setIconSize(qreal size)
{
    m_iconSize = size;
    update();
}

inline qreal QtMaterialCheckableIcon::iconSize() const
{
    return m_iconSize;
}

inline void QtMaterialCheckableIcon::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    update();
}

inline qreal QtMaterialCheckableIcon::opacity() const
{
    return m_opacity;
}

#endif // QTMATERIALCHECKABLE_INTERNAL_H
