#include "menusettingseditor.h"
#include <QVBoxLayout>
#include <QDebug>
#include <qtmaterialmenu.h>

MenuSettingsEditor::MenuSettingsEditor(QWidget *parent)
    : QWidget(parent),
      //ui(new Ui::MenuSettingsForm),
      m_menu(new QtMaterialMenu)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    //ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);

    layout->addWidget(m_menu);
    layout->addSpacing(600);
    layout->setAlignment(m_menu, Qt::AlignCenter);

    setupForm();
}

MenuSettingsEditor::~MenuSettingsEditor()
{
    //delete ui;
}

void MenuSettingsEditor::setupForm()
{
}

void MenuSettingsEditor::updateWidget()
{
}

void MenuSettingsEditor::selectColor()
{
}
