#ifndef QTMATERIALBADGE_H
#define QTMATERIALBADGE_H

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialBadgePrivate;

class QtMaterialBadge : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QPointF relativePosition WRITE setRelativePosition READ relativePosition)

public:
    explicit QtMaterialBadge(QWidget *parent = 0);
    explicit QtMaterialBadge(const QIcon &icon, QWidget *parent = 0);
    explicit QtMaterialBadge(const QString &text, QWidget *parent = 0);
    ~QtMaterialBadge();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setRelativePosition(const QPointF &pos);
    void setRelativePosition(qreal x, qreal y);
    QPointF relativePosition() const;

    void setRelativeXPosition(qreal x);
    qreal relativeXPosition() const;

    void setRelativeYPosition(qreal y);
    qreal relativeYPosition() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setIcon(const QIcon &icon);
    QIcon icon() const;

    void setText(const QString &text);
    QString text() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    int getDiameter() const;

    const QScopedPointer<QtMaterialBadgePrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialBadge)
    Q_DECLARE_PRIVATE(QtMaterialBadge)
};

#endif // QTMATERIALBADGE_H
