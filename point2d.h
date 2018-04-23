#ifndef POINT2D_H
#define POINT2D_H

#include <math.h>

class Point2D
{
public:
    double X;
    double Y;
    Point2D(double, double);
    static double distance(Point2D, Point2D);
    static Point2D vector(Point2D, Point2D);
    Point2D sub(Point2D);
    Point2D add(Point2D);
};

#endif // POINT2D_H
