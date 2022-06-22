#ifndef DIALOG_H
#define DIALOG_H

#include <QScopedPointer>
#include <QLayout>

#include "dialog_p.h"
#include "dialog_internal.h"
#include "lib/statetransition.h"
#include "lib/overlaywidget.h"

namespace md
{

class DialogPrivate;

class Dialog : public OverlayWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QLayout *windowLayout() const;
    void setWindowLayout(QLayout *layout);

public slots:
    void showDialog();
    void hideDialog();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<DialogPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Dialog)
    Q_DECLARE_PRIVATE(Dialog)
};
}
#endif // DIALOG_H
