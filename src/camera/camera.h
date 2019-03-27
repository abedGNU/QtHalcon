#ifndef CAMERA_H
#define CAMERA_H

#include <QString>
#include "HalconCpp.h"
#include "cameraparam.h"
#include "global.h"

class Camera: public HalconCpp::HFramegrabber
{
public:
    Camera();

    Camera(QString deviceName, QString cameraName="dumpName",
           QString interfac="GigEVision", QString cameraType="default",
           Global::eCamOEM camOem = Global::eCamOEM::eBasler );

    // Open and configure an image acquisition device.
    Camera(const  HalconCpp::HString& Name,  Hlong HorizontalResolution, Hlong VerticalResolution, Hlong ImageWidth, Hlong ImageHeight,
           Hlong StartRow, Hlong StartColumn, const  HalconCpp::HString& Field, const  HalconCpp::HTuple& BitsPerChannel, const  HalconCpp::HTuple& ColorSpace,
           const  HalconCpp::HTuple& Generic, const HalconCpp::HString& ExternalTrigger,
           const  HalconCpp::HTuple& CameraType, const  HalconCpp::HTuple& Device, const  HalconCpp::HTuple& Port, const  HalconCpp::HTuple& LineIn);

    ///////////////////////////////////////////////////////////////////////////////////
    void openCamera();
    void closeCamera();
    bool isConnected();
    bool isOpened();

    void setExpTime(int expTime);
    void setCamOem(Global::eCamOEM camOem);
    Global::eCamOEM getCamOem();

    //////////////////////////////////////////////////////////////////////////////////
    // "GigEVision", "File", "DirectShow", ....
    QString interfac;

    // phycical image acquisition device name.
    // "default" if interface = "File"
    QString deviceName;

    // camera name, for example if I have more than one calibration for the same device
    QString cameraName;

    // "default", or "fileName.seq" a file with image names
    QString cameraType;

    // Camera parameters
    CameraParam cameraPar;
    //QList<CameraParam> camPar;
    QHash<QString, CameraParam> camParam; // the key is the camera name

private:
    Global::eCamOEM camOem;
};

#endif // CAMERA_H
