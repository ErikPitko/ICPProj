#ifndef RECT_H
#define RECT_H

#include <QRect>
#include "point2d.h"
#include <algorithm>

class MyRect : public QRect
{
public:
    MyRect(const MyRect&);
    MyRect(Point2D, Point2D);
    MyRect(double, double, Point2D);
    MyRect(Point2D, double, double);
    MyRect(double, double, double, double);
    bool contains(Point2D*);
    bool intersect(MyRect*);
    double XMin();
    double XMax();
    double YMin();
    double YMax();
    Point2D* Position();
    Point2D* Size();
    Point2D* Center();
};

#endif // RECT_H
