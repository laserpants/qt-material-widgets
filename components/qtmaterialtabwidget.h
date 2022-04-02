#ifndef QTMATERIALTABWIDGET_H
#define QTMATERIALTABWIDGET_H

#include <QWidget>
#include "qtmaterial_global.h"
#include "lib/qtmaterialtheme.h"

QT_BEGIN_NAMESPACE
class QStackedWidget;
QT_END_NAMESPACE
class QtMaterialTabs;

class QT_MATERIAL_EXPORT QtMaterialTabWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(QString pageTitle READ pageTitle WRITE setPageTitle STORED false)
    Q_PROPERTY(bool haloVisible WRITE setHaloVisible READ isHaloVisible)
    Q_PROPERTY(MaterialConst::RippleStyle rippleStyle WRITE setRippleStyle READ rippleStyle)
    Q_PROPERTY(QColor inkColor WRITE setInkColor READ inkColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)

public:
    explicit QtMaterialTabWidget(QWidget *parent = nullptr);

    void setHaloVisible(bool value);
    bool isHaloVisible() const;

    void setRippleStyle(MaterialConst::RippleStyle style);
    MaterialConst::RippleStyle rippleStyle() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    QSize sizeHint() const override;

    int count() const;
    int currentIndex() const;
    QWidget *widget(int index);
    QString pageTitle() const;

public slots:
    void addPage(QWidget *page);
    void insertPage(int index, QWidget *page);
    void removePage(int index);
    void setPageTitle(QString const &newTitle);
    void setCurrentIndex(int index);

private slots:
    void pageWindowTitleChanged();

signals:
    void currentIndexChanged(int index);
    void pageTitleChanged(const QString &title);

private:
    QtMaterialTabs *tabBar;
    QStackedWidget *stackWidget;
};

#endif // QTMATERIALTABWIDGET_H
