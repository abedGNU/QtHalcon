#include "testgraphicsview.h"


TestGraphicsView::TestGraphicsView(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    graphicsView = new qViewGraphics();
    horizontalLayout->addWidget(graphicsView);

   // view = new View("to");
   // horizontalLayout_2->addWidget(view);
}


void TestGraphicsView::on_pbShowImage_clicked()
{

    graphicsView->showImage(QImage("green-dot"));
    try
    {
        HalconCpp::HObject obj;
        QString imloc = qApp->applicationDirPath() + "/Matchimage";
        HalconCpp::ReadImage(&obj, HalconCpp::HTuple(imloc.toStdString().c_str()));
        graphicsView->showImage(ImageConvertion::HImage2QImage(obj));
    }
    catch(HalconCpp::HException &ex)
    {
        Global::HExceptio(ex);
    }

}

void TestGraphicsView::on_pbShowView_clicked()
{

}
