#ifndef QTMATERIALAVATAR_P_H
#define QTMATERIALAVATAR_P_H

#include <QtGlobal>
#include <QChar>
#include <QImage>
#include <QIcon>
#include <QPixmap>
#include <QColor>
#include "lib/qtmaterialtheme.h"

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
    int                     size;
    Material::AvatarType    type;
    QChar                   letter;
    QImage                  image;
    QIcon                   icon;
    QPixmap                 pixmap;
    bool                    useThemeColors;
    QColor                  textColor;
    QColor                  backgroundColor;
};

#endif // QTMATERIALAVATAR_P_H
