#ifndef GLOBAL_H
#define GLOBAL_H

#include <QList>


namespace Global {

//QList Cameras;

enum eDrawShape{eRectangle, eRectangleOrient, eCircle, eEllipse, ePolygon, eFreeHand};

struct HPointD
{
    double x;
    double y ;
    double z;
};


}
#endif // GLOBAL_H
