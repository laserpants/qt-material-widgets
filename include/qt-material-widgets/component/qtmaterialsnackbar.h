#ifndef QTMATERIALSNACKBAR_H
#define QTMATERIALSNACKBAR_H

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialSnackbarPrivate;

class QtMaterialSnackbar : public QtMaterialOverlayWidget
{
    Q_OBJECT

public:
    explicit QtMaterialSnackbar(QWidget *parent = 0);
    ~QtMaterialSnackbar();

    void setAutoHideDuration(int duration);
    int autoHideDuration() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setBackgroundOpacity(qreal opacity);
    qreal backgroundOpacity() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setFontSize(qreal size);
    qreal fontSize() const;

    void setBoxWidth(int width);
    int boxWidth() const;

    void setClickToDismissMode(bool value);
    bool clickToDismissMode() const;

public slots:
    void addMessage(const QString &message);
    void addInstantMessage(const QString &message);

protected slots:
    void dequeue();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialSnackbarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSnackbar)
    Q_DECLARE_PRIVATE(QtMaterialSnackbar)
};

#endif // QTMATERIALSNACKBAR_H
