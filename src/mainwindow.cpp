#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    //appSett = new appSettings();
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
