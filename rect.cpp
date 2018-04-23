#include "rect.h"


double Rect::XMin() {
    return getX();
}

double Rect::XMax() { return getX() + getWidth();
}

double Rect::YMin() {
    return getY();
}

double Rect::YMax() {
    return getY() + getHeight();
}

Point2D Rect::Position()
{
    return new Point2D(getX(),getY());
}

Point2D Rect::Size()
{
    return new Point2D(getWidth(),getHeight());
}

Point2D Rect::Center()
{
    return new Point2D(getX()+(getWidth()/2),getY()+(getHeight()/2));
}

static Rect ZERO = new Rect(0,0,0,0);

Rect::Rect(Rect rect)
{
    super();
    setX(rect.getX());
    setY(rect.getY());
    setWidth(rect.getWidth());
    setHeight(rect.getHeight());
}

Rect::Rect(Point2D position, Point2D size)
{
    super();
    setX(position.X);
    setY(position.Y);
    setWidth(size.X);
    setHeight(size.Y);
}

Rect::Rect(double positionX,double positionY, Point2D size)
{
    super();
    setX(positionX);
    setY(positionY);
    setWidth(size.X);
    setHeight(size.Y);
}

Rect::Rect(Point2D position, double sizeX,double sizeY)
{
    super();
    setX(position.X);
    setY(position.Y);
    setWidth(sizeX);
    setHeight(sizeY);
}

Rect::Rect(double positionX,double positionY, double sizeX,double sizeY)
{
    super();
    setX(positionX);
    setY(positionY);
    setWidth(sizeX);
    setHeight(sizeY);
}

bool Rect::Contains(Point2D point)
{
    return point.X >=  getX() && point.X <= XMax() && point.Y >= getY() && point.Y <= YMax();
}

bool Rect::Intersect(Rect rect)
{
    double xmin = Math.max(getX(), rect.getX());
    double xmax = Math.min(XMax(), rect.XMax());
    if (xmax >= xmin) {
        double ymin = Math.max(getY(),rect.getY());
        double ymax = Math.min(YMax(), rect.YMax());
        if (ymax >= ymin) {
            return true;
        }
    }
    return false;
}
