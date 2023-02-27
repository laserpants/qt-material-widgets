#include "drawersettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <qtmaterialdrawer.h>

DrawerSettingsEditor::DrawerSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::DrawerSettingsForm),
      m_drawer(new QtMaterialDrawer)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    canvas->setMaximumHeight(300);

    m_drawer->setParent(canvas);
    m_drawer->setClickOutsideToClose(true);
    m_drawer->setOverlayMode(true);

    //

    QVBoxLayout *drawerLayout = new QVBoxLayout;
    m_drawer->setDrawerLayout(drawerLayout);

    QVector<QString> labels = {"Motion", "Style", "Layout", "Components", "Patterns", "Growth & communications", "Usability", "Platforms", "Resources"};

    QVector<QString>::iterator it;
    for (it = labels.begin(); it != labels.end(); ++it) {
        QLabel *label = new QLabel(*it);
        label->setMinimumHeight(30);
        label->setFont(QFont("Roboto", 10, QFont::Medium));
        drawerLayout->addWidget(label);
    }

    drawerLayout->addStretch(3);
    m_drawer->setContentsMargins(10, 0, 0, 0);

    drawerLayout->addWidget(new QPushButton("abc"));

    //

    setupForm();

    connect(ui->showDrawerButton, SIGNAL(pressed()), m_drawer, SLOT(openDrawer()));
    connect(ui->hideDrawerButton, SIGNAL(pressed()), m_drawer, SLOT(closeDrawer()));
    connect(ui->clickToCloseCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->overlayModeCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
}

DrawerSettingsEditor::~DrawerSettingsEditor()
{
    delete ui;
}

void DrawerSettingsEditor::setupForm()
{
    ui->clickToCloseCheckBox->setChecked(m_drawer->clickOutsideToClose());
    ui->overlayModeCheckBox->setChecked(m_drawer->overlayMode());
}

void DrawerSettingsEditor::updateWidget()
{
    m_drawer->setClickOutsideToClose(ui->clickToCloseCheckBox->isChecked());
    m_drawer->setOverlayMode(ui->overlayModeCheckBox->isChecked());
}
