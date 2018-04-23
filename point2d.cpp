#include "point2d.h"

Point2D::Point2D(double x, double y)
{
    X = x;
    Y = y;
}

double Point2D::distance(Point2D first, Point2D second)
{
    sqrt(pow(first.X -second.X,2)+pow(first.Y -second.Y,2));
}

Point2D Point2D::vector(Point2D first, Point2D second)
{
    return *new Point2D(second.X-first.X,second.Y-first.Y);
}

Point2D Point2D::sub(Point2D other)
{
    return *new Point2D(this->X - other.X, this->Y - other.Y);
}

Point2D Point2D::add(Point2D other)
{
    return *new Point2D(this->X + other.X, this->Y + other.Y);
}
