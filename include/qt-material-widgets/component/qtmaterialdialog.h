#ifndef QTMATERIALDIALOG_H
#define QTMATERIALDIALOG_H

#include <QScopedPointer>
#include <qwidget.h>

#include "qt-material-widgets/lib/qtmaterialoverlaywidget.h"

class QLayout;
class QtMaterialDialogPrivate;

class QT_MATERIAL_WIDGETS_EXPORT QtMaterialDialog
    : public QtMaterialOverlayWidget
{
    Q_OBJECT

public:
    explicit QtMaterialDialog(QWidget *parent = 0);
    ~QtMaterialDialog();

    QLayout *windowLayout() const;
    void setWindowLayout(QLayout *layout);
    QWidget* getContentWidget() const;

public slots:
    void showDialog();
    void hideDialog();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialDialogPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDialog)
    Q_DECLARE_PRIVATE(QtMaterialDialog)
};


#endif // QTMATERIALDIALOG_H
