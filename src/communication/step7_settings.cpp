#include "step7_settings.h"
#include "ui_step7_settings.h"

step7_Settings::step7_Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::step7_Settings)
{
    ui->setupUi(this);
}

step7_Settings::~step7_Settings()
{
    delete ui;
}
