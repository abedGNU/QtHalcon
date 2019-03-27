#include "cameraui.h"






CameraUi::CameraUi(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    hwind = new QHWindow();
    vlHwindows->addWidget(hwind);
    hwind->show();

    cmbInterface->clear();
    cmbInterface->addItems( QStringList(interfaceLst) );
    twConnectedDevices->setShowGrid(true);
    twConnectedDevices->setSelectionMode(QAbstractItemView::SingleSelection);
    twConnectedDevices->setSelectionBehavior(QAbstractItemView::SelectRows);
    findConnectedDevices();
    retrieveSavedCameras();
    displayInstantiatedDev();
}



void CameraUi::findConnectedDevices()
{
    try{
        QString interf = cmbInterface->currentText();
        QList<QList<QString>> conDev;
        conDev.clear();
        // search ALL connected devices
        if (interf == "ALL")
        {

            for(int i=0; i< interfaceLst.length();i++)
            {
                if( interfaceLst[i]== "ALL")
                    continue;
                conDev.append(Explorer::searchConnectedDevices(interfaceLst[i]));
            }
        }
        // serach devices of selected interface
        else
        {
            conDev.append(Explorer::searchConnectedDevices(interf));
        }
        qDebug()<< conDev;

        //Show number of devices in label
        lblNoConnDevices->setText("Numer of devices: "+ QString::number(conDev.length()) );

        // view devices in table
        twConnectedDevices->setRowCount( conDev.length() );
        for(int i=0;i< conDev.length(); i++)
        {
            int k=0;
            twConnectedDevices->setItem(i,k++, new QTableWidgetItem( conDev.at(i).at(0) ) );
            twConnectedDevices->setItem(i,k++, new QTableWidgetItem( conDev.at(i).at(1) ) );
        }

    }
    catch(QException &ex)
    {
        Global::QExceptio(ex);
    }
}

void CameraUi::createCamData()
{
    if(twConnectedDevices->selectedItems().length() == 2)
    {
        // every item(cell) of the table is a QTableWidgetItem.
        // selectedItems return a QList<QTableWidgetItem>
        // single selection is active,
        // if (twConnectedDevices->selectedItems().length() == 0)
        // return;
        QString device = twConnectedDevices->selectedItems()[0]->text();
        QString interf = twConnectedDevices->selectedItems()[1]->text();
        QString cameraName;

        InputDialog dial(this);
        if(dial.exec()==QDialog::Accepted) {
            cameraName=dial.inputText->text();
        }
        else{ //dial.exec()==QDialog::Rejected
            return;
        }

        QList<QString> camData;
        camData.append(device);
        camData.append(cameraName);
        camData.append(interf);

        QDir camDir(qApp->applicationDirPath() + Global::camDir);
        Global::debugRepDirs();
        Explorer::createCamData(camDir.absolutePath(), camData);
    }
}

void CameraUi::retrieveSavedCameras()
{
    QString locVision = Global::repDirLoc+Global::camDir;
    savedCam=Explorer::getSavedCameras(locVision);
    twSavedDevices->setRowCount(savedCam.size());

    QHash<QString, QList<QString>>::iterator i;
    int k=0;
    for (i = savedCam.begin(); i != savedCam.end(); ++i)
    {
        if(i.value().length()<2 )
            return;
        qDebug()<< "Key = "<<i.key() << "Value" << i.value().at(0) << i.value().at(1);
        int j=0;
        twSavedDevices->setCellWidget(k,j++, new QCheckBox );
        twSavedDevices->setItem(k,j++, new QTableWidgetItem( i.key() ) );
        twSavedDevices->setItem(k,j++, new QTableWidgetItem( i.value().at(0) ) );
        twSavedDevices->setItem(k,j++, new QTableWidgetItem( i.value().at(1) ) );
        k++;
    }
    twSavedDevices->sortByColumn(1);
}

void CameraUi::displayInstantiatedDev()
{
    QList<QString> camDev = Explorer::ActiveCamera.keys();
    listWidgetInstanceDev->clear();
    listWidgetInstanceDev->addItems(camDev);
}

void CameraUi::on_pbFindConnectedDevices_clicked()
{
    // Explorer::ActiveCamera.clear();
    twConnectedDevices->clearContents();
    findConnectedDevices();
}

void CameraUi::on_pbSaveDevices_clicked()
{
    createCamData();
    retrieveSavedCameras();
}

void CameraUi::on_pbGrab_clicked()
{
    try{
    QList<QString> camDev = Explorer::ActiveCamera.keys();
    if(twConnectedDevices->selectedItems().length() == 2)
    {
        QString device = twConnectedDevices->selectedItems()[0]->text();
        QString interf = twConnectedDevices->selectedItems()[1]->text();
        QString camType="default";
        if (interf == "File")
            return;
        if (!camDev.contains( device))
        {
            Camera cam(device, "dumpCamName", interf, camType);
            hwind->showImage(cam.GrabImage());
            qDebug()<< "Image grabbed from"<< device;
        }
        else
        {
            qDebug()<< "Instance device name"<< Explorer::ActiveCamera.value(device)->deviceName;
            qDebug()<< "Camera Name"<< Explorer::ActiveCamera.value(device)->cameraName;
            HalconCpp::HImage img = Explorer::ActiveCamera.value(device)->GrabImage();
            qDebug()<<"Image height" << img.Height().ToString();
            hwind->showImage( img);

        }
    }
    }
    catch(HalconCpp::HException& ex)
    {
        Global::HExceptio(ex);
    }
}


void CameraUi::on_pbUpdate_clicked()
{
    retrieveSavedCameras();
}

void CameraUi::on_pbInitializeDevices_clicked()
{
    Explorer::activeCameras();
    displayInstantiatedDev();
}

void CameraUi::on_pbReinitializeDevices_clicked()
{
    HalconCpp::CloseAllFramegrabbers();
    Explorer::ActiveCameras.clear();
    Explorer::activeCameras();
    displayInstantiatedDev();
}

void CameraUi::on_pbCloseAllDevices_clicked()
{
    HalconCpp::CloseAllFramegrabbers();
    Explorer::ActiveCamera.clear();
    displayInstantiatedDev();
}
