#ifndef ICONBUTTON_P_H
#define ICONBUTTON_P_H

#include <QtGlobal>
#include <QColor>

namespace md
{
class IconButton;
class RippleOverlay;

class IconButtonPrivate
{
    Q_DISABLE_COPY(IconButtonPrivate)
    Q_DECLARE_PUBLIC(IconButton)

public:
    IconButtonPrivate(IconButton *q);
    virtual ~IconButtonPrivate();

    void init();
    void updateRipple();

    IconButton    *const q_ptr;
    RippleOverlay *rippleOverlay;
    QColor                   color;
    QColor                   disabledColor;
    bool                     useThemeColors;
};

}

#endif // ICONBUTTON_P_H
