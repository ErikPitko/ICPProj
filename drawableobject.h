#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "point2d.h"
#include <QtGui>

class DrawableObject
{
public:
    DrawableObject();
    void virtual Draw(QPainter*);
};

#endif // DRAWABLEOBJECT_H
