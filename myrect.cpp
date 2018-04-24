#include "myrect.h"


double MyRect::XMin() {
    return getX();
}

double MyRect::XMax() { return getX() + getWidth();
}

double MyRect::YMin() {
    return getY();
}

double MyRect::YMax() {
    return getY() + getHeight();
}

Point2D MyRect::Position()
{
    return new Point2D(getX(),getY());
}

Point2D MyRect::Size()
{
    return new Point2D(getWidth(),getHeight());
}

Point2D MyRect::Center()
{
    return new Point2D(getX()+(getWidth()/2),getY()+(getHeight()/2));
}

static MyRect ZERO = new MyRect(0,0,0,0);

MyRect::MyRect(MyRect rect) : QRect()
{
    //super();
    setX(rect.x());
    setY(rect.y());
    setWidth(rect.getWidth());
    setHeight(rect.getHeight());
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

bool MyRect::Contains(Point2D point)
{
    return point.X >=  x() && point.X <= XMax() && point.Y >= y() && point.Y <= YMax();
}

bool MyRect::Intersect(MyRect rect)
{
    double xmin = max(x(), rect.x());
    double xmax = min(XMax(), rect.XMax());
    if (xmax >= xmin) {
        double ymin = max(y(),rect.y());
        double ymax = min(YMax(), rect.YMax());
        if (ymax >= ymin) {
            return true;
        }
    }
    return false;
}
