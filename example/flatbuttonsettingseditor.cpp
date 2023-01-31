#include "flatbuttonsettingseditor.h"
#include <QColorDialog>
#include <QDebug>
#include <qtmaterialflatbutton.h>

FlatButtonSettingsEditor::FlatButtonSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::FlatButtonSettingsForm),
      m_button(new QtMaterialFlatButton("I'm flat"))
{
    init();
}

FlatButtonSettingsEditor::~FlatButtonSettingsEditor()
{
    delete ui;
}

FlatButtonSettingsEditor::FlatButtonSettingsEditor(QtMaterialFlatButton *button, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::FlatButtonSettingsForm),
      m_button(button)
{
    init();
}

void FlatButtonSettingsEditor::setupForm()
{
    switch (m_button->role())
    {
    case Material::Default:
        ui->buttonRoleComboBox->setCurrentIndex(0);
        break;
    case Material::Primary:
        ui->buttonRoleComboBox->setCurrentIndex(1);
        break;
    case Material::Secondary:
        ui->buttonRoleComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    switch (m_button->overlayStyle())
    {
    case Material::NoOverlay:
        ui->hoverStyleComboBox->setCurrentIndex(0);
        break;
    case Material::TintedOverlay:
        ui->hoverStyleComboBox->setCurrentIndex(1);
        break;
    case Material::GrayOverlay:
        ui->hoverStyleComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    switch (m_button->rippleStyle())
    {
    case Material::CenteredRipple:
        ui->rippleStyleComboBox->setCurrentIndex(0);
        break;
    case Material::PositionedRipple:
        ui->rippleStyleComboBox->setCurrentIndex(1);
        break;
    case Material::NoRipple:
        ui->rippleStyleComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    switch (m_button->iconPlacement())
    {
    case Material::LeftIcon:
        ui->iconPlacementComboBox->setCurrentIndex(0);
        break;
    case Material::RightIcon:
        ui->iconPlacementComboBox->setCurrentIndex(1);
        break;
    }

    switch (ui->textAlignmentComboBox->currentIndex())
    {
    case Qt::AlignLeft:
        ui->textAlignmentComboBox->setCurrentIndex(0);
        break;
    default:
        ui->textAlignmentComboBox->setCurrentIndex(1);
    }

    ui->checkedCheckBox->setEnabled(m_button->isCheckable());

    ui->disabledCheckBox->setChecked(!m_button->isEnabled());
    ui->checkableCheckBox->setChecked(m_button->isCheckable());
    ui->checkedCheckBox->setChecked(m_button->isChecked());
    ui->showHaloCheckBox->setChecked(m_button->isHaloVisible());
    ui->iconCheckBox->setChecked(!m_button->icon().isNull());
    ui->useThemeColorsCheckBox->setChecked(m_button->useThemeColors());
    ui->transparentCheckBox->setChecked(Qt::TransparentMode == m_button->backgroundMode());
    ui->cornerRadiusSpinBox->setValue(m_button->cornerRadius());
    ui->overlayOpacityDoubleSpinBox->setValue(m_button->baseOpacity());
    ui->iconSizeSpinBox->setValue(m_button->iconSize().width());
    ui->fontSizeDoubleSpinBox->setValue(m_button->fontSize());
    ui->buttonTextLineEdit->setText(m_button->text());
}

void FlatButtonSettingsEditor::updateWidget()
{
    switch (ui->buttonRoleComboBox->currentIndex())
    {
    case 0:
        m_button->setRole(Material::Default);
        break;
    case 1:
        m_button->setRole(Material::Primary);
        break;
    case 2:
        m_button->setRole(Material::Secondary);
        break;
    default:
        break;
    }

    switch (ui->hoverStyleComboBox->currentIndex())
    {
    case 0:
        m_button->setOverlayStyle(Material::NoOverlay);
        break;
    case 1:
        m_button->setOverlayStyle(Material::TintedOverlay);
        break;
    case 2:
        m_button->setOverlayStyle(Material::GrayOverlay);
        break;
    default:
        break;
    }

    switch (ui->rippleStyleComboBox->currentIndex())
    {
    case 0:
        m_button->setRippleStyle(Material::CenteredRipple);
        break;
    case 1:
        m_button->setRippleStyle(Material::PositionedRipple);
        break;
    case 2:
        m_button->setRippleStyle(Material::NoRipple);
        break;
    default:
        break;
    }

    switch (ui->iconPlacementComboBox->currentIndex())
    {
    case 0:
        m_button->setIconPlacement(Material::LeftIcon);
        break;
    case 1:
        m_button->setIconPlacement(Material::RightIcon);
        break;
    default:
        break;
    }

    switch (ui->textAlignmentComboBox->currentIndex())
    {
    case 0:
        m_button->setTextAlignment(Qt::AlignLeft);
        break;
    case 1:
    default:
        m_button->setTextAlignment(Qt::AlignHCenter);
        break;
    }

    m_button->setDisabled(ui->disabledCheckBox->isChecked());
    m_button->setCheckable(ui->checkableCheckBox->isChecked());
    m_button->setChecked(ui->checkedCheckBox->isChecked());
    m_button->setHaloVisible(ui->showHaloCheckBox->isChecked());
    m_button->setIcon(ui->iconCheckBox->isChecked() ? QtMaterialTheme::icon("toggle", "star")
                                                    : QIcon());
    m_button->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_button->setBackgroundMode(ui->transparentCheckBox->isChecked()
                                ? Qt::TransparentMode : Qt::OpaqueMode);
    m_button->setCornerRadius(ui->cornerRadiusSpinBox->value());
    m_button->setBaseOpacity(ui->overlayOpacityDoubleSpinBox->value());
    m_button->setIconSize(QSize(ui->iconSizeSpinBox->value(), ui->iconSizeSpinBox->value()));
    m_button->setFontSize(ui->fontSizeDoubleSpinBox->value());
    m_button->setText(ui->buttonTextLineEdit->text());

    ui->checkedCheckBox->setEnabled(m_button->isCheckable());
}

void FlatButtonSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("foregroundColorToolButton" == senderName) {
            m_button->setForegroundColor(color);
            ui->foregroundColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("backgroundColorToolButton" == senderName) {
            m_button->setBackgroundColor(color);
            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("overlayColorToolButton" == senderName) {
            m_button->setOverlayColor(color);
            ui->overlayColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("disabledFgColorToolButton" == senderName) {
            m_button->setDisabledForegroundColor(color);
            ui->disableFgColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("disabledBgColorToolButton" == senderName) {
            m_button->setDisabledBackgroundColor(color);
            ui->disabledBgColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}

void FlatButtonSettingsEditor::applyDefaultPreset()
{
    ui->buttonRoleComboBox->setCurrentIndex(0);
    ui->rippleStyleComboBox->setCurrentIndex(1);
    ui->iconPlacementComboBox->setCurrentIndex(0);
    ui->hoverStyleComboBox->setCurrentIndex(2);
    ui->textAlignmentComboBox->setCurrentIndex(1);
    ui->transparentCheckBox->setChecked(true);
    ui->cornerRadiusSpinBox->setValue(3);
    ui->overlayOpacityDoubleSpinBox->setValue(0.13);
    ui->fontSizeDoubleSpinBox->setValue(10);
    ui->useThemeColorsCheckBox->setChecked(true);
    ui->showHaloCheckBox->setChecked(true);
    ui->checkableCheckBox->setChecked(false);
    ui->disabledCheckBox->setChecked(false);
    updateWidget();
    m_button->applyPreset(Material::FlatPreset);
}

void FlatButtonSettingsEditor::applyCheckablePreset()
{
    ui->buttonRoleComboBox->setCurrentIndex(0);
    ui->rippleStyleComboBox->setCurrentIndex(1);
    ui->iconPlacementComboBox->setCurrentIndex(0);
    ui->hoverStyleComboBox->setCurrentIndex(2);
    ui->textAlignmentComboBox->setCurrentIndex(1);
    ui->transparentCheckBox->setChecked(true);
    ui->cornerRadiusSpinBox->setValue(3);
    ui->overlayOpacityDoubleSpinBox->setValue(0.13);
    ui->fontSizeDoubleSpinBox->setValue(10);
    ui->useThemeColorsCheckBox->setChecked(true);
    ui->showHaloCheckBox->setChecked(true);
    ui->checkableCheckBox->setChecked(true);
    ui->disabledCheckBox->setChecked(false);
    updateWidget();
    m_button->applyPreset(Material::CheckablePreset);
}

void FlatButtonSettingsEditor::init()
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

    m_button->setFixedWidth(300);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    layout->addWidget(m_button);
    layout->setAlignment(m_button, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->checkableCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->checkedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->showHaloCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->iconCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->transparentCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->buttonRoleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->rippleStyleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->hoverStyleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->iconPlacementComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->textAlignmentComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->cornerRadiusSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->overlayOpacityDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui->iconSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->fontSizeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui->buttonTextLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->foregroundColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->backgroundColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->disabledFgColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->disabledBgColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->overlayColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->cornerRadiusSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->overlayOpacityDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui->iconSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->fontSizeDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidget()));
    connect(ui->buttonTextLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(ui->defaultPresetPushButton, SIGNAL(pressed()), this, SLOT(applyDefaultPreset()));
    connect(ui->checkablePresetPushButton, SIGNAL(pressed()), this, SLOT(applyCheckablePreset()));
    connect(m_button, SIGNAL(clicked(bool)), ui->checkedCheckBox, SLOT(setChecked(bool)));

    ui->buttonRoleComboBox->setCurrentIndex(1);
}
