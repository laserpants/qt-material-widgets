#ifndef AVATAR_P_H
#define AVATAR_P_H

#include <QtGlobal>
#include <QChar>
#include <QImage>
#include <QIcon>
#include <QPixmap>
#include <QColor>
#include "lib/theme.h"

namespace md
{

class Avatar;

class AvatarPrivate
{
    Q_DISABLE_COPY(AvatarPrivate)
    Q_DECLARE_PUBLIC(Avatar)

public:
    AvatarPrivate(Avatar *q);
    ~AvatarPrivate();

    void init();

    Avatar *const q_ptr;
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

}

#endif // AVATAR_P_H
