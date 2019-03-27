#include "qviewgraphics.h"


qViewGraphics::qViewGraphics(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    graphicsView->setScene(&scene);
    scene.addItem(&originalPixmap);

    graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    originalPixmap.setVisible(true);
}

void qViewGraphics::showImage(QImage image)
{
   originalPixmap.setPixmap(QPixmap::fromImage(image));
   graphicsView->scale( (double)graphicsView->width()/image.width(), (double)graphicsView->height()/image.height());
}



