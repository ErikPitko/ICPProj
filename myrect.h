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

#ifndef RECT_H
#define RECT_H

#include <QRect>
#include "point2d.h"
#include <algorithm>
#include <QtGui>
#include <iostream>
/**
 * The Rectangle class.
 */
class MyRect : public QRect
{
public:
	/**
	 * Instantiates a new rectangle from existing one.
	 *
	 * @param rect copied rectangle
	 */
    MyRect(const MyRect& rect);
    /**
	 * Instantiates a new rectangle.
	 *
	 * @param position position of created rectangle
	 * @param size dimensions of rectangle
	 */
    MyRect(Point2D position, Point2D size);
    /**
	 * Instantiates a new rectangle.
	 *
	 * @param positionX the x coord
	 * @param positionY the y coord
	 * @param size dimensions of rectangle
	 */
    MyRect(double positionX, double positionY, Point2D size);
    /**
	 * Instantiates a new rectangle.
	 *
	 * @param position position of created rectangle
	 * @param sizeX width
	 * @param sizeY height
	 */
    MyRect(Point2D position, double sizeX, double sizeY);
    /**
	 * Instantiates a new rectangle.
	 *
	 * @param positionX the x coord
	 * @param positionY the y coord
	 * @param sizeX width
	 * @param sizeY height
	 */
    MyRect(double positionX, double positionY, double sizeX, double sizeY);
    /**
	 * Checks if rectangle contains given point.
	 *
	 * @param point point to be checked
	 * @return true, if successful
	 */
    bool contains(Point2D* point);
    /**
	 * Checks if rectangle intersects with given rectangle.
	 *
	 * @param rect rectangle to be checked
	 * @return true, if successful
	 */
    bool intersect(MyRect* rect);
    /**
	 * Gets minimal x axis coord.
	 *
	 * @return leftmost x axis coord
	 */
    double XMin();
    /**
	 * Gets maximal x axis coord (X + rect width).
	 *
	 * @return rightmost x axis coord
	 */
    double XMax();
    /**
	 * Gets minimal y axis coord.
	 *
	 * @return bottom y axis coord
	 */
    double YMin();
    /**
	 * Gets maximal x axis coord (Y + rect height).
	 *
	 * @return top y axis coord
	 */
    double YMax();
    /**
	 * @return Rectangle position
	 */
    Point2D* Position();
    /**
	 * @return Rectangle dimensions
	 */
    Point2D* Size();
    /**
	 * @return Center of the rectangle
	 */
    Point2D* Center();

    friend std::istream& operator >>(std::istream& is, MyRect& rect)
    {
        char trash;
        double temp;
        is >> temp;
        rect.setX(temp);
        is >> trash;
        is >> temp;
        rect.setY(temp);
        is >> trash;
        is >> temp;
        rect.setWidth(temp);
        is >> trash;
        is >> temp;
        rect.setHeight(temp);
        return is;
    }

    friend std::ostream& operator <<(std::ostream& os, MyRect& rect)
    {
        os << rect.x() << '-' << rect.y() << '-' << rect.width() << '-' << rect.height();
        return os;
    }
};

#endif // RECT_H
