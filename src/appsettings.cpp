#include "appsettings.h"

appSettings::appSettings()
{
    QFile settFile(settingsFileName);
    int res =-1;
    /* If settings file doesn't exist in the default directory
         * create new one with default value Or select one
         **/
    settings = new QSettings(settingsFileName, QSettings::IniFormat);
    if (!settFile.exists())
    {
        createDefaultSettings();
        qDebug() << "Creating default setting in: " << "done " << res;
    }
    else
    {
        //choose a file from dialog windows??
    }

    /* Load settings from file
         **/
    res=loadSettings();
    qDebug() << "Loading setting from: " << "done " << res;
}

int appSettings::loadSettings()
{
    settings->beginGroup("PLC");
    PlcIpAddress = settings->value("PlcAddress").toString();
    NoDB = settings->value("DBNumber").toInt();
    BufferLen = settings->value("Bufferlength").toInt();
    settings->endGroup();

    settings->beginGroup("DataRepository");
    dirDataRep=settings->value("path").toString();
    settings->endGroup();

    return 0;
}

int appSettings::saveSettings()
{
    settings->beginGroup("PLC");
    settings->setValue("PlcAddress", PlcIpAddress);
    settings->setValue("DBNumber",NoDB );
    settings->setValue("Bufferlength", BufferLen);
    settings->endGroup();

    settings->beginGroup("DataRepository");
    settings->setValue("path", dirDataRep);
    settings->endGroup();

    return 0;
}

int appSettings::createDefaultSettings()
{
    settings->beginGroup("PLC");
    settings->setValue("PlcAddress", PlcIpAddressDef);
    settings->setValue("DBNumber",NoDBdef);
    settings->setValue("Bufferlength", BufferLendef);
    settings->endGroup();

    settings->beginGroup("DataRepository");
    settings->setValue("path", dirDataRepDef);
    settings->endGroup();
    return 0;
}
