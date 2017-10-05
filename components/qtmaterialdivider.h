#ifndef QTMATERIALDIVIDER_H
#define QTMATERIALDIVIDER_H

#include <QtWidgets/QWidget>
#include <QResizeEvent>
#include "lib/qtmaterialtheme.h"

class QtMaterialDividerPrivate;

class QtMaterialDivider : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialDivider(QWidget *parent = 0);
    //explicit QtMaterialDivider(const QIcon &icon, QWidget *parent = 0);
    //explicit QtMaterialDivider(const QChar &letter, QWidget *parent = 0);
    //explicit QtMaterialDivider(const QImage &image, QWidget *parent = 0);
    ~QtMaterialDivider();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    //void setTextColor(const QColor &color);
    //QColor textColor() const;

    //void setBackgroundColor(const QColor &color);
    //QColor backgroundColor() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setSize(int size);
    int size() const;

    //void setLetter(const QChar &letter);
    //void setImage(const QImage &image);
    //void setIcon(const QIcon &icon);

    //Material::DividerType type() const;

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialDividerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDivider)
    Q_DECLARE_PRIVATE(QtMaterialDivider)
};

#endif // QTMATERIALDIVIDER_H
