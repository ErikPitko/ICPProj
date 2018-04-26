/*******************************************************************************
 *
 * VUT FIT Brno - ICP project BlockDiagram
 *
 * Copyright (C) 2018, Adam Petras (xpetra19)
 * Copyright (C) 2018, Erik Pitko (xpitko00)
 *
 * Contributors:
 * 		Adam Petras - GUI, base application implementation, Doxygen doc
 * 		Erik Pitko - base application implementation, save/load scene
 *
 ******************************************************************************/

#ifndef POINT2D_H
#define POINT2D_H

#include <math.h>
#include <istream>
class Point2D
{
public:
    double X;
    double Y;
    Point2D(double, double);
    static double distance(Point2D, Point2D);
    static Point2D* vector(Point2D*, Point2D*);
    Point2D sub(Point2D);
    Point2D add(Point2D);

    friend std::ostream& operator <<(std::ostream& os, Point2D& point)
    {
        os <<"X: "<<point.X<<"Y: "<< point.Y;
        return os;
    }
};

#endif // POINT2D_H
