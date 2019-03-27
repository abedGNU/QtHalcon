#ifndef TESTGRAPHICSVIEW_H
#define TESTGRAPHICSVIEW_H

#include <QWidget>
#include "imageconvertion.h"
#include "qviewgraphics.h"
//#include "view.h"

#include "global.h"

#include "ui_testgraphicsview.h"

class TestGraphicsView : public QWidget, public Ui::TestGraphicsView
{
    Q_OBJECT

public:
    explicit TestGraphicsView(QWidget *parent = 0);
    qViewGraphics *graphicsView;
    //View *view;

private slots:
    void on_pbShowImage_clicked();

    void on_pbShowView_clicked();

private:

};

#endif // TESTGRAPHICSVIEW_H
