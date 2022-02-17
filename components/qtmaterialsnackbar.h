#ifndef QTMATERIALSNACKBAR_H
#define QTMATERIALSNACKBAR_H

#include "lib/qtmaterialoverlaywidget.h"
namespace md
{

class SnackBarPrivate;

class SnackBar : public OverlayWidget
{
    Q_OBJECT

public:
    explicit SnackBar(QWidget *parent = 0);
    ~SnackBar();

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

    const QScopedPointer<SnackBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(SnackBar)
    Q_DECLARE_PRIVATE(SnackBar)
};
}
#endif // QTMATERIALSNACKBAR_H
