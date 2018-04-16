#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include "ui_camera.h"

class CameraUi : public QWidget, public Ui::Camera
{
    Q_OBJECT

public:
    explicit CameraUi(QWidget *parent = 0);
    //virtual ~Camera();

private:

};

#endif // CAMERA_H
