#include "cameraparam.h"

CameraParam::CameraParam()
{

}

int CameraParam::readParam(QString camDir)
{
    try
    {
        camRepDir = camDir;
        camParIntern = HalconCpp::HMisc::ReadCamPar(camDir.toStdString().c_str());
        if (camParIntern.Length() == 8 && cameraModel==Global::area_scan_division)
        {
            int i=0;
            Focus = camParIntern[i];
            Kappa = camParIntern[++i];
            Sx=camParIntern[++i];
            Sy =camParIntern[++i];
            Cx=camParIntern[++i];
            Cy =camParIntern[++i];
            ImageWidth=camParIntern[++i];
            ImageHeight=camParIntern[++i];
            return (int)Global::area_scan_division;
        }
        else
        {
            return -1;
        }
        return 0;
    }
    catch(HalconCpp::HException& ex)
    {
        Global::HExceptio(ex);
        return -2;
    }

}

int CameraParam::writeParam(QString camDir)
{
    try{
       // HalconCpp::HMisc::
        return 0;
    }
    catch(HalconCpp::HException& ex)
    {
        Global::HExceptio(ex);
        return -2;
    }

}
