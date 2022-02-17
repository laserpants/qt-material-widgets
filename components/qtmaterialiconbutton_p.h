#ifndef QTMATERIALICONBUTTON_P_H
#define QTMATERIALICONBUTTON_P_H

#include <QtGlobal>


namespace md
{
class IconButton;
class RippleOverlay;
class QColor;

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

#endif // QTMATERIALICONBUTTON_P_H
