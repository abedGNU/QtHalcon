#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include "cameraui.h"
#include "settingsui.h"
#include "matching.h"

#include "appsettings.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    CameraUi *camera;
    SettingsUi *settings;
    MatchingUi *matching;

    //appSettings appSett;

private slots:
    void on_pbCamera_clicked();

    void on_pbSettings_clicked();

    void on_pbMatching_clicked();

    void on_pbExit_clicked();

private:

};

#endif // MAINWINDOW_H
