#ifndef PROGRESS_H
#define PROGRESS_H

#include <QtWidgets/QProgressBar>
#include "lib/theme.h"

namespace md
{

class ProgressBarPrivate;

class ProgressBar : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(QColor progressColor WRITE setProgressColor READ progressColor)
    Q_PROPERTY(QColor backgroundColor WRITE setProgressColor READ backgroundColor)

public:
    explicit ProgressBar(QWidget *parent = 0);
    ~ProgressBar();

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

    void setUseThemeColors(bool state);
    bool useThemeColors() const;

    void setProgressColor(const QColor &color);
    QColor progressColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<ProgressBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(ProgressBar)
    Q_DECLARE_PRIVATE(ProgressBar)
};
}
#endif // PROGRESS_H
