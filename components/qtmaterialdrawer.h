#ifndef QTMATERIALDRAWER_H
#define QTMATERIALDRAWER_H

#include "lib/qtmaterialoverlaywidget.h"
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
#endif // QTMATERIALDRAWER_H
