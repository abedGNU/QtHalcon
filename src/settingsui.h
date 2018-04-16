#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "ui_settings.h"

#include "step7_settings.h"

class SettingsUi : public QWidget, public Ui::settings
{
    Q_OBJECT

public:
    explicit SettingsUi(QWidget *parent = 0);
    step7_Settings *plc7Setting;

private:

};

#endif // SETTINGS_H
