#ifndef CAMARAPARAM_H
#define CAMARAPARAM_H

#include <QList>
#include <QString>
#include "HalconCpp.h"
#include "global.h"

class CameraParam
{
public:
    CameraParam();
    CameraParam(QString camDir);

    /*
     * Functions
     * */
    int readParam();
    int readParam(QString camDir);

    int writeParam();
    int writeParam(QString camDir);

    /*
     * Variables
     * */
    QString cameraName;
    HalconCpp::HTuple camParIntern, camParExt;
    QString camRepDir;


    Global::eCameraModel cameraModel;
    double Focus, Kappa, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight;
    Global::camInternalParam interParam;

    int expTime;
    int prevExpTime;
    QList<int> expTimeLst;
    QString expParamName = "ExposureTimeAbs";

private:




};

#endif // CAMARAPARAM_H


//CameraType                                CameraParam                                                                      #
//"area_scan_division"                      [Focus, Kappa, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight]                             8
//"area_scan_telecentric_division"           [0, Kappa, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight]                                 8
//"area_scan_tilt_division"                 [Focus, Kappa, Tilt, Rot, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight]                  10
//"area_scan_telecentric_tilt_division" 	[0, Kappa, Tilt, Rot, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight]                  10
//"area_scan_polynomial"                    [Focus, K1, K2, K3, P1, P2, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight]             12
//"area_scan_telecentric_polynomial"        [0, K1, K2, K3, P1, P2, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight]                    12
//"area_scan_tilt_polynomial"                [Focus, K1, K2, K3, P1, P2, Tilt, Rot, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight]	 14
//"area_scan_telecentric_tilt_polynomial"	[0, K1, K2, K3, P1, P2, Tilt, Rot, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight]         14
//"line_scan"                               [Focus, Kappa, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight, Vx, Vy, Vz]                 11
