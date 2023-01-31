#ifndef QTMATERIALAUTOCOMPLETE_H
#define QTMATERIALAUTOCOMPLETE_H

#include <qt-material-widgets/qt-material-widgets_export.hpp>

#include "qtmaterialtextfield.h"

class QtMaterialAutoCompletePrivate;

class QT_MATERIAL_WIDGETS_EXPORT QtMaterialAutoComplete
    : public QtMaterialTextField
{
  Q_OBJECT

public:
  explicit QtMaterialAutoComplete(QWidget* parent = 0);
  ~QtMaterialAutoComplete();

  void setDataSource(const QStringList& data);

signals:
  void itemSelected(QString);

protected slots:
  void updateResults(QString text);

protected:
  bool event(QEvent* event) Q_DECL_OVERRIDE;
  bool eventFilter(QObject* watched, QEvent* event) Q_DECL_OVERRIDE;

private:
  Q_DISABLE_COPY(QtMaterialAutoComplete)
  Q_DECLARE_PRIVATE(QtMaterialAutoComplete)
};

#endif  // QTMATERIALAUTOCOMPLETE_H
