/*******************************************************************************
 *
 * VUT FIT Brno - ICP project BlockDiagram
 *
 * Copyright (C) 2018, Adam Petras (xpetra19)
 * Copyright (C) 2018, Erik Pitko (xpitko00)
 *
 * Contributors:
 * 		Adam Petras - GUI, base application implementation, Doxygen doc
 * 		Erik Pitko - base application implementation, save/load scene
 *
 ******************************************************************************/

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
