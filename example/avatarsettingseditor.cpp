#include "avatarsettingseditor.h"
#include <QColorDialog>
#include <qtmaterialavatar.h>
#include <lib/qtmaterialtheme.h>

AvatarSettingsEditor::AvatarSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::AvatarSettingsForm),
      m_avatar(new QtMaterialAvatar(QChar('X')))
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
    layout->addWidget(m_avatar);
    layout->setAlignment(m_avatar, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->sizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->typeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->backgroundColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->textColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    ui->sizeSpinBox->setRange(5, 300);
}

AvatarSettingsEditor::~AvatarSettingsEditor()
{
    delete ui;
}

void AvatarSettingsEditor::setupForm()
{
    switch (m_avatar->type())
    {
    case Material::LetterAvatar:
        ui->typeComboBox->setCurrentIndex(0);
        break;
    case Material::ImageAvatar:
        ui->typeComboBox->setCurrentIndex(1);
        break;
    case Material::IconAvatar:
        ui->typeComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    ui->disabledCheckBox->setChecked(!m_avatar->isEnabled());
    ui->useThemeColorsCheckBox->setChecked(m_avatar->useThemeColors());
    ui->sizeSpinBox->setValue(m_avatar->size());
}

void AvatarSettingsEditor::updateWidget()
{
    switch (ui->typeComboBox->currentIndex())
    {
    case 0:
        m_avatar->setLetter(QChar('X'));
        break;
    case 1:
        m_avatar->setImage(QImage(":/images/assets/sikh.jpg"));
        break;
    case 2:
        m_avatar->setIcon(QtMaterialTheme::icon("communication", "message"));
        break;
    default:
        break;
    }

    m_avatar->setDisabled(ui->disabledCheckBox->isChecked());
    m_avatar->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_avatar->setSize(ui->sizeSpinBox->value());
}

void AvatarSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("textColorToolButton" == senderName) {
            m_avatar->setTextColor(color);
            ui->textColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("backgroundColorToolButton" == senderName) {
            m_avatar->setBackgroundColor(color);
            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
