#ifndef FLATBUTTON_P_H
#define FLATBUTTON_P_H

#include <QtGlobal>
#include <QColor>
#include "lib/theme.h"

namespace md
{
class FlatButton;
class RippleOverlay;
class FlatButtonStateMachine;

class FlatButtonPrivate
{
    Q_DISABLE_COPY(FlatButtonPrivate)
    Q_DECLARE_PUBLIC(FlatButton)

public:
    FlatButtonPrivate(FlatButton *q);
    virtual ~FlatButtonPrivate();

    void init();

    FlatButton             *const q_ptr;
    RippleOverlay          *rippleOverlay;
    FlatButtonStateMachine *stateMachine;
    Material::Role                    role;
    Material::RippleStyle             rippleStyle;
    Material::ButtonIconPlacement     iconPlacement;
    Material::OverlayStyle            overlayStyle;
    Qt::BGMode                        bgMode;
    Qt::Alignment                     textAlignment;
    QColor                            backgroundColor;
    QColor                            foregroundColor;
    QColor                            overlayColor;
    QColor                            disabledColor;
    QColor                            disabledBackgroundColor;
    qreal                             fixedRippleRadius;
    qreal                             cornerRadius;
    qreal                             baseOpacity;
    qreal                             fontSize;
    bool                              useThemeColors;
    bool                              useFixedRippleRadius;
    bool                              haloVisible;
};
}

#endif // FLATBUTTON_P_H
