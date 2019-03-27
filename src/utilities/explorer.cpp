#include "explorer.h"


/**
 * @brief
 * @param
 * @return
 * @todo
 * @date
 */
Explorer::Explorer()
{

}


/**
 * @brief
 * @param
 * @return each item is Qlist of deviceName, interface,
 * @todo
 * @date
 */
QList<QList<QString>> Explorer::searchConnectedDevices(QString interfac)
{

    QList<QList<QString>> lstDev;
    HalconCpp::HTuple name (interfac.toStdString().c_str() );
    HalconCpp::HTuple query = QString("info_boards").toStdString().c_str();
    HalconCpp::HTuple information;
    HalconCpp::HTuple valueList;
    QString sValue = "device:";
    try{
        HalconCpp::InfoFramegrabber(name, query, &information, &valueList);
        qDebug()<< valueList.ToString();

        if (valueList.Length()==0 )
            return lstDev;
        for(int i=0; i<valueList.Length();i++)
        {
            std::string str = valueList[i].S();
            QString qStr = QString(str.c_str());
            qStr = qStr.mid( qStr.indexOf(sValue)+ sValue.length());
            QList<QString> lstDevices;
            lstDevices.append(qStr);
            lstDevices.append(interfac);
            lstDev.append(lstDevices);
            qDebug()<< "Device found" << lstDev.at(i);
        }
        return lstDev;
    }
    catch(HalconCpp::HException& ex)
    {
        Global::HExceptio(ex);
        return lstDev;
    }
}

/**
 * @brief
 * @param repDir : Cameras directories, where all cameras folders are stored by CamName
 * @param CamName : Camera name
 * @return
 * @todo
 * @date
 */
Global::efileCreate Explorer::createCamData(QDir repDir, QList<QString> camData)
{
    int lenData =3;
    QString deviceName = camData[0];
    QString CamName = camData[1];

    QString deviceLoc= repDir.absolutePath() + "/"+deviceName;
    QString camLoc = deviceLoc + "/" + CamName;
    QDir deviceDir(deviceLoc);
    QDir camDir(camLoc);
    bool dirCreated;

    // QString caminfoFileDevice= "cameraInfo.tup";
    QString caminfoName = camLoc +"/"+ Global::camInfoFile;

    qDebug()<<"Device" << deviceName <<"with name" << CamName << "will be created in" <<deviceLoc;

    // if parent directory doesn't exisites, return error
    // somrthing wrong happen in the repository initilization
    if (!repDir.exists() || camData.length()!=lenData)
    {
        qDebug()<< "Directory exist" << repDir.exists();
        qDebug() << "camera data length" << camData.length();
        return Global::efileCreate::eErr;
    }
    // If Camera already exist return exist
    if ( deviceDir.exists() && camDir.exists() && QFile::exists(caminfoName))
    {
        qDebug()<< "Camera"<< CamName << "already exist in" << deviceLoc;
        return Global::efileCreate::eExist;
    }
    else if(deviceDir.exists() && !camDir.exists()) {
        dirCreated=deviceDir.mkdir(CamName);
        qDebug()<< "Camera" << CamName << "created with result" << dirCreated;
    }
    else if(!deviceDir.exists() && !camDir.exists())
    {
        dirCreated=deviceDir.mkpath(CamName);
        qDebug()<< "Camera" << CamName << "and device"<<deviceName <<"created with result" << dirCreated;
    }

    if(dirCreated)
    {
        HalconCpp::HTuple cameraInfo ;
        cameraInfo.Clear();
        cameraInfo.Append(camData.at(0).toStdString().c_str());
        cameraInfo.Append(camData.at(1).toStdString().c_str());
        cameraInfo.Append(camData.at(2).toStdString().c_str());

        HalconCpp::HTuple tcm ;
        tcm.Append( caminfoName.toStdString().c_str() );
        cameraInfo.WriteTuple(tcm);
        //::string cm=caminfoFileDevice.toStdString().c_str();
        // HalconCpp::WriteTuple(cameraInfo, camLoc+"/"+caminfoFileDevice );
        return Global::efileCreate::eCreated;
    }
    else {
        return Global::efileCreate::eErr;
    }

}

/**
 * @brief Explorer::getSavedDevices
 * @param deviceName :
 * @return QHash<QString, QList<QString>> The key is the camera name, the Qlist contain device name and interface
 * @todo
 * @date
 */
QHash<QString, QList<QString> > Explorer::getSavedCameras(QString locVision)
{
    QHash<QString, QList<QString> > hCam;
    try
    {
        hCam.clear();
        QDir dirVision(locVision);
        //
        if(dirVision.isEmpty())
            return hCam;
        //
        qDebug()<< "**************Looking for devices";
        QFileInfoList infoFileDevice=dirVision.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        qDebug()<< "Found the following" << infoFileDevice.length() << "directories";
        for(int i=0; i<infoFileDevice.length() ; i++)
        {
            qDebug()<< infoFileDevice.at(i).fileName();
            qDebug()<< infoFileDevice.at(i).absoluteFilePath();
        }
        qDebug()<<"************** Looking for cameras";
        for(int i=0;i<infoFileDevice.length() ; i++)
        {
            // QFileInfoList infoFileCam= infoFileDevice.at(i).absoluteDir().entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
            QFileInfoList infoFileCam= QDir(infoFileDevice.at(i).absoluteFilePath()).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
            for(int j=0; j< infoFileCam.length() && infoFileCam.length()>0 ;j++ )
            {
                QString CamName = infoFileCam.at(j).fileName();
                QList<QString> CamInfo;
                CamInfo.append(infoFileDevice.at(i).fileName()); // append device name
                QString caminfoname = infoFileCam.at(j).absoluteFilePath() + "/"+Global::camInfoFile;
                qDebug()<< "Camera info tuple file:"<< caminfoname;
                if(QFile::exists(caminfoname))
                {
                    HalconCpp::HTuple caminfo;
                    HalconCpp::ReadTuple(HalconCpp::HTuple(caminfoname.toStdString().c_str()), &caminfo);
                    //caminfo.ReadTuple( HalconCpp::HTuple(caminfoname.toStdString().c_str() ));
                    qDebug()<<"Tuple length"<< caminfo.Length();
                    qDebug() << "Tuple info camera" << caminfo.ToString();
                    if(caminfo.Length()>=3)
                    {
                        HalconCpp::HTuple inter;
                        inter.Clear();inter.Append(caminfo[2]);
                        qDebug()<<"Tuple to char" <<inter.ToString().Text();
                        CamInfo.append( inter.ToString().Text() );
                        CamInfo.append(infoFileCam.at(j).absoluteFilePath());
                        hCam[CamName]=CamInfo;
                        qDebug()<<"Camera found"<< CamName<<CamInfo.at(0) << CamInfo.at(1) << CamInfo.at(2);
                    }
                }
                else
                    qDebug()<< "File dosen't exist" << caminfoname;
            }

        }
        QHash<QString, QList<QString>>::iterator i;
        for (i = hCam.begin(); i != hCam.end(); ++i)
            qDebug()<< i.key();
        return hCam;
    }
    catch(HalconCpp::HException &ex)
    {
        Global::HExceptio(ex);
        return hCam;
    }
}

QHash<QString, QString> Explorer::getEnabledCameras(QString locVision)
{
    QHash<QString, QString> activeCamF; // cameras enabled in file

    // check if camera is active (if is in the file activecameras)
    QString camActFile = locVision + "/" +Global::camActFile;
    QFile file(camActFile);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<< "error reading file" << file.errorString();
    }
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.count() == 2)
        {
            // when changing the Camera class to handle multiple cameras, use insertMulti
            //activeCamF.insertMulti(fields.at(0), fields.at(1));

            // insert, doesn't duplicate the key, the key will be unique
            // fields.at(0) = device name
            // fields.at(1) = camera name
            activeCamF.insert(fields.at(0), fields.at(1));
        }
    }

    file.close();

    return activeCamF;
}

/**
 * @brief
 * @param
 * @return
 * @todo
 * @date
 */
int Explorer::activeCameras()
{
    try
    {
        QString locVision = Global::repDirLoc+Global::camDir;

        QHash<QString, QList<QString> > savedCam = getSavedCameras(locVision);
        QList<QList<QString>> conDev = searchConnectedDevices("GigEVision");
        QHash<QString, QString> activeCamF = getEnabledCameras(locVision); // cameras enabled in file

        // check if enabled devices are instantiated
        QHashIterator<QString, QString> iact(activeCamF);
        while (iact.hasNext())
        {
            iact.next();
            if( ActiveCamera.count()==0 || !ActiveCamera.contains(iact.key()) )
            {
                qDebug()<<iact.key() << iact.value();
                //Camera cam(iact.key(), iact.value());
                for(int i = 0; i<conDev.count() ; i++ )
                {
                    // check if instantiated devices are connected
                    if(conDev.at(i).at(0) == iact.key() )
                    {
                        ActiveCamera.insert(iact.key(), new Camera (iact.key(), iact.value())  );
                        break;
                    }
                }
            }
            else
            {
                //ActiveCamera.value(iact.key());
                // se esite, cercaa se le camera essitono nel device, gestione futura
            }

        }


        // check if remaning cameras are saved

        //QHashIterator<QString, QList<QString>> isav(hash);
        QHash<QString,Camera*> hcam =ActiveCamera ;

        return 0;
    }
    catch (QException& ex)
    {
        Global::QExceptio(ex);
    }
}

QHash<QString,Camera*>  Explorer::ActiveCamera = QHash<QString,Camera*>();

QList<Camera> Explorer::ActiveCameras = QList<Camera>();
