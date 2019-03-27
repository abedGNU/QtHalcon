#include "global.h"

namespace Global {

// watch the eCameraModel begin from 1 not 0
QList<QString> CameraModels{"area_scan_division", "area_scan_polynomial",
                            "area_scan_telecentric_division", "area_scan_telecentric_polynomial",
                            "area_scan_telecentric_tilt_division", "area_scan_telecentric_tilt_polynomial",
                            "area_scan_tilt_division", "area_scan_tilt_polynomial", "line_scan"};

QString camActFile = "activeCameras";
//QList<Camera> ActiveCameras;
//QHash<QString,Camera> ActiveCamera;

QString repDirLoc="";

QString repDirName="dataRep";
QString repDir= "/"+repDirName ;

QString repvisDirName="vision";
QString repVisDir=repDir + "/" + repvisDirName;

QString camDirName = "cameras";
QString camDir = repVisDir+"/"+camDirName;

QString modelDirName ="models";
QString modelDir =repVisDir+"/"+modelDirName;

QString jobDirName="jobs";
QString jobDir =repVisDir+"/"+jobDirName;

QString activeCamLsit ="";
QString activeModelsList ="";
QString activeJobsList ="";

QString settFile="";
QString settVisFile="";

QString camInfoFile= "cameraInfo.tup";

void HExceptio(HalconCpp::HException& ex)
{
    qDebug() << ex.ErrorCode() << ex.ErrorMessage();
}

void QExceptio(QException& ex)
{
    qDebug()<< ex.what();
}

void debugRepDirs()
{
   qDebug()<<"" << repDir;
   qDebug()<<"" << repVisDir;
   qDebug()<<"" << camDir;
   qDebug()<<"" << modelDir;
   qDebug()<<"" << jobDir;
}

}//Global
