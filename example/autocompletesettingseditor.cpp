#include "autocompletesettingseditor.h"
#include <QVBoxLayout>
#include <QDebug>
#include <qtmaterialautocomplete.h>

AutoCompleteSettingsEditor::AutoCompleteSettingsEditor(QWidget *parent)
    : QWidget(parent),
      //ui(new Ui::AutoCompleteSettingsForm),
      m_autocomplete(new QtMaterialAutoComplete)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    canvas->setMinimumHeight(900); //

    //ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);

    QStringList states =
      { "Alabama"
      , "Alaska"
      , "American Samoa"
      , "Arizona"
      , "Arkansas"
      , "California"
      , "Colorado"
      , "Connecticut"
      , "Delaware"
      , "District of Columbia"
      , "Florida"
      , "Georgia"
      , "Guam"
      , "Hawaii"
      , "Idaho"
      , "Illinois"
      , "Indiana"
      , "Iowa"
      , "Kansas"
      , "Kentucky"
      , "Louisiana"
      , "Maine"
      , "Maryland"
      , "Massachusetts"
      , "Michigan"
      , "Minnesota"
      , "Mississippi"
      , "Missouri"
      , "Montana"
      , "Nebraska"
      , "Nevada"
      , "New Hampshire"
      , "New Jersey"
      , "New Mexico"
      , "New York"
      , "North Carolina"
      , "North Dakota"
      , "Northern Marianas Islands"
      , "Ohio"
      , "Oklahoma"
      , "Oregon"
      , "Pennsylvania"
      , "Puerto Rico"
      , "Rhode Island"
      , "South Carolina"
      , "South Dakota"
      , "Tennessee"
      , "Texas"
      , "Utah"
      , "Vermont"
      , "Virginia"
      , "Virgin Islands"
      , "Washington"
      , "West Virginia"
      , "Wisconsin"
      , "Wyoming"
    };

    m_autocomplete->setDataSource(states);

    layout->addWidget(m_autocomplete);
    layout->addSpacing(600);
    layout->setAlignment(m_autocomplete, Qt::AlignCenter);

    setupForm();
}

AutoCompleteSettingsEditor::~AutoCompleteSettingsEditor()
{
    //delete ui;
}

void AutoCompleteSettingsEditor::setupForm()
{
}

void AutoCompleteSettingsEditor::updateWidget()
{
}

void AutoCompleteSettingsEditor::selectColor()
{
}
