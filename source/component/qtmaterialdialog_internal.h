#ifndef QTMATERIALDIALOG_INTERNAL_H
#define QTMATERIALDIALOG_INTERNAL_H

#include <QtWidgets/QWidget>

class QStackedLayout;
class QtMaterialDialog;
class QtMaterialDialogWindow;

class QtMaterialDialogProxy : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

    enum TransparencyMode {
        Transparent,
        SemiTransparent,
        Opaque,
    };

public:
    QtMaterialDialogProxy(QtMaterialDialogWindow *source,
                          QStackedLayout *layout,
                          QtMaterialDialog *dialog,
                          QWidget *parent = 0);
    ~QtMaterialDialogProxy();

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
    Q_DISABLE_COPY(QtMaterialDialogProxy)

    QtMaterialDialogWindow *const m_source;
    QStackedLayout         *const m_layout;
    QtMaterialDialog       *const m_dialog;
    qreal                         m_opacity;
    TransparencyMode              m_mode;
};

inline qreal QtMaterialDialogProxy::opacity() const
{
    return m_opacity;
}

class QtMaterialDialogWindow : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
    explicit QtMaterialDialogWindow(QtMaterialDialog *dialog, QWidget *parent = 0);
    ~QtMaterialDialogWindow();

    void setOffset(int offset);
    int offset() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialDialogWindow)

    QtMaterialDialog *const m_dialog;
};

#endif // QTMATERIALDIALOG_INTERNAL_H
