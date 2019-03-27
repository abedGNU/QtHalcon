#ifndef QHWINDOW_H
#define QHWINDOW_H

#include <QWidget>
#include <QDebug>
#include <HalconCpp.h>
#include <QPushButton>

class QHWindow : public QWidget, public HalconCpp::HWindow
{
    Q_OBJECT
public:
    QHWindow(QWidget *parent = 0, long Width=3840/6, long Height=2748/6);
    void showImage(HalconCpp::HImage img);
    QPushButton *pbZoom, *pbZomIn, *pbZoomOut;
    QPushButton *pbMove;
    QPushButton *pbClear, *pbGrabImage;
private:

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void mouseClic();
};

#endif // QHWINDOW_H
