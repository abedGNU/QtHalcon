#ifndef CAMERAUI_H
#define CAMERAUI_H

#include <QWidget>
#include <QList>
#include <QString>
#include <QException>
#include <QDir>
#include <QCheckBox>

#include "global.h"

#include "inputdialog.h"
#include "explorer.h"
#include "camera.h"
#include "qhwindow.h"
#include "imageconvertion.h"

#include "ui_cameraui.h"

class CameraUi : public QWidget, public Ui::CameraUi
{
    Q_OBJECT

public:
    explicit CameraUi(QWidget *parent = 0);
    QHWindow *hwind;
private slots:
    void on_pbFindConnectedDevices_clicked();
    void on_pbSaveDevices_clicked();

    void on_pbGrab_clicked();

    void on_pbUpdate_clicked();

    void on_pbInitializeDevices_clicked();

    void on_pbReinitializeDevices_clicked();

    void on_pbCloseAllDevices_clicked();

private:
    QList<QString> interfaceLst {"GigEVision", "File", "ALL"}; //"DirectShow"
    QHash<QString,QList<QString>> savedCam;

    void findConnectedDevices();

    void createCamData();
    void retrieveSavedCameras();

    void highlightConnSavedDev();

    void displayInstantiatedDev();

};

#endif // CAMERAUI_H
