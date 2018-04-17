#ifndef MATCHING_H
#define MATCHING_H

#include <QWidget>
#include <QList>
#include <QtMath>

#include "ui_matching.h"

#include "qhwindow.h"
#include "HalconCpp.h"
#include "global.h"

class MatchingUi : public QWidget, public Ui::Matching
{
    Q_OBJECT

public:
    explicit MatchingUi(QWidget *parent = 0);

    QHWindow *hwind;
    HalconCpp::HImage imgGrabbed, imgReduced;
    HalconCpp::HRegion selectedRegion;
    HalconCpp::HRegion modelRegion;
    HalconCpp::HShapeModel shapeModel;
   // int test1;

private slots:
    void on_pbGrabImage_clicked();

    void on_pbAddRoi_clicked();

    void on_pbDeleteRoi_clicked();

    void on_pbDeleteAll_clicked();

    void on_pbAddAll_clicked();

    void mouseClicked();

    void on_pbOkRoi_clicked();

    void on_pbUndoRoi_clicked();


    void on_spinLowerThreshold_valueChanged(int arg1);

    void on_spinUpperThreshold_valueChanged(int arg1);

    void on_spinBoxMinSize_valueChanged(int arg1);

    void on_pbFindModel_clicked();

    void on_spinStartAngle_valueChanged(int arg1);

    void on_spinEndAngle_valueChanged(int arg1);

    void on_spinStepAngle_valueChanged(int arg1);

    void on_spinMinScale_valueChanged(int arg1);

    void on_spinMaxScale_valueChanged(int arg1);

    void on_spinMinScore_valueChanged(int arg1);

    void on_spinNumMatchs_valueChanged(int arg1);

    void on_spinMaxOverlap_valueChanged(int arg1);

    void on_spinGreediness_valueChanged(int arg1);

    void on_cobSubpixel_currentIndexChanged(const QString &arg1);

private:
    HalconCpp::HRegion drawShape(Global::eDrawShape shape);
    bool roiAddActive=false;
    bool roiCutActive = false;
    bool drawActive=false; // draw in progress
    int regionCounter=0;
    QList<HalconCpp::HRegion*> lstRegions;

    void clearAndShow();
    void clearAndShow(int arg1);
    void initValues();

    void inspectModel();
    void createModel();
    void findModel();
    void writeModel();

    HalconCpp::HTuple HAuto = "auto";
    HalconCpp::HTuple numLevels =HAuto;
    double angleStart=-M_PI; double angleExtent=2*M_PI; HalconCpp::HTuple angleStep = HAuto;
    double scaleMin=0.9; double scaleMax=1.1; HalconCpp::HTuple scaleStep =HAuto;
    HalconCpp::HTuple optimization =HAuto;
    HalconCpp::HString metric="use_polarity";
    HalconCpp::HTuple contrast; // Htuple containing [lowerThreshold, UpperThreshold, MinSizeContrast]
    HalconCpp::HTuple minContrast =HAuto;


    double minScore=0.9; Hlong numMatches=1; double maxOverlap=0.9; HalconCpp::HTuple subPixel="none";
    double greediness=1;
    HalconCpp::HTuple row , col, angle, scale, score;
};

#endif // MATCHING_H
