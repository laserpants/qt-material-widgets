#include "dividersettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <QLabel>
#include <qtmaterialdivider.h>

DividerSettingsEditor::DividerSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::DividerSettingsForm),
      m_divider1(new QtMaterialDivider),
      m_divider2(new QtMaterialDivider),
      m_textfield1(new QtMaterialTextField),
      m_textfield2(new QtMaterialTextField)
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
//    layout->setContentsMargins(0, 0, 0, 0);

    m_textfield1->setLabel( "First Name" );
    m_textfield1->setPlaceholderText( "Placeholder" );
    m_textfield1->setShowUnderline( false );

    m_textfield2->setLabel( "Middle Name" );
    m_textfield2->setShowUnderline( false );

    layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    canvas->setLayout(layout);
    layout->addWidget(m_textfield1);
    layout->addWidget(m_divider1);
    layout->addWidget(m_textfield2);
    layout->addWidget(m_divider2);
    layout->addStretch();

    setupForm();

}

DividerSettingsEditor::~DividerSettingsEditor()
{
    delete ui;
}

void DividerSettingsEditor::setupForm()
{
}

void DividerSettingsEditor::updateWidget()
{
}

