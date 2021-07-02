#ifndef QTMATERIALSCROLLBAR_H
#define QTMATERIALSCROLLBAR_H

#include <QtWidgets/QScrollBar>
#include "qtmaterial_global.h"

class QtMaterialScrollBarPrivate;

class QT_MATERIAL_EXPORT QtMaterialScrollBar : public QScrollBar
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(QColor canvasColor WRITE setCanvasColor READ canvasColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor sliderColor WRITE setSliderColor READ sliderColor)
    Q_PROPERTY(bool hideOnMouseOut WRITE setHideOnMouseOut READ hideOnMouseOut)

public:
    explicit QtMaterialScrollBar(QWidget *parent = 0);
    ~QtMaterialScrollBar();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setCanvasColor(const QColor &color);
    QColor canvasColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setSliderColor(const QColor &color);
    QColor sliderColor() const;

    void setHideOnMouseOut(bool value);
    bool hideOnMouseOut() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialScrollBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialScrollBar)
    Q_DECLARE_PRIVATE(QtMaterialScrollBar)
};

#endif // QTMATERIALSCROLLBAR_H
