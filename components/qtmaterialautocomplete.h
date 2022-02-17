#ifndef QTMATERIALAUTOCOMPLETE_H
#define QTMATERIALAUTOCOMPLETE_H

#include "qtmaterialtextfield.h"

namespace md
{

class AutoCompletePrivate;

class AutoComplete : public TextField
{
    Q_OBJECT

public:
    explicit AutoComplete(QWidget *parent = 0);
    ~AutoComplete();

    void setDataSource(const QStringList &data);

signals:
    void itemSelected(QString);

protected slots:
    void updateResults(QString text);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(AutoComplete)
    Q_DECLARE_PRIVATE(AutoComplete)
};

}

#endif // QTMATERIALAUTOCOMPLETE_H
