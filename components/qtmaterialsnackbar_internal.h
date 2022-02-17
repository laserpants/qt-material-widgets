#ifndef QTMATERIALSNACKBAR_INTERNAL_H
#define QTMATERIALSNACKBAR_INTERNAL_H

#include <QStateMachine>
#include <QTimer>

namespace md
{

class SnackBar;

class SnackBarStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
    SnackBarStateMachine(SnackBar *parent);
    ~SnackBarStateMachine();

    void setOffset(qreal offset);
    inline qreal offset() const;

public slots:
    void progress();

protected slots:
    void snackbarShown();

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(SnackBarStateMachine)

    SnackBar *const m_snackbar;
    QTimer                    m_timer;
    qreal                     m_offset;
};

inline qreal SnackBarStateMachine::offset() const
{
    return m_offset;
}
}
#endif // QTMATERIALSNACKBAR_INTERNAL_H
