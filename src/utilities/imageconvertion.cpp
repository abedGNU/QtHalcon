#include "imageconvertion.h"

ImageConvertion::ImageConvertion()
{

}

QImage ImageConvertion::HImage2QImage(HalconCpp::HObject &hobj)
{
    QImage qImage;
    HalconCpp::HTuple width, height, channels, typ, ptr;
    uchar *ptr1;

    //ConvertImageType(hobj, &hobj, "byte");
    //HalconCpp::GetImageSize(hobj, &width, &height);
    HalconCpp::CountChannels(hobj, &channels);
    HalconCpp::GetImagePointer1(hobj, &ptr,&typ,&width,&height);
    qDebug() << "image type" << typ.ToString();
    qDebug() << "image width" << width.ToString() << "image height" << height.ToString();
    qDebug() << "ptr" << ptr.ToString();

    ptr1 = (uchar*)ptr.I();
    if(channels.I() == 1)// gray scale image
    {
        return QImage(ptr1, width,height, QImage::Format_Grayscale8);
    }
    else if (channels.I() ==3) // RGB image
    {
        return QImage(ptr1, width,height, QImage::Format_RGB888);
    }
    return qImage;
}
