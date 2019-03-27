#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    pbCamera->setSizePolicy(QSizePolicy::MinimumExpanding,
                            QSizePolicy::MinimumExpanding);
    pbSettings->setSizePolicy(QSizePolicy::MinimumExpanding,
                              QSizePolicy::MinimumExpanding);
    pbCalibration->setSizePolicy(QSizePolicy::MinimumExpanding,
                                 QSizePolicy::MinimumExpanding);
    pbProduction->setSizePolicy(QSizePolicy::MinimumExpanding,
                                QSizePolicy::MinimumExpanding);
    pbMatching->setSizePolicy(QSizePolicy::MinimumExpanding,
                              QSizePolicy::MinimumExpanding);
    pbExit->setSizePolicy(QSizePolicy::MinimumExpanding,
                          QSizePolicy::MinimumExpanding);

    Global::repDirLoc = qApp->applicationDirPath();

    Explorer::ActiveCamera.clear();
    Explorer::ActiveCameras.clear();
    Explorer::activeCameras();
}


void MainWindow::on_pbCamera_clicked()
{
    camera = new CameraUi();
    camera->show();
}

void MainWindow::on_pbSettings_clicked()
{
    settings = new SettingsUi();
    settings->show();
}

void MainWindow::on_pbMatching_clicked()
{
    matching = new MatchingUi();
    matching->show();
}

void MainWindow::on_pbExit_clicked()
{
    gv = new TestGraphicsView();
    gv->show();
}

void MainWindow::on_pbCalibration_clicked()
{
    calibration = new CalibrationUi();
    calibration->show();
}
