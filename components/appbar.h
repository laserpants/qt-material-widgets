#ifndef APPBAR_H
#define APPBAR_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

namespace md
{

class AppBarPrivate;

class AppBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)

public:
    explicit AppBar(QWidget *parent = 0);
    ~AppBar();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    inline QHBoxLayout *appBarLayout() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<AppBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(AppBar)
    Q_DECLARE_PRIVATE(AppBar)
};

inline QHBoxLayout *AppBar::appBarLayout() const
{
    return static_cast<QHBoxLayout *>(layout());
}

}

#endif // APPBAR_H
