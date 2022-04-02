#ifndef QTMATERIALFAB_H
#define QTMATERIALFAB_H

#include "qtmaterialraisedbutton.h"
#include "qtmaterial_global.h"

class QtMaterialFloatingActionButtonPrivate;

class QT_MATERIAL_EXPORT QtMaterialFloatingActionButton : public QtMaterialRaisedButton
{
    Q_OBJECT
    Q_PROPERTY(bool mini WRITE setMini READ isMini)
    Q_PROPERTY(Qt::Corner corner WRITE setCorner READ corner)
    Q_PROPERTY(int xOffset WRITE setXOffset READ xOffset)
    Q_PROPERTY(int yOffset WRITE setYOffset READ yOffset)

public:
    explicit QtMaterialFloatingActionButton(QWidget *parent = 0);
    explicit QtMaterialFloatingActionButton(const QIcon &icon, QWidget *parent = 0);
    ~QtMaterialFloatingActionButton();

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
    Q_DISABLE_COPY(QtMaterialFloatingActionButton)
    Q_DECLARE_PRIVATE(QtMaterialFloatingActionButton)

};

#endif // QTMATERIALFAB_H
