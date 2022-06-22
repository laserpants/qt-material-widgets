#ifndef FAB_H
#define FAB_H

#include "raisedbutton.h"
namespace md
{

class FloatingActionButtonPrivate;

class FloatingActionButton : public RaisedButton
{
    Q_OBJECT

public:
    explicit FloatingActionButton(const QIcon &icon, QWidget *parent = 0);
    ~FloatingActionButton();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setMini(bool state);
    bool isMini() const;

    void setCorner(Qt::Corner corner);
    Qt::Corner corner() const;

    void setOffset(int x, int y);
    QSize offset() const;

    void setXOffset(int x);
    int xOffset() const;

    void setYOffset(int y);
    int yOffset() const;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void updateClipPath() Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(FloatingActionButton)
    Q_DECLARE_PRIVATE(FloatingActionButton)

};
}
#endif // FAB_H
