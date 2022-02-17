#ifndef FAB_P_H
#define FAB_P_H

#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QState>
#include <QEvent>
#include <QPainter>

#include "raisedbutton_p.h"

namespace md
{

class FloatingActionButton;

class FloatingActionButtonPrivate : public RaisedButtonPrivate
{
    Q_DISABLE_COPY(FloatingActionButtonPrivate)
    Q_DECLARE_PUBLIC(FloatingActionButton)

public:
    enum {
        DefaultDiameter = 56,
        MiniDiameter = 40
    };

    enum {
        DefaultIconSize = 24,
        MiniIconSize = 18
    };

    FloatingActionButtonPrivate(FloatingActionButton *q);
    ~FloatingActionButtonPrivate();

    void init();
    QRect fabGeometry() const;
    void setupProperties();

    inline int diameter() const;
    inline int iconSize() const;

    Qt::Corner corner;
    bool       mini;
    int        offsX;
    int        offsY;
};

inline int FloatingActionButtonPrivate::diameter() const
{
    return mini ? MiniDiameter : DefaultDiameter;
}

inline int FloatingActionButtonPrivate::iconSize() const
{
    return mini ? MiniIconSize : DefaultIconSize;
}
}
#endif // FAB_P_H
