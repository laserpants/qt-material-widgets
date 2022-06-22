#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QtWidgets/QAbstractButton>

namespace md
{

class IconButtonPrivate;

class IconButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit IconButton(const QIcon &icon, QWidget *parent = 0);
    ~IconButton();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setColor(const QColor &color);
    QColor color() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

protected:
    IconButton(IconButtonPrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<IconButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(IconButton)
    Q_DECLARE_PRIVATE(IconButton)
};

}

#endif // ICONBUTTON_H
