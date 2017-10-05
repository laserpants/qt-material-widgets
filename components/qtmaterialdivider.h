#ifndef QTMATERIALDIVIDER_H
#define QTMATERIALDIVIDER_H

#include <QtWidgets/QWidget>
#include <QResizeEvent>
#include "lib/qtmaterialtheme.h"

class QtMaterialDividerPrivate;

class QtMaterialDivider : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialDivider(QWidget *parent = 0);
    ~QtMaterialDivider();

    void setInsetSize(int size);
    int insetSize() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialDividerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDivider)
    Q_DECLARE_PRIVATE(QtMaterialDivider)
};

#endif // QTMATERIALDIVIDER_H
