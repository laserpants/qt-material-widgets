#ifndef QTMATERIALAVATAR_P_H
#define QTMATERIALAVATAR_P_H

#include "lib/qtmaterialtheme.h"
#include <QChar>
#include <QColor>
#include <QIcon>
#include <QImage>
#include <QPixmap>
#include <QtGlobal>

class QtMaterialAvatar;

class QtMaterialAvatarPrivate
{
    Q_DISABLE_COPY(QtMaterialAvatarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialAvatar)

public:
    QtMaterialAvatarPrivate(QtMaterialAvatar *q);
    ~QtMaterialAvatarPrivate();

    void init();

    QtMaterialAvatar *const q_ptr;
    int size;
    Material::AvatarType type;
    QChar letter;
    QImage image;
    QIcon icon;
    QPixmap pixmap;
    bool useThemeColors;
    QColor textColor;
    QColor backgroundColor;
};

#endif  // QTMATERIALAVATAR_P_H
