#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QWidget>
#include "ui_calibration.h"

class CalibrationUi : public QWidget, public Ui::Calibration
{
    Q_OBJECT

public:
    explicit CalibrationUi(QWidget *parent = 0);

private:
};

#endif // CALIBRATION_H
