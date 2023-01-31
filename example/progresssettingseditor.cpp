#include "progresssettingseditor.h"
#include <QColorDialog>
#include <qtmaterialprogress.h>
#include <lib/qtmaterialtheme.h>

ProgressSettingsEditor::ProgressSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ProgressSettingsForm),
      m_progress(new QtMaterialProgress)
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
    layout->addWidget(m_progress);
    layout->setAlignment(m_progress, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->progressTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->progressSlider, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->progressColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->backgroundColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    ui->progressSlider->setRange(0, 100);
}

ProgressSettingsEditor::~ProgressSettingsEditor()
{
    delete ui;
}

void ProgressSettingsEditor::setupForm()
{
    switch (m_progress->progressType())
    {
    case Material::DeterminateProgress:
        ui->progressTypeComboBox->setCurrentIndex(0);
        break;
    case Material::IndeterminateProgress:
        ui->progressTypeComboBox->setCurrentIndex(1);
        break;
    default:
        break;
    }

    ui->disabledCheckBox->setChecked(!m_progress->isEnabled());
    ui->progressSlider->setValue(m_progress->value());
    ui->useThemeColorsCheckBox->setChecked(m_progress->useThemeColors());
}

void ProgressSettingsEditor::updateWidget()
{
    switch (ui->progressTypeComboBox->currentIndex())
    {
    case 0:
        m_progress->setProgressType(Material::DeterminateProgress);
        break;
    case 1:
        m_progress->setProgressType(Material::IndeterminateProgress);
        break;
    default:
        break;
    }

    m_progress->setDisabled(ui->disabledCheckBox->isChecked());
    m_progress->setValue(ui->progressSlider->value());
    m_progress->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void ProgressSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("progressColorToolButton" == senderName) {
            m_progress->setProgressColor(color);
            ui->progressColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("backgroundColorToolButton" == senderName) {
            m_progress->setBackgroundColor(color);
            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
