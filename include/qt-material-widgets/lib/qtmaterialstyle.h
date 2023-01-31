#ifndef QTMATERIALSTYLE_H
#define QTMATERIALSTYLE_H

#include <memory>

#include <qt-material-widgets/qt-material-widgets_export.hpp>

#include <QtWidgets/QCommonStyle>
class QtMaterialStylePrivate;
#define MATERIAL_DISABLE_THEME_COLORS \
  if (d->useThemeColors == true) { \
    d->useThemeColors = false; \
  }

class QtMaterialTheme;

class QT_MATERIAL_WIDGETS_EXPORT QtMaterialStyle : public QCommonStyle
{
  Q_OBJECT

public:
  inline static QtMaterialStyle& instance();

  void setTheme(QtMaterialTheme* theme);
  QColor themeColor(const QString& key) const;

protected:
  const std::shared_ptr<QtMaterialStylePrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(QtMaterialStyle)

  QtMaterialStyle();

  QtMaterialStyle(QtMaterialStyle const&);
  void operator=(QtMaterialStyle const&);
};

inline QtMaterialStyle& QtMaterialStyle::instance()
{
  static QtMaterialStyle instance;
  return instance;
}

#endif  // QTMATERIALSTYLE_H
