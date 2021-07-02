#include "qtmaterialtabwidget.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <qtmaterialtabs.h>

QtMaterialTabWidget::QtMaterialTabWidget(QWidget *parent)
    : QWidget(parent)
    , tabBar(new QtMaterialTabs)
    , stackWidget(new QStackedWidget)
{
    tabBar->setObjectName(QStringLiteral("__qt__passive_tabBar"));
    tabBar->setHaloVisible(false);

    connect(tabBar, QOverload<int>::of(&QtMaterialTabs::currentChanged),
            this, &QtMaterialTabWidget::setCurrentIndex);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabBar);
    layout->addWidget(stackWidget);
}

void QtMaterialTabWidget::setHaloVisible(bool value)
{
    tabBar->setHaloVisible(value);
}

bool QtMaterialTabWidget::isHaloVisible() const
{
    return tabBar->isHaloVisible();
}

void QtMaterialTabWidget::setRippleStyle(MaterialConst::RippleStyle style)
{
    tabBar->setRippleStyle(style);
}

MaterialConst::RippleStyle QtMaterialTabWidget::rippleStyle() const
{
    return tabBar->rippleStyle();
}

void QtMaterialTabWidget::setInkColor(const QColor &color)
{
    tabBar->setInkColor(color);
}

QColor QtMaterialTabWidget::inkColor() const
{
    return tabBar->inkColor();
}

void QtMaterialTabWidget::setBackgroundColor(const QColor &color)
{
    tabBar->setBackgroundColor(color);
}

QColor QtMaterialTabWidget::backgroundColor() const
{
    return tabBar->backgroundColor();
}

void QtMaterialTabWidget::setTextColor(const QColor &color)
{
    tabBar->setTextColor(color);
}

QColor QtMaterialTabWidget::textColor() const
{
    return tabBar->textColor();
}

QSize QtMaterialTabWidget::sizeHint() const
{
    return QSize(300, 200);
}

void QtMaterialTabWidget::addPage(QWidget *page)
{
    insertPage(count(), page);
}

void QtMaterialTabWidget::removePage(int index)
{
    QWidget *widget = stackWidget->widget(index);
    stackWidget->removeWidget(widget);

    tabBar->removeTab(index);
}

int QtMaterialTabWidget::count() const
{
    return stackWidget->count();
}

int QtMaterialTabWidget::currentIndex() const
{
    return stackWidget->currentIndex();
}

void QtMaterialTabWidget::insertPage(int index, QWidget *page)
{
    page->setParent(stackWidget);

    stackWidget->insertWidget(index, page);

    QString title = page->windowTitle();
    if (title.isEmpty()) {
        title = tr("Tab %1").arg(tabBar->count() + 1);
        page->setWindowTitle(title);
    }
    connect(page, &QWidget::windowTitleChanged,
            this, &QtMaterialTabWidget::pageWindowTitleChanged);
    tabBar->insertTab(index, title);
}

void QtMaterialTabWidget::setCurrentIndex(int index)
{
    if (index != currentIndex()) {
        stackWidget->setCurrentIndex(index);
        tabBar->setCurrentTab(index);
        emit currentIndexChanged(index);
    }
}

void QtMaterialTabWidget::pageWindowTitleChanged()
{
    QWidget *page = qobject_cast<QWidget *>(sender());
    const int index = stackWidget->indexOf(page);
    tabBar->setTabText(index, page->windowTitle());
}

QWidget* QtMaterialTabWidget::widget(int index)
{
    return stackWidget->widget(index);
}

QString QtMaterialTabWidget::pageTitle() const
{
    if (const QWidget *currentWidget = stackWidget->currentWidget())
        return currentWidget->windowTitle();
    return QString();
}

void QtMaterialTabWidget::setPageTitle(QString const &newTitle)
{
    if (QWidget *currentWidget = stackWidget->currentWidget())
        currentWidget->setWindowTitle(newTitle);
    emit pageTitleChanged(newTitle);
}
