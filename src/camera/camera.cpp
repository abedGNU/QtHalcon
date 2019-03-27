#include "camera.h"

/**
 * @brief
 * @param
 * @return
 * @todo
 */
Camera::Camera()
{

}

/**
 * @brief Camera::Camera
 * @param deviceName :
 * @param cameraName :
 * @param interfac :
 */
Camera::Camera(QString deviceName, QString cameraName, QString interfac, QString cameraType , Global::eCamOEM camOem)
{
    try
    {
        this->interfac= interfac;
        this->deviceName=deviceName;
        this->cameraName = cameraName;
        this->cameraType=cameraType;
        setCamOem (camOem);
        openCamera();

    }
    catch(HalconCpp::HException& ex)
    {
        Global::HExceptio(ex);
    }
}

/**
 * @brief Camera::Camera like Halcon openframgrabber signature
 * @param
 * @return
 * @todo
 * @date
 */
Camera::Camera(const HalconCpp::HString &Name, Hlong HorizontalResolution, Hlong VerticalResolution, Hlong ImageWidth, Hlong ImageHeight,
               Hlong StartRow, Hlong StartColumn, const HalconCpp::HString &Field, const HalconCpp::HTuple &BitsPerChannel, const HalconCpp::HTuple &ColorSpace,
               const HalconCpp::HTuple &Generic, const HalconCpp::HString &ExternalTrigger, const HalconCpp::HTuple &CameraType,
               const HalconCpp::HTuple &Device, const HalconCpp::HTuple &Port, const HalconCpp::HTuple &LineIn)
{
    qDebug()<< interfac.toStdString().c_str() <<  cameraType.toStdString().c_str()<< deviceName.toStdString().c_str();

    //        HalconCpp::HString Name =interfac.toStdString().c_str();
    //        Hlong HorizontalResolution=0; Hlong VerticalResolution=0;
    //        Hlong ImageWidth=0; Hlong ImageHeight=0; Hlong StartRow=0; Hlong StartColumn=0;

    //        HalconCpp::HString Field="default"; HalconCpp::HTuple BitsPerChannel=-1;  HalconCpp::HTuple ColorSpace="default";  HalconCpp::HTuple Generic=-1;
    //        HalconCpp::HString ExternalTrigger="false";

    //        HalconCpp::HTuple CameraType=cameraType.toStdString().c_str();  HalconCpp::HTuple Device=deviceName.toStdString().c_str();

    //        HalconCpp::HTuple Port=0;  HalconCpp::HTuple LineIn=-1;
    this->OpenFramegrabber(  Name,  HorizontalResolution,  VerticalResolution,
                             ImageWidth,  ImageHeight,  StartRow,  StartColumn,   Field,
                             BitsPerChannel,   ColorSpace,   Generic,   ExternalTrigger,
                             CameraType,   Device,
                             Port,   LineIn);
}

/**
 * @brief
 * @param
 * @return
 * @todo
 * @date
 */
void Camera::openCamera()
{
    try
    {
    //this->OpenFramegrabber("File",1,1,0,0,0,0,"default",-1,"default",-1,"default",
    //                  "board/board.seq","default",-1,1);
    this->OpenFramegrabber(interfac.toStdString().c_str(),0,0,0,0,0,0,
                           "default",-1,"default",-1,"false",
                           cameraType.toStdString().c_str(),
                           deviceName.toStdString().c_str(),0,-1);
    }
    catch(HalconCpp::HException& ex)
    {
        Global::HExceptio(ex);
    }
}


/**
 * @brief
 * @param
 * @return
 * @todo
 * @date
 */
void Camera::setExpTime(int expTime)
{
    if ( cameraPar.expTime!= expTime)
    {
        cameraPar.prevExpTime = cameraPar.expTime ;
        cameraPar.expTime = expTime;
        this->SetFramegrabberParam( cameraPar.expParamName.toStdString().c_str(), QString::number(expTime).toStdString().c_str());
    }
}

/**
 * @brief
 * @param
 * @return
 * @todo
 */
void Camera::setCamOem(Global::eCamOEM camOem)
{
    if (camOem == Global::eCamOEM::eBasler )
    {
        cameraPar.expParamName="ExposureTimeAbs";
    }
    else
    {
        cameraPar.expParamName="ExposureTime";
    }
    this->camOem=camOem;
}

/**
 * @brief
 * @param
 * @return
 * @todo
 */
Global::eCamOEM Camera::getCamOem()
{
    return this->camOem;
}




