#include "plugindemoform.h"
#include "ui_plugindemoform.h"

PluginDemoForm::PluginDemoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PluginDemoForm)
{
    ui->setupUi(this);
}

PluginDemoForm::~PluginDemoForm()
{
    delete ui;
}
