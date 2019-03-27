#ifndef CALIBRATIONUI_H
#define CALIBRATIONUI_H

#include <QWidget>
#include <HalconCpp.h>
#include <qhwindow.h>
#include <QFileDialog>
#include <QTextCodec>
#include <camera.h>
#include "global.h"
#include "explorer.h"

#include "ui_calibrationui.h"


class CalibrationUi : public QWidget, public Ui::CalibrationUi
{
    Q_OBJECT

public:
    explicit CalibrationUi(QWidget *parent = 0);


    void on_pb_calibrate_clicked();
    QHWindow *hwind;

    HalconCpp::HImage image;
    HalconCpp::HCalibData caltemp;
    HalconCpp::HTuple StartCamPar;
    HalconCpp::HXLDCont calcont;
    HalconCpp::HFramegrabber framegrab;


    double Focus, Kappa, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight;
    QString calibname, fileNameDescr;
    char caltab;




    void calibrationset();
    void calibration(int i);
private slots:
    void on_pb_readcalibrationfile_clicked();

    void on_pbGrab_clicked();

    void on_pb_calibration_clicked();

private:
};

#endif // CALIBRATIONUI_H
