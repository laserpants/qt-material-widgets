#include "iconbuttonsettingseditor.h"
#include <QColorDialog>
#include <lib/qtmaterialtheme.h>
#include <qtmaterialiconbutton.h>

IconButtonSettingsEditor::IconButtonSettingsEditor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IconButtonSettingsForm)
    , m_button(new QtMaterialIconButton(QtMaterialTheme::icon("toggle", "star")))
{
    init();
}

IconButtonSettingsEditor::~IconButtonSettingsEditor()
{
    delete ui;
}

IconButtonSettingsEditor::IconButtonSettingsEditor(QtMaterialIconButton *button, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IconButtonSettingsForm)
    , m_button(button)
{
    init();
}

void IconButtonSettingsEditor::setupForm()
{
    ui->disabledCheckBox->setChecked(!m_button->isEnabled());
    ui->useThemeColorsCheckBox->setChecked(m_button->useThemeColors());
    ui->sizeSpinBox->setValue(m_button->iconSize().width());
}

void IconButtonSettingsEditor::updateWidget()
{
    m_button->setDisabled(ui->disabledCheckBox->isChecked());
    m_button->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_button->setIconSize(QSize(ui->sizeSpinBox->value(), ui->sizeSpinBox->value()));
}

void IconButtonSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("colorToolButton" == senderName) {
            m_button->setColor(color);
            ui->colorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("disabledColorToolButton" == senderName) {
            m_button->setDisabledColor(color);
            ui->disabledColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}

void IconButtonSettingsEditor::init()
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
    layout->addWidget(m_button);
    layout->setAlignment(m_button, Qt::AlignCenter);

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->colorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->disabledColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->sizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
}
