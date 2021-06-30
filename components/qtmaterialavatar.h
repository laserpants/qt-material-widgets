#ifndef QTMATERIALAVATAR_H
#define QTMATERIALAVATAR_H

#include <QtWidgets/QWidget>
#include "lib/qtmaterialtheme.h"

class QtMaterialAvatarPrivate;

class QtMaterialAvatar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(int size WRITE setSize READ size)
    Q_PROPERTY(QChar letter WRITE setLetter READ letter)
    Q_PROPERTY(QImage image WRITE setImage READ image)
    Q_PROPERTY(QIcon icon WRITE setIcon READ icon)

public:
    explicit QtMaterialAvatar(QWidget *parent = 0);
    explicit QtMaterialAvatar(const QIcon &icon, QWidget *parent = 0);
    explicit QtMaterialAvatar(const QChar &letter, QWidget *parent = 0);
    explicit QtMaterialAvatar(const QImage &image, QWidget *parent = 0);
    ~QtMaterialAvatar();

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
    QChar letter() const;

    void setImage(const QImage &image);
    QImage image() const;

    void setIcon(const QIcon &icon);
    QIcon icon() const;

    MaterialConst::AvatarType type() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialAvatarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialAvatar)
    Q_DECLARE_PRIVATE(QtMaterialAvatar)
};

#endif // QTMATERIALAVATAR_H
