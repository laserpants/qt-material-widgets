#ifndef AVATAR_H
#define AVATAR_H

#include <QtWidgets/QWidget>
#include "lib/theme.h"

namespace md {
class AvatarPrivate;

class Avatar : public QWidget
{
    Q_OBJECT

public:
    explicit Avatar(QWidget *parent = 0);
    explicit Avatar(const QIcon &icon, QWidget *parent = 0);
    explicit Avatar(const QChar &letter, QWidget *parent = 0);
    explicit Avatar(const QImage &image, QWidget *parent = 0);
    ~Avatar();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setSize(int size);
    int size() const;

    void setLetter(const QChar &letter);
    void setImage(const QImage &image);
    void setIcon(const QIcon &icon);

    Material::AvatarType type() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<AvatarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Avatar)
    Q_DECLARE_PRIVATE(Avatar)
};
}

#endif // AVATAR_H
