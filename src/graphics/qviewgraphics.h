#ifndef QVIEWGRAPHICS_H
#define QVIEWGRAPHICS_H

#include <QWidget>
#include <QDebug>
#include "ui_qviewgraphics.h"

#include <QGraphicsPixmapItem>

class qViewGraphics : public QWidget, public Ui::qViewGraphics
{
    Q_OBJECT

public:
    explicit qViewGraphics(QWidget *parent = 0);
    void showImage(QImage image);

    QGraphicsScene scene;
    QGraphicsPixmapItem originalPixmap, processedPixmap;
    QImage originalImage, processedImage;

protected:


private:


};

#endif // QVIEWGRAPHICS_H
