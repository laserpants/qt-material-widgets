#include "togglesettingseditor.h"
#include <QColorDialog>
#include <qtmaterialtoggle.h>

ToggleSettingsEditor::ToggleSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ToggleSettingsForm),
      m_toggle(new QtMaterialToggle)
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

    m_toggle->setOrientation(Qt::Vertical);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    layout->addWidget(m_toggle);
    layout->setAlignment(m_toggle, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->checkedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->orientationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->disabledColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->activeColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->inactiveColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->trackColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    connect(m_toggle, SIGNAL(toggled(bool)), this, SLOT(setupForm()));
}

ToggleSettingsEditor::~ToggleSettingsEditor()
{
}

void ToggleSettingsEditor::setupForm()
{
    switch (m_toggle->orientation())
    {
    case Qt::Horizontal:
        ui->orientationComboBox->setCurrentIndex(0);
        break;
    case Qt::Vertical:
        ui->orientationComboBox->setCurrentIndex(1);
        break;
    default:
        break;
    }

    ui->disabledCheckBox->setChecked(!m_toggle->isEnabled());
    ui->checkedCheckBox->setChecked(m_toggle->isChecked());
    ui->useThemeColorsCheckBox->setChecked(m_toggle->useThemeColors());
}

void ToggleSettingsEditor::updateWidget()
{
    switch (ui->orientationComboBox->currentIndex())
    {
    case 0:
        m_toggle->setOrientation(Qt::Horizontal);
        break;
    case 1:
        m_toggle->setOrientation(Qt::Vertical);
        break;
    default:
        break;
    }

    m_toggle->setDisabled(ui->disabledCheckBox->isChecked());
    m_toggle->setChecked(ui->checkedCheckBox->isChecked());
    m_toggle->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void ToggleSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("disabledColorToolButton" == senderName) {
            m_toggle->setDisabledColor(color);
            ui->disabledColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("activeColorToolButton" == senderName) {
            m_toggle->setActiveColor(color);
            ui->activeColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("inactiveColorToolButton" == senderName) {
            m_toggle->setInactiveColor(color);
            ui->inactiveColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("trackColorToolButton" == senderName) {
            m_toggle->setTrackColor(color);
            ui->trackColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
