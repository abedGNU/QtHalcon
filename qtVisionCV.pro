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
            src/utilities \
            src/graphics \
            src/testclasses

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/communication/plc_siemens.cpp \
        src/communication/snap7.cpp \
        src/communication/step7_settings.cpp \
        src/graphics/qhwindow.cpp \
        src/appsettings.cpp \
        src/productionui.cpp \
        src/settingsui.cpp \
        src/utilities/explorer.cpp \
        src/matching/matchingui.cpp \
        src/matching/matching.cpp \
        src/matching/matchingparameters.cpp \
        src/camera/cameraparam.cpp \
        src/global.cpp \
        src/utilities/inputdialog.cpp \
        src/camera/camera.cpp \
        src/camera/cameraui.cpp \
        src/graphics/qviewgraphics.cpp \
        src/utilities/imageconvertion.cpp \
        src/testclasses/testgraphicsview.cpp \
        src/graphics/qenhancedgraphicsview.cpp \
        #src/graphics/view.cpp \
        src/calibration/calibrationui.cpp \
        src/calibration/calibration.cpp

HEADERS += \
        src/mainwindow.h \
        src/communication/plc_siemens.h \
        src/communication/snap7.h \
        src/communication/step7_settings.h \
        src/graphics/qhwindow.h \
        src/appsettings.h \
        src/productionui.h \
        src/settingsui.h \
        src/global.h \
        src/utilities/explorer.h \
        src/matching/matchingui.h \
        src/matching/matching.h \
        src/matching/matchingparameters.h \
        src/camera/cameraparam.h \
        src/utilities/inputdialog.h \
        src/camera/camera.h \
        src/camera/cameraui.h \
        src/graphics/qviewgraphics.h \
        src/utilities/imageconvertion.h \
        src/testclasses/testgraphicsview.h \
        src/graphics/qenhancedgraphicsview.h \
        #src/graphics/view.h \
        src/calibration/calibrationui.h \
        src/calibration/calibration.h

FORMS += \
    src/mainwindow.ui \
    src/settings.ui \
    src/production.ui \
    src/communication/step7_settings.ui \
    src/utilities/inputdialog.ui \
    src/camera/cameraui.ui \
    src/matching/matchingui.ui \
    src/graphics/qviewgraphics.ui \
    src/testclasses/testgraphicsview.ui \
    src/calibration/calibrationui.ui

TRANSLATIONS = ts/ts_it.ts \
               ts/ts_cn.ts

RESOURCES += \
    res/resources.qrc
