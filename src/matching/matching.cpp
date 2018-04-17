#include "matching.h"
#include <QDebug>
#include <QException>

MatchingUi::MatchingUi(QWidget *parent) :
    QWidget(parent)
{
    try{
        setupUi(this);
        hwind = new QHWindow();
        vlHwindows->addWidget(hwind);

        initValues();
        connect(pbAddRoi,SIGNAL(clicked()), this, SLOT(mouseClicked()) );
        connect(pbDeleteRoi, SIGNAL(clicked()), this, SLOT(mouseClicked())  );
        connect(hwind, SIGNAL(mouseClic()), this, SLOT(mouseClicked() ) );
        //connect(spinBoxtest,&spinBoxtest::valueChanged,
        //      [=](){test1=spinBoxtest->value(); }   );

        hwind->show();
    }
    catch( QException &e)
    {
        qDebug()<< e.what();
    }
}


void MatchingUi::on_pbGrabImage_clicked()
{
    roiAddActive = roiCutActive = false;
    imgGrabbed.ReadImage("Matchimage");
    selectedRegion.GenEmptyObj();
    clearAndShow();

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
    roiAddActive= roiCutActive=false;
    regionCounter=0;
    HalconCpp::HRegion gridRegion; gridRegion.GenGridRegion(10,10,"points",(Hlong)imgGrabbed.Width(), (Hlong)imgGrabbed.Height() );
    hwind->SetColor("dim gray");
    hwind->DispObj(gridRegion);

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
    try{
        if(imgGrabbed.IsInitialized())
        {
            selectedRegion.GenEmptyObj();
            selectedRegion.GenRectangle1(0,0, (double)imgGrabbed.Height(), (double)imgGrabbed.Width());
            clearAndShow();
            regionCounter=1;
            inspectModel();
        }
        roiAddActive= roiCutActive=false;
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug() << ex.ErrorCode() << ex.ErrorMessage();
    }
}

void MatchingUi::mouseClicked()
{
    try
    {
        if((roiCutActive | roiAddActive) & !drawActive)
        {
            drawActive = true;
            //
            regionCounter++;
            qDebug()<< "Region No. " << regionCounter;
            HalconCpp::HRegion regTemp = drawShape(Global::eDrawShape(cmbRoiShape->currentIndex()));
            lstRegions.append(&regTemp);
            //
            drawActive = false;
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
            clearAndShow();
            HalconCpp::HRegion gridRegion; gridRegion.GenGridRegion(10,10,"points",(Hlong)imgGrabbed.Width(), (Hlong)imgGrabbed.Height() );
            HalconCpp::Difference(gridRegion, selectedRegion, &gridRegion);
            hwind->SetColor("dim gray");
            hwind->DispObj(gridRegion);
            inspectModel();
        }
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug()<< ex.ErrorCode()<< " " << ex.ErrorMessage();
    }
}

void MatchingUi::on_pbOkRoi_clicked()
{
    try{
        roiAddActive= roiCutActive=false;
        createModel();
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug() << ex.ErrorCode() << ex.ErrorMessage();
    }
}

void MatchingUi::on_pbUndoRoi_clicked()
{
    try{
        if (regionCounter>=1){
            /*
            regionCounter--;
            selectedRegion.GenEmptyObj();
            selectedRegion= lstRegions.at(regionCounter-1)->Clone();
            clearAndShow();
            */
        }
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug()<< ex.ErrorCode() << ex.ErrorMessage();
    }
}


void MatchingUi::clearAndShow()
{
    try{
        hwind->ClearWindow();
        if (imgGrabbed.IsInitialized())
            hwind->showImage(imgGrabbed);
        if (selectedRegion.IsInitialized())
            hwind->DispObj(selectedRegion);
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug() << ex.ErrorCode() << ex.ErrorMessage();
    }
}

void MatchingUi::clearAndShow(int arg1)
{
    try{
        hwind->ClearWindow();
        if (imgGrabbed.IsInitialized() & ((arg1==1) | (arg1==3) ))
            hwind->showImage(imgGrabbed);
        if (selectedRegion.IsInitialized() & ((arg1==2) | (arg1==3)))
            hwind->DispObj(selectedRegion);
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug() << ex.ErrorCode() << ex.ErrorMessage();
    }
}

void MatchingUi::initValues()
{
    spinUpperThreshold->setValue(20);
    spinLowerThreshold->setValue(10);

    spinBoxMinSize->setValue(30);

    contrast[0]=10; contrast[1]=20; contrast[2]=30;
}

void MatchingUi::inspectModel()
{
    try{
        if(imgGrabbed.IsInitialized() & selectedRegion.IsInitialized())
        {
            imgReduced= imgGrabbed.ReduceDomain(selectedRegion);
            imgReduced.InspectShapeModel(&modelRegion,1,contrast);
            hwind->SetColor("green");
            hwind->DispObj(modelRegion);
        }
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug() << ex.ErrorCode() << ex.ErrorMessage();
    }
}

void MatchingUi::createModel()
{
    try{
        // if (shapeModel.InvalidateHandle())
        {
            //const HTuple& NumLevels, double AngleStart, double AngleExtent, const HTuple& AngleStep,
            //double ScaleMin, double ScaleMax, const HTuple& ScaleStep, const HTuple& Optimization,
            //const HString& Metric, const HTuple& Contrast, const HTuple& MinContrast) const;
            shapeModel= imgReduced.CreateScaledShapeModel(numLevels, angleStart, angleExtent,
                                                          angleStep, scaleMin, scaleMax,
                                                          scaleStep, optimization, metric, contrast, minContrast);
        }
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug() << ex.ErrorCode() << ex.ErrorMessage();
    }

}

void MatchingUi::findModel()
{
    try{
        HalconCpp::HTuple numLevel =0;
        shapeModel.FindScaledShapeModel(imgGrabbed,angleStart, angleExtent,
                                        scaleMin, scaleMax, minScore,numMatches,
                                        maxOverlap, subPixel, numLevel, greediness,
                                        &row, &col, &angle, &scale, &score);

        HalconCpp::HXLDCont xldCont =shapeModel.GetShapeModelContours(1);
        // tranfermo to new position
        /*
        vector_angle_to_rigid (0, 0, 0, Row[I], Column[I], Angle[I], HomMat2DRotate)
        hom_mat2d_scale (HomMat2DRotate, Scale[I], Scale[I], Row[I], Column[I], HomMat2DScale)
        affine_trans_contour_xld (ModelContours, ModelTrans, HomMat2DScale)
        */
        qDebug()<< "Number of matches= " << score.Length();
        if (score.Length())
        {
            HalconCpp::HHomMat2D matrix;
            matrix.HomMat2dIdentity();

            HalconCpp::HTuple xldRow=0, xldCol=0, xldAngle=0;
            for(int i=0;score.Length()-1; i++)
            {
                matrix.VectorAngleToRigid((double)xldRow[i],xldCol[i],xldAngle[i], row[i], col[i], angle[i]);
                matrix = matrix.HomMat2dScale((double)scale[i],scale[i],row[i],col[i]);
                xldCont=matrix.AffineTransContourXld(xldCont);

                clearAndShow(1);
                hwind->DispObj(xldCont);
            }
        }
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug() << ex.ErrorCode() << ex.ErrorMessage();
    }

}



void MatchingUi::on_spinLowerThreshold_valueChanged(int arg1)
{
    if (arg1 >= spinUpperThreshold->value())
    {
        spinLowerThreshold->setValue(spinUpperThreshold->value()-1);
        return;
    }
    contrast[0]=arg1;
    clearAndShow();
    inspectModel();
}

void MatchingUi::on_spinUpperThreshold_valueChanged(int arg1)
{
    if (arg1 <=spinLowerThreshold->value() )
    {
        spinUpperThreshold->setValue(spinLowerThreshold->value()+1);
        return;
    }
    contrast[1]=arg1;
    clearAndShow();
    inspectModel();
}

void MatchingUi::on_spinBoxMinSize_valueChanged(int arg1)
{
    contrast[2]=arg1;
    inspectModel();
}

void MatchingUi::on_pbFindModel_clicked()
{
    findModel();
}


void MatchingUi::on_spinStartAngle_valueChanged(int arg1)
{
    if(arg1 >= spinEndAngle->value())
    {
        spinStartAngle->setValue(spinEndAngle->value()-1);
        return;
    }
    angleStart = qDegreesToRadians( (double)spinStartAngle->value() );
}

void MatchingUi::on_spinEndAngle_valueChanged(int arg1)
{
    if(arg1<=spinStartAngle->value())
    {
        spinEndAngle->setValue(spinStartAngle->value()+1);
        return;
    }
    angleExtent = qDegreesToRadians ((double)spinEndAngle->value());
}

void MatchingUi::on_spinStepAngle_valueChanged(int arg1)
{

    if (arg1 == 0)
    {
        angleStep = HAuto;
    }
    else
    {
        angleStep = qDegreesToRadians((double)arg1);
    }
}

void MatchingUi::on_spinMinScale_valueChanged(int arg1)
{
    scaleMin = arg1/100.0;
}

void MatchingUi::on_spinMaxScale_valueChanged(int arg1)
{
    scaleMax = arg1/100.0;
}

void MatchingUi::on_spinMinScore_valueChanged(int arg1)
{
    minScore = arg1/100.0;
}

void MatchingUi::on_spinNumMatchs_valueChanged(int arg1)
{
    numMatches = (Hlong)arg1;
}

void MatchingUi::on_spinMaxOverlap_valueChanged(int arg1)
{
    maxOverlap = arg1/100.0;
}

void MatchingUi::on_spinGreediness_valueChanged(int arg1)
{
    greediness = arg1/100.0;
}

void MatchingUi::on_cobSubpixel_currentIndexChanged(const QString &arg1)
{
    subPixel[0] = arg1.toStdString().c_str();
    qDebug()<< arg1;
}
