#include "circularprogresssettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <qtmaterialcircularprogress.h>

CircularProgressSettingsEditor::CircularProgressSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::CircularProgressSettingsForm),
      m_progress(new QtMaterialCircularProgress)
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
    connect(ui->lineWidthDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui->sizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->colorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    ui->sizeSpinBox->setRange(10, 200);
    ui->progressSlider->setRange(0, 100);
}

CircularProgressSettingsEditor::~CircularProgressSettingsEditor()
{
    delete ui;
}

void CircularProgressSettingsEditor::setupForm()
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
    ui->lineWidthDoubleSpinBox->setValue(m_progress->lineWidth());
    ui->sizeSpinBox->setValue(m_progress->size());
    ui->useThemeColorsCheckBox->setChecked(m_progress->useThemeColors());
}

void CircularProgressSettingsEditor::updateWidget()
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
    m_progress->setLineWidth(ui->lineWidthDoubleSpinBox->value());
    m_progress->setSize(ui->sizeSpinBox->value());
    m_progress->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void CircularProgressSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("colorToolButton" == senderName) {
            m_progress->setColor(color);
            ui->colorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
