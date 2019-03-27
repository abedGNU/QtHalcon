#ifndef IMAGECONVERTION_H
#define IMAGECONVERTION_H

#include <QImage>
#include <QDebug>

#include "HalconCpp.h"


class ImageConvertion
{
public:
    ImageConvertion();
    static QImage HImage2QImage(HalconCpp::HObject &hobj);

    static HalconCpp::HObject QImage2Himage();
};

#endif // IMAGECONVERTION_H
