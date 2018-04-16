#-------------------------------------------------
#
# Project created by QtCreator 2018-04-16T09:24:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtVisionCV
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include("lib.pri")

INCLUDEPATH += $$PWD/. \
            src \
            src/camera \
            src/matching \
            src/calibration \
            src/roi \
            src/communication \
            src/utilities

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/communication/plc_siemens.cpp \
        src/communication/snap7.cpp \
        src/matching/matching.cpp \
        src/communication/step7_settings.cpp \
        src/utilities/qhwindow.cpp \
        src/appsettings.cpp \
        src/camera/cameraui.cpp \
    src/calibration/calibrationui.cpp \
    src/roi/roiui.cpp \
    src/productionui.cpp \
    src/settingsui.cpp

HEADERS += \
        src/mainwindow.h \
    src/communication/plc_siemens.h \
    src/communication/snap7.h \
    src/matching/matching.h \
    src/communication/step7_settings.h \
    src/utilities/qhwindow.h \
    src/appsettings.h \
    src/camera/cameraui.h \
    src/calibration/calibrationui.h \
    src/roi/roiui.h \
    src/productionui.h \
    src/settingsui.h \
    src/global.h

FORMS += \
    src/mainwindow.ui \
    src/settings.ui \
    src/camera/camera.ui \
    src/calibration/calibration.ui \
    src/matching/matching.ui \
    src/roi/roi.ui \
    src/production.ui \
    src/communication/step7_settings.ui

TRANSLATIONS = ts/ts_it.ts \
               ts/ts_cn.ts

RESOURCES += \
    res/resources.qrc
