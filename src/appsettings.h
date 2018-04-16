#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QSettings>
#include <QDebug>
#include <QFile>

class appSettings
{
public:
    appSettings();

    QSettings *settings;
    int loadSettings();
    int saveSettings();
    int createDefaultSettings();

    QString PlcIpAddress;
    int NoDB;
    int BufferLen;
    //

    // Data repository directory, if "." current directory
    QString dirDataRep ;


private:
    QString PlcIpAddressDef="192.168.50.100";
    int NoDBdef=1;
    int BufferLendef=20;

    // Data repository directory, if "." current directory
    QString dirDataRepDef= "." ;

    QString settingsFileName = "settings.ini";
};

#endif // APPSETTINGS_H
