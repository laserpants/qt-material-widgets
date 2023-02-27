#include "badgesettingseditor.h"
#include <QColorDialog>
#include <qtmaterialavatar.h>
#include <qtmaterialbadge.h>

BadgeSettingsEditor::BadgeSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::BadgeSettingsForm),
      m_avatar(new QtMaterialAvatar(QImage(":/images/assets/sikh.jpg"))),
      m_badge(new QtMaterialBadge)
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
    m_avatar->setSize(60);

    m_badge->setParent(m_avatar);
    m_badge->setRelativePosition(18, 18);
    m_badge->setText("3");

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->typeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->horizontalOffsetSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->verticalOffsetSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->backgroundColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->textColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    ui->verticalOffsetSpinBox->setRange(-40, 40);
    ui->horizontalOffsetSpinBox->setRange(-40, 40);
}

BadgeSettingsEditor::~BadgeSettingsEditor()
{
    delete ui;
}

void BadgeSettingsEditor::setupForm()
{
    if (m_badge->icon().isNull()) {
        ui->typeComboBox->setCurrentIndex(0);
    } else {
        ui->typeComboBox->setCurrentIndex(1);
    }

    ui->verticalOffsetSpinBox->setValue(m_badge->relativeYPosition());
    ui->horizontalOffsetSpinBox->setValue(m_badge->relativeXPosition());
    ui->disabledCheckBox->setChecked(!m_badge->isEnabled());
    ui->useThemeColorsCheckBox->setChecked(m_badge->useThemeColors());
}

void BadgeSettingsEditor::updateWidget()
{
    switch (ui->typeComboBox->currentIndex())
    {
    case 0:
        m_badge->setText("3");
        break;
    case 1:
        m_badge->setIcon(QIcon(QtMaterialTheme::icon("communication", "message")));
        break;
    default:
        break;
    }

    m_badge->setRelativeYPosition(ui->verticalOffsetSpinBox->value());
    m_badge->setRelativeXPosition(ui->horizontalOffsetSpinBox->value());
    m_badge->setDisabled(ui->disabledCheckBox->isChecked());
    m_badge->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void BadgeSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("textColorToolButton" == senderName) {
            m_badge->setTextColor(color);
            ui->textColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("backgroundColorToolButton" == senderName) {
            m_badge->setBackgroundColor(color);
            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
