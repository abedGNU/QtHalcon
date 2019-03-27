#include "matchingui.h"
#include <QDebug>
#include <QException>
#include <QFile>

MatchingUi::MatchingUi(QWidget *parent) :
    QWidget(parent)
{
    try{
        setupUi(this);
        hwind = new QHWindow();
        vlHwindows->addWidget(hwind);

        initValues(false);

        connect(pbAddRoi,SIGNAL(clicked()), this, SLOT(mouseClicked()) );
        connect(pbDeleteRoi, SIGNAL(clicked()), this, SLOT(mouseClicked())  );
        connect(hwind, SIGNAL(mouseClic()), this, SLOT(mouseClicked() ) );
        //connect(spinBoxtest,&spinBoxtest::valueChanged,
        //      [=](){test1=spinBoxtest->value(); }   );

        hwind->show();
        cmbCamera->addItems(Explorer::ActiveCamera.keys());
    }
    catch( QException &e)
    {
        qDebug()<< e.what();
    }
}


void MatchingUi::on_pbGrabImage_clicked()
{
    roiAddActive = roiCutActive = false;
   // imgGrabbed.ReadImage("green-dot");
    imgGrabbed = Explorer::ActiveCamera.value(cmbCamera->currentText())->GrabImage() ;
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
        Global::HExceptio(ex);
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

void MatchingUi::initValues(bool readModel)
{
    numLevels =HAuto;
    optimization =HAuto;
    metric="use_polarity";
    subPixel="least_squares";

    if (! readModel)
    {
        contrast[0]=10; contrast[1]=20; contrast[2]=30; minContrast =HAuto;
        angleStart = -M_PI; angleExtent = M_PI; angleStep=HAuto;
        scaleMin=0.9; scaleMax=1.1;scaleStep=HAuto;

        minScore=0.5;
        numMatches=1;
        maxOverlap=0.9;
        greediness=0.9;
    }
    // Contrast
    spinUpperThreshold->setValue(contrast[1]);
    spinLowerThreshold->setValue(contrast[0]);
    spinBoxMinSize->setValue(contrast[2]);

    // Angles
    spinStartAngle->setValue( (int)qRadiansToDegrees(angleStart) );
    spinEndAngle->setValue((int)qRadiansToDegrees(angleExtent));
    if (angleStep==HAuto)
        spinStepAngle->setValue(0);

    // Scale
    spinMinScale->setValue( (int)(scaleMin*100) );
    spinMaxScale->setValue((int)(scaleMax*100));

    // Min  Score
    spinMinScore->setValue((int)(minScore*100));

    // Number of matches
    spinNumMatchs->setValue(numMatches);

    // max overlap
    spinMaxOverlap->setValue((int)(maxOverlap*100));
    // Greediness
    spinGreediness->setValue((int)(greediness*100));

    // subpixel
    cmbSubpixel->setCurrentText("least_squares");
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
            qDebug()<< "Model created" << "NumLevels="<<numLevels.ToString()
                    << " Angle start " << qRadiansToDegrees(angleStart) << " angleExtent=" << qRadiansToDegrees(angleExtent)
                    << " angleStep=" << angleStep.ToString() << " scaleMin="<< scaleMin << " scaleMax " << scaleMax
                    << " scaleStep=" << scaleStep.ToString() <<  " optimization=" << optimization.ToString()
                    << " metric=" << metric.Text() << " contrast="<< contrast.ToString() <<" minContrast=" << minContrast.ToString();
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
        qDebug()<< " Angle start " << qRadiansToDegrees(angleStart) << " angleExtent=" << qRadiansToDegrees(angleExtent)
                << " scaleMin="<< scaleMin << " scaleMax " << scaleMax
                << "minScore="<<minScore<< "numMatches="<<numMatches
                <<"maxOverlap="<<maxOverlap<< "subPixel"<<subPixel.ToString()
               << "numLevel="<<numLevel.ToString()<<"greediness="<< greediness
               <<"row=" <<row.ToString() << "col="<<col.ToString()<< "angle="<< angle.ToString()
              << "scale="<< scale.ToString()<< "score="<< score.ToString();

        HalconCpp::HXLDCont xldCont =shapeModel.GetShapeModelContours(1);
        // tranfermo to new position
        /*
        vector_angle_to_rigid (0, 0, 0, Row[I], Column[I], Angle[I], HomMat2DRotate)
        hom_mat2d_scale (HomMat2DRotate, Scale[I], Scale[I], Row[I], Column[I], HomMat2DScale)
        affine_trans_contour_xld (ModelContours, ModelTrans, HomMat2DScale)
        */
        qDebug()<< "Number of matches found= " << score.Length();
        // hwind->DispObj(xldCont);
        clearAndShow(1);
        if (score.Length()>0)
        {
            HalconCpp::HHomMat2D matrix;
            matrix.HomMat2dIdentity();

            HalconCpp::HTuple xldRow=0, xldCol=0, xldAngle=0;
            for(int i=0;i < score.Length(); i++)
            {
                matrix.VectorAngleToRigid((double)xldRow[i],xldCol[i],xldAngle[i], row[i], col[i], angle[i]);
                matrix = matrix.HomMat2dScale((double)scale[i],scale[i],row[i],col[i]);
                HalconCpp::HXLDCont xldContTrans=matrix.AffineTransContourXld(xldCont);

                hwind->DispObj(xldContTrans);
            }
        }
    }
    catch(HalconCpp::HException &ex)
    {
        qDebug() << ex.ErrorCode() << ex.ErrorMessage();
    }

}

void MatchingUi::writeModel()
{
    shapeModel.WriteShapeModel(modelFullName.toStdString().c_str());
    qDebug()<< "model Saved in : " << modelFullName;
    //
    imgGrabbed.WriteImage(imgExt.toStdString().c_str(),0, imgFullName.toStdString().c_str() );
    imgReduced.WriteImage(imgExt.toStdString().c_str(),0,imgReducedFullName.toStdString().c_str());
    selectedRegion.WriteRegion(regionFullName.toStdString().c_str());
}

void MatchingUi::readModel()
{
    if(QFile::exists(modelFullName) )
    {
        shapeModel.ReadShapeModel(modelFullName.toStdString().c_str());
        qDebug() << "Read model file " << modelFullName;

        double rowRefModel, colRefModel;
        shapeModel.GetShapeModelOrigin(&rowRefModel, &colRefModel);
        double angleStepD, scaleStepD;
        Hlong minContrastL;
        // GetShapeModelParams(double* AngleStart, double* AngleExtent, double* AngleStep,
        //double* ScaleMin, double* ScaleMax, double* ScaleStep, HString* Metric, Hlong* MinContrast) const;
        shapeModel.GetShapeModelParams(&angleStart, &angleExtent, &angleStepD,
                                       &scaleMin, &scaleMax, &scaleStepD,
                                       &metric, &minContrastL);
        angleStep = angleStepD;
        scaleStep = scaleStepD;
        minContrast=minContrastL;
        initValues(true);
        qDebug()<< " Angle start " << qRadiansToDegrees(angleStart) << " angleExtent=" << qRadiansToDegrees(angleExtent)
                << " angleStep=" << angleStepD << " scaleMin="<< scaleMin << " scaleMax " << scaleMax
                << " scaleStep=" << scaleStepD
                << " metric=" << metric.Text() <<" minContrast=" << minContrastL;
    }
    else
        qDebug()<< "File" << modelFullName << " dosen't exist";

    if (QFile::exists(imgFullNameExt))
    {
        imgGrabbed.ReadImage( imgFullName.toStdString().c_str() );
        qDebug() << "Read image from" << imgFullNameExt;

    }
    if (QFile::exists(imgReducedFullNameExt))
    {
        imgReduced.ReadImage(imgReducedFullName.toStdString().c_str());
         qDebug() << "Read reduced image from" << imgReducedFullNameExt;
    }
    if(QFile::exists(regionFullNameExt))
    {
        selectedRegion.ReadRegion(regionFullName.toStdString().c_str());
          qDebug() << "Read region from" << regionFullNameExt;
    }
    clearAndShow();
    inspectModel();
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

void MatchingUi::on_pushButton_clicked()
{
    writeModel();
}

void MatchingUi::on_pbReadModelFile_clicked()
{
    readModel();
}
