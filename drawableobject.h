#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "point2d.h"


class DrawableObject
{
public:
    DrawableObject();
    Point2D Position;
    void virtual Draw();
};

#endif // DRAWABLEOBJECT_H
