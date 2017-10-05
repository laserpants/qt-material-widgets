#include "dividersettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <QLabel>
#include <qtmaterialdivider.h>
#include <qtmaterialtextfield.h>

DividerSettingsEditor::DividerSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::DividerSettingsForm),
      m_divider(new QtMaterialDivider)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    ui->setupUi(widget);
//    layout->setContentsMargins(20, 20, 20, 20);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel *lbl = new QLabel;
    lbl->setText( "1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 " );

    QtMaterialTextField *txt1 = new QtMaterialTextField;
    txt1->setLabel( "First Name" );
    txt1->setPlaceholderText( "Placeholder" );

    QtMaterialTextField *txt2 = new QtMaterialTextField;
    txt2->setLabel( "Middle Name" );

    QtMaterialDivider *div2 = new QtMaterialDivider;
    div2->setInsetSize( 40 );

    layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    canvas->setLayout(layout);
    layout->addWidget(txt1);
    layout->addWidget(m_divider);
    layout->addWidget(txt2);
    layout->addWidget(div2);
    layout->addWidget(lbl);

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

