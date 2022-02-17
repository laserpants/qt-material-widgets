#ifndef DRAWER_INTERNAL_H
#define DRAWER_INTERNAL_H

#include <QStateMachine>
#include "lib/qtmaterialoverlaywidget.h"

namespace md
{

class Drawer;
class DrawerWidget;

class DrawerStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    explicit DrawerStateMachine(DrawerWidget *drawer,
                                          Drawer *parent);
    ~DrawerStateMachine();

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

    bool isInClosedState() const;

    void updatePropertyAssignments();

signals:
    void signalOpen();
    void signalClose();

private:
    Q_DISABLE_COPY(DrawerStateMachine)

    DrawerWidget *const m_drawer;
    Drawer       *const m_main;
    QState                 *const m_openingState;
    QState                 *const m_openedState;
    QState                 *const m_closingState;
    QState                 *const m_closedState;
    qreal                         m_opacity;
};

inline qreal DrawerStateMachine::opacity() const
{
    return m_opacity;
}

class DrawerWidget : public OverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
    explicit DrawerWidget(QWidget *parent = 0);
    ~DrawerWidget();

    void setOffset(int offset);
    inline int offset() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    QRect overlayGeometry() const Q_DECL_OVERRIDE;

private:
    int  m_offset;
};

inline int DrawerWidget::offset() const
{
    return m_offset;
}
}
#endif // DRAWER_INTERNAL_H
