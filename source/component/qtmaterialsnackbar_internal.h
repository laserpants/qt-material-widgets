#ifndef QTMATERIALSNACKBAR_INTERNAL_H
#define QTMATERIALSNACKBAR_INTERNAL_H

#include <QStateMachine>
#include <QTimer>

class QtMaterialSnackbar;

class QtMaterialSnackbarStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
    QtMaterialSnackbarStateMachine(QtMaterialSnackbar *parent);
    ~QtMaterialSnackbarStateMachine();

    void setOffset(qreal offset);
    inline qreal offset() const;

public slots:
    void progress();

protected slots:
    void snackbarShown();

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialSnackbarStateMachine)

    QtMaterialSnackbar *const m_snackbar;
    QTimer                    m_timer;
    qreal                     m_offset;
};

inline qreal QtMaterialSnackbarStateMachine::offset() const
{
    return m_offset;
}

#endif // QTMATERIALSNACKBAR_INTERNAL_H
