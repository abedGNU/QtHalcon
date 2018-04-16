#include "qhwindow.h"

QHWindow::QHWindow(QWidget *parent, long Width, long Height) : QWidget(parent)
{
    HalconCpp::SetWindowAttr("border_width",0);
    HalconCpp::SetCheck("~father");
    this->setGeometry(0,0,Width,Height);
    OpenWindow(10,10,Width,Height,(Hlong)this->winId(),"","");
    HalconCpp::SetCheck("father");
    SetDraw("margin");
    SetColor("blue");

}

void QHWindow::showImage(HalconCpp::HImage img)
{
    try{
        if (img.IsInitialized())
        {
            SetPart(0,0, img.Height()-1, img.Width()-1);
            DispObj(img);
        }
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug()<< ex.ErrorCode() << ex.ErrorMessage();
    }
}

void QHWindow::mousePressEvent(QMouseEvent *event)
{
    emit mouseClic();
}
