#ifndef RECT_H
#define RECT_H

#include <QRect>

class Rect : public QRect
{
public:
    Rect(const Rect&);
    Rect(Point2D, Point2D);
    Rect(double, double, Point2D);
    Rect(Point2D, double, double);
    Rect(double, double, double, double);
    bool contains(Point2D);
    bool intersect(Rect);
    double XMin();
    double XMax();
    double YMin();
    double YMax();
    Point2D Position();
    Point2D Size();
    Point2D Center();
};

#endif // RECT_H
