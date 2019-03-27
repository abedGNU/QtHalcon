#ifndef GLOBAL_H
#define GLOBAL_H

#include <QList>
#include <QDebug>
#include <QException>
#include "HalconCpp.h"
//#include "camera.h"


namespace Global {

enum eDrawShape{eRectangle, eRectangleOrient, eCircle, eEllipse, ePolygon, eFreeHand};
enum eCamOEM {eBasler, eDaheng, eHikVision};
enum eCameraModel{ area_scan_division=1, area_scan_polynomial,
                   area_scan_telecentric_division,  area_scan_telecentric_polynomial,
                   area_scan_telecentric_tilt_division,area_scan_telecentric_tilt_polynomial,
                   area_scan_tilt_division,area_scan_tilt_polynomial,line_scan};

enum efileCreate {eErr, eCreated, eExist};

struct camInternalParam
{
 double Focus, Kappa, Sx, Sy, Cx, Cy, ImageWidth, ImageHeight;
};

struct HPointD
{
    double x;
    double y ;
    double z;
};

// watch the eCameraModel begin from 1 not 0
extern QList<QString> CameraModels;

extern QString camActFile;
//extern QList<Camera> ActiveCameras;
//extern QHash<QString,Camera> ActiveCamera;

extern QString repDirLoc;

extern QString  repDirName ;
extern QString  repDir ;

extern QString  repvisDirName ;
extern QString  repVisDir ;

extern QString camDirName;
extern QString camDir;

extern QString modelDirName;
extern QString modelDir;

extern QString jobDirName;
extern QString jobDir;

extern QString activeCamLsit;
extern QString activeModelsList;
extern QString activeJobsList;

extern QString settFile;
extern QString settVisFile;

extern QString camInfoFile;

void HExceptio(HalconCpp::HException& ex);
void QExceptio(QException& ex);

void debugRepDirs();

}
#endif // GLOBAL_H
