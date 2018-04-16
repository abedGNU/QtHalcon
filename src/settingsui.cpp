#include "settingsui.h"


SettingsUi::SettingsUi(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    plc7Setting = new step7_Settings(tabCommunication);
    plc7Setting->show();
}

