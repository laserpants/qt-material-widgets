#include "dividersettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <QLabel>
#include <qtmaterialdivider.h>

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
    layout->setContentsMargins(20, 20, 20, 20);

    QLabel *lbl = new QLabel;
lbl->setText( "1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 " );

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    layout->addWidget(m_divider);
    layout->setAlignment(m_divider, Qt::AlignCenter);
    m_divider->setSize( canvas->width() );
    layout->addWidget(lbl);
        QSizePolicy policy(QSizePolicy::Ignored,
                       QSizePolicy::Fixed);
    lbl->setSizePolicy(policy);
    m_divider->setSizePolicy(policy);


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

