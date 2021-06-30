#ifndef QTMATERIALFLATBUTTON_H
#define QTMATERIALFLATBUTTON_H

#include <QtWidgets/QPushButton>
#include <QScopedPointer>
#include "lib/qtmaterialtheme.h"

class QtMaterialFlatButtonPrivate;

class QtMaterialFlatButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor overlayColor WRITE setOverlayColor READ overlayColor)
    Q_PROPERTY(QColor disabledForegroundColor WRITE setDisabledForegroundColor READ disabledForegroundColor)
    Q_PROPERTY(QColor disabledBackgroundColor WRITE setDisabledBackgroundColor READ disabledBackgroundColor)
    Q_PROPERTY(qreal fontSize WRITE setFontSize READ fontSize)

    Q_PROPERTY(bool useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(bool haloVisible WRITE setHaloVisible READ isHaloVisible)
    Q_PROPERTY(MaterialConst::Role role WRITE setRole READ role)
    Q_PROPERTY(MaterialConst::OverlayStyle overlayStyle WRITE setOverlayStyle READ overlayStyle)
    Q_PROPERTY(MaterialConst::RippleStyle rippleStyle WRITE setRippleStyle READ rippleStyle)
    Q_PROPERTY(MaterialConst::ButtonIconPlacement iconPlacement WRITE setIconPlacement READ iconPlacement)
    Q_PROPERTY(qreal cornerRadius WRITE setCornerRadius READ cornerRadius)
    Q_PROPERTY(Qt::BGMode backgroundMode WRITE setBackgroundMode READ backgroundMode)
    Q_PROPERTY(qreal baseOpacity WRITE setBaseOpacity READ baseOpacity)
    Q_PROPERTY(bool checkable WRITE setCheckable)

public:
    explicit QtMaterialFlatButton(QWidget *parent = 0, MaterialConst::ButtonPreset preset = MaterialConst::FlatPreset);
    explicit QtMaterialFlatButton(const QString &text, QWidget *parent = 0, MaterialConst::ButtonPreset preset = MaterialConst::FlatPreset);
    QtMaterialFlatButton(const QString &text, MaterialConst::Role role, QWidget *parent = 0, MaterialConst::ButtonPreset preset = MaterialConst::FlatPreset);
    ~QtMaterialFlatButton();

    void applyPreset(MaterialConst::ButtonPreset preset);

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

    void setDisabledForegroundColor(const QColor &color);
    QColor disabledForegroundColor() const;

    void setDisabledBackgroundColor(const QColor &color);
    QColor disabledBackgroundColor() const;

    void setFontSize(qreal size);
    qreal fontSize() const;

    void setHaloVisible(bool visible);
    bool isHaloVisible() const;

    void setRole(MaterialConst::Role role);
    MaterialConst::Role role() const;

    void setOverlayStyle(MaterialConst::OverlayStyle style);
    MaterialConst::OverlayStyle overlayStyle() const;

    void setRippleStyle(MaterialConst::RippleStyle style);
    MaterialConst::RippleStyle rippleStyle() const;

    void setIconPlacement(MaterialConst::ButtonIconPlacement placement);
    MaterialConst::ButtonIconPlacement iconPlacement() const;

    void setCornerRadius(qreal radius);
    qreal cornerRadius() const;

    void setBackgroundMode(Qt::BGMode mode);
    Qt::BGMode backgroundMode() const;

    void setBaseOpacity(qreal opacity);
    qreal baseOpacity() const;

    void setCheckable(bool value);

    void setHasFixedRippleRadius(bool value);
    bool hasFixedRippleRadius() const;

    void setFixedRippleRadius(qreal radius);

    void setTextAlignment(Qt::Alignment alignment);
    Qt::Alignment textAlignment() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    enum {
        IconPadding = 12
    };

    QtMaterialFlatButton(QtMaterialFlatButtonPrivate &d, QWidget *parent = 0, MaterialConst::ButtonPreset preset = MaterialConst::FlatPreset);

    void checkStateSet() Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    virtual void paintBackground(QPainter *painter);
    virtual void paintHalo(QPainter *painter);
    virtual void paintForeground(QPainter *painter);

    virtual void updateClipPath();

    const QScopedPointer<QtMaterialFlatButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialFlatButton)
    Q_DECLARE_PRIVATE(QtMaterialFlatButton)
};

#endif // QTMATERIALFLATBUTTON_H
