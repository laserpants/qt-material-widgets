#ifndef DRAWER_H
#define DRAWER_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QLayout>
#include <QtWidgets/QVBoxLayout>
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QLinearGradient>

#include "drawer_p.h"
#include "drawer_internal.h"
#include "lib/overlaywidget.h"

namespace md
{

class DrawerPrivate;
class DrawerStateMachine;

class Drawer : public OverlayWidget
{
    Q_OBJECT

public:
    explicit Drawer(QWidget *parent = 0);
    ~Drawer();

    void setDrawerWidth(int width);
    int drawerWidth() const;

    void setDrawerLayout(QLayout *layout);
    QLayout *drawerLayout() const;

    void setClickOutsideToClose(bool state);
    bool clickOutsideToClose() const;

    void setAutoRaise(bool state);
    bool autoRaise() const;

    void setOverlayMode(bool value);
    bool overlayMode() const;

public slots:
    void openDrawer();
    void closeDrawer();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<DrawerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Drawer)
    Q_DECLARE_PRIVATE(Drawer)
};
}
#endif // DRAWER_H
