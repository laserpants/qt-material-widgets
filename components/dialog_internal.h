#ifndef DIALOG_INTERNAL_H
#define DIALOG_INTERNAL_H

#include <QtWidgets/QWidget>
#include <QPainter>
#include <QPixmap>
#include <QEvent>
#include <QtWidgets/QStackedLayout>

#include "dialog.h"

namespace md
{

class Dialog;
class DialogWindow;

class DialogProxy : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

    enum TransparencyMode {
        Transparent,
        SemiTransparent,
        Opaque,
    };

public:
    DialogProxy(DialogWindow *source,
                          QStackedLayout *layout,
                          Dialog *dialog,
                          QWidget *parent = 0);
    ~DialogProxy();

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

protected slots:
    void makeOpaque();
    void makeTransparent();

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(DialogProxy)

    DialogWindow *const m_source;
    QStackedLayout         *const m_layout;
    Dialog       *const m_dialog;
    qreal                         m_opacity;
    TransparencyMode              m_mode;
};

inline qreal DialogProxy::opacity() const
{
    return m_opacity;
}

class DialogWindow : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
    explicit DialogWindow(Dialog *dialog, QWidget *parent = 0);
    ~DialogWindow();

    void setOffset(int offset);
    int offset() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(DialogWindow)

    Dialog *const m_dialog;
};
}

#endif // DIALOG_INTERNAL_H

