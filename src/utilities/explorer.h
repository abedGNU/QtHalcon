#ifndef EXPLORER_H
#define EXPLORER_H

#include <QException>
#include <QDebug>
#include"global.h"

#include <QDir>
#include <QList>
#include <QString>

#include "camera.h"
#include "HalconCpp.h"

class Explorer
{
public:
    Explorer();

    static QHash<QString,Camera*> ActiveCamera;// future use
    static QList<Camera> ActiveCameras;

    static QList<QList<QString>> searchConnectedDevices(QString interfac);

    static Global::efileCreate createCamData(QDir repDir, QList<QString> camData);
    static QHash<QString, QList<QString>> getSavedCameras(QString locVision);
    static  QHash<QString, QString>  getEnabledCameras(QString locVision);

    static int activeCameras();

};

#endif // EXPLORER_H
