#ifndef QTMATERIALDIALOG_H
#define QTMATERIALDIALOG_H

#include <QScopedPointer>
#include <QLayout>

#include "qtmaterialdialog_p.h"
#include "qtmaterialdialog_internal.h"
#include "lib/qtmaterialstatetransition.h"
#include "lib/qtmaterialoverlaywidget.h"

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
#endif // QTMATERIALDIALOG_H
