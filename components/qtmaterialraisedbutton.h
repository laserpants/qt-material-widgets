#ifndef QTMATERIALRAISEDBUTTON_H
#define QTMATERIALRAISEDBUTTON_H

#include "qtmaterialflatbutton.h"
namespace md
{

class RaisedButtonPrivate;

class RaisedButton : public FlatButton
{
    Q_OBJECT

public:
    explicit RaisedButton(QWidget *parent = 0);
    explicit RaisedButton(const QString &text, QWidget *parent = 0);
    ~RaisedButton();

protected:
    RaisedButton(RaisedButtonPrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(RaisedButton)
    Q_DECLARE_PRIVATE(RaisedButton)
};
}
#endif // QTMATERIALRAISEDBUTTON_H
