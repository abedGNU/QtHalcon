#ifndef MATCHING_H
#define MATCHING_H

#include <QWidget>
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
    HalconCpp::HImage imgGrabbed;
    HalconCpp::HRegion selectedRegion;

private slots:
    void on_pbGrabImage_clicked();

    void on_pbAddRoi_clicked();

    void on_pbDeleteRoi_clicked();

    void on_pbDeleteAll_clicked();

    void on_pbAddAll_clicked();

    void mouseClicked();

    void on_pbOkRoi_clicked();

private:
    HalconCpp::HRegion drawShape(Global::eDrawShape shape);
    bool roiAddActive=false;
    bool roiCutActive = false;
    bool drawActive=false; // draw in progress
    int regionCounter=0;
};

#endif // MATCHING_H
