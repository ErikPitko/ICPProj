#ifndef RECT_H
#define RECT_H

#include <QRect>
#include "point2d.h"
#include <algorithm>
#include <iostream>

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

    friend std::istream& operator >>(std::istream& is, MyRect& rect)
    {
        double temp;
        is >> temp;
        rect.setX(temp);
        is >> temp;
        rect.setY(temp);
        is >> temp;
        rect.setWidth(temp);
        is >> temp;
        rect.setHeight(temp);
        return is;
    }

    friend std::ostream& operator <<(std::ostream& os, MyRect& rect)
    {
        os << rect.x() << rect.y() << rect.width() << rect.height();
        return os;
    }
};

#endif // RECT_H
