#ifndef STEP7_SETTINGS_H
#define STEP7_SETTINGS_H

#include <QWidget>

namespace Ui {
class step7_Settings;
}

class step7_Settings : public QWidget
{
    Q_OBJECT

public:
    explicit step7_Settings(QWidget *parent = 0);
    ~step7_Settings();

private:
    Ui::step7_Settings *ui;
};

#endif // STEP7_SETTINGS_H
