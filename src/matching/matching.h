#ifndef MATCHING_H
#define MATCHING_H

#include <QWidget>
#include <QList>
#include <QtMath>
#include <QString>

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

    void on_pushButton_clicked();

    void on_pbReadModelFile_clicked();

private:
    HalconCpp::HRegion drawShape(Global::eDrawShape shape);
    bool roiAddActive=false;
    bool roiCutActive = false;
    bool drawActive=false; // draw in progress
    int regionCounter=0;
    QList<HalconCpp::HRegion*> lstRegions;

    void clearAndShow();
    void clearAndShow(int arg1);
    void initValues(bool readModel);

    void inspectModel();
    void createModel();
    void findModel();
    void writeModel();
    void readModel();

    HalconCpp::HTuple HAuto = "auto";
    HalconCpp::HTuple numLevels;

    double angleStart; double angleExtent; HalconCpp::HTuple angleStep;
    double scaleMin; double scaleMax; HalconCpp::HTuple scaleStep;

    HalconCpp::HTuple optimization;
    HalconCpp::HString metric;
    HalconCpp::HTuple contrast; // Htuple containing [lowerThreshold, UpperThreshold, MinSizeContrast]
    HalconCpp::HTuple minContrast;


    double minScore; Hlong numMatches; double maxOverlap;
    HalconCpp::HTuple subPixel;
    double greediness;

    HalconCpp::HTuple row , col, angle, scale, score;
    QString path = qApp->applicationDirPath()+"/";
    QString modelName="model", ext=".shm";
    //const char *modelFullName=(path+modelName+ext).toStdString().c_str();
    QString modelFullName=path+modelName+ext;
    QString imageName= "image", imageReducedName= "imagereduced", imgExt="bmp";
    QString selcectRegionName="selectedregion", regExt="HOBJ";
    /*
    const char *imgFullName=(path+imageName+imgExt).toStdString().c_str();
    const char *imgReducedFullName=(path+imageReducedName+imgExt).toStdString().c_str();
    const char *regionFullName=(path+selcectRegionName).toStdString().c_str();
    const char *imageExt = imgExt.toStdString().c_str();
*/
    QString imgFullName=path+imageName;
    QString imgFullNameExt=path+imageName+"."+imgExt;

    QString imgReducedFullName=path+imageReducedName;
    QString imgReducedFullNameExt=path+imageReducedName+"."+imgExt;

    QString regionFullName=path+selcectRegionName;
    QString regionFullNameExt=path+selcectRegionName+"."+regExt;

   // QString imageExt = imgExt;

};

#endif // MATCHING_H
