#include "matching.h"
#include <QDebug>
#include <QException>

MatchingUi::MatchingUi(QWidget *parent) :
    QWidget(parent)
{
    try{
        setupUi(this);
        connect(pbAddRoi,SIGNAL(clicked(bool)), this, SLOT(mouseClicked()) );
        connect(pbDeleteRoi, SIGNAL(clicked()), this, SLOT(mouseClicked())  );
        connect(hwind, SIGNAL(mouseClic()), this, SLOT(mouseClicked() ) );

        hwind = new QHWindow();
        vlHwindows->addWidget(hwind);
        hwind->show();
    }
    catch( QException &e)
    {
        qDebug()<< e.what();
    }
}


void MatchingUi::on_pbGrabImage_clicked()
{
    imgGrabbed.ReadImage("Matchimage");
    hwind->showImage(imgGrabbed);

}

void MatchingUi::on_pbAddRoi_clicked()
{
    roiAddActive = !roiAddActive;
    roiCutActive =false;

}

void MatchingUi::on_pbDeleteRoi_clicked()
{
    roiCutActive = !roiCutActive;
    roiAddActive= false;
}

void MatchingUi::on_pbDeleteAll_clicked()
{
    selectedRegion.GenEmptyRegion();
    hwind->ClearWindow();

    hwind->showImage(imgGrabbed);
}

HalconCpp::HRegion MatchingUi::drawShape(Global::eDrawShape shape)
{
    Global::HPointD pt1, pt2;
    HalconCpp::HRegion regTemp;
    double phi, rad;
    try{
        if(shape== Global::eRectangle)
        {
            hwind->DrawRectangle1(&pt1.x, &pt1.y, &pt2.x, &pt2.y);
            regTemp.GenRectangle1(pt1.x, pt1.y, pt2.x, pt2.y );
        }
        else if (shape == Global::eRectangleOrient)
        {
            hwind->DrawRectangle2(&pt1.x, &pt1.y, &phi,&pt2.x, &pt2.y);
            regTemp.GenRectangle2(pt1.x, pt1.y, phi,pt2.x, pt2.y );
        }
        else if (shape == Global::eCircle)
        {
            hwind->DrawCircle(&pt1.x,&pt2.y, &rad);
            regTemp.GenCircle(pt1.x, pt2.y, rad);
        }
        else if (shape == Global::eEllipse)
        {
            hwind->DrawEllipse(&pt1.x, &pt1.y, &phi,&pt2.x, &pt2.y);
            regTemp.GenEllipse(pt1.x, pt1.y, phi,pt2.x, pt2.y );
        }
        else if (shape == Global::ePolygon)
        {
            regTemp =hwind->DrawPolygon();
        }
        else if (shape == Global::eFreeHand)
        {
            regTemp = hwind->DrawRegion();
        }
        else
        {
            return regTemp;
        }
        return regTemp;
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug()<< ex.ErrorCode() << ex.ErrorMessage();
        return regTemp;
    }

}

void MatchingUi::on_pbAddAll_clicked()
{
    if(imgGrabbed.IsInitialized())
    {
        selectedRegion.GenRectangle1(0,0, (double)imgGrabbed.Height(), (double)imgGrabbed.Width());
    }
}

void MatchingUi::mouseClicked()
{
    try
    {
        if(roiCutActive | roiAddActive)
        {
            HalconCpp::HRegion regTemp = drawShape(Global::eDrawShape(cmbRoiShape->currentIndex()));
            if (!selectedRegion.IsInitialized())
            {
                selectedRegion =  regTemp.Clone();
            }
            else
            {
                if (roiCutActive)
                    HalconCpp::Difference(selectedRegion,regTemp,&selectedRegion);
                else if (roiAddActive)
                    HalconCpp::Union2(regTemp,selectedRegion,&selectedRegion);
            }
            hwind->ClearWindow();
            hwind->showImage(imgGrabbed);
            hwind->DispObj(selectedRegion);
        }
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug()<< ex.ErrorCode()<< " " << ex.ErrorMessage();
    }
}

void MatchingUi::on_pbOkRoi_clicked()
{
    roiAddActive= roiCutActive=false;
}
