#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QtWidgets/QWidget>

namespace md
{
class OverlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OverlayWidget(QWidget *parent = 0);
    ~OverlayWidget();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

    virtual QRect overlayGeometry() const;

private:
    Q_DISABLE_COPY(OverlayWidget)
};
}

#endif // OVERLAYWIDGET_H
