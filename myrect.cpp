#include "myrect.h"


double MyRect::XMin() {
    return x();
}

double MyRect::XMax() { return x() + width();
}

double MyRect::YMin() {
    return y();
}

double MyRect::YMax() {
    return y() + height();
}

Point2D* MyRect::Position()
{
    return new Point2D(x(),x());
}

Point2D* MyRect::Size()
{
    return new Point2D(width(),height());
}

Point2D* MyRect::Center()
{
    return new Point2D(x()+(width()/2),y()+(height()/2));
}

MyRect::MyRect(const MyRect &rect) : QRect()
{
    //super();
    setX(rect.x());
    setY(rect.y());
    setWidth(rect.width());
    setHeight(rect.height());
}

MyRect::MyRect(Point2D position, Point2D size) : QRect()
{
    //super();
    setX(position.X);
    setY(position.Y);
    setWidth(size.X);
    setHeight(size.Y);
}

MyRect::MyRect(double positionX,double positionY, Point2D size) : QRect()
{
    //super();
    setX(positionX);
    setY(positionY);
    setWidth(size.X);
    setHeight(size.Y);
}

MyRect::MyRect(Point2D position, double sizeX,double sizeY) : QRect()
{
    //super();
    setX(position.X);
    setY(position.Y);
    setWidth(sizeX);
    setHeight(sizeY);
}

MyRect::MyRect(double positionX,double positionY, double sizeX,double sizeY) : QRect()
{
    //super();
    setX(positionX);
    setY(positionY);
    setWidth(sizeX);
    setHeight(sizeY);
}

bool MyRect::contains(Point2D *point)
{
    return point->X >=  x() && point->X <= XMax() && point->Y >= y() && point->Y <= YMax();
}

bool MyRect::intersect(MyRect *rect)
{
    double xmin = std::max(x(), rect->x());
    double xmax = std::min(XMax(), rect->XMax());
    if (xmax >= xmin) {
        double ymin = std::max(y(),rect->y());
        double ymax = std::min(YMax(), rect->YMax());
        if (ymax >= ymin) {
            return true;
        }
    }
    return false;
}
