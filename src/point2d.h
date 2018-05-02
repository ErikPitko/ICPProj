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

#ifndef POINT2D_H
#define POINT2D_H

#include <math.h>
#include <istream>
class Point2D
{
public:
	/** The x coord. */
    double X;
    /** The y coord. */
    double Y;
    /**
	 * Instantiates a new point2D.
	 *
	 * @param x the x coord
	 * @param y the y coord
	 */
    Point2D(double x, double y);
    /**
	 * Calculates distance between two points.
	 *
	 * @param first the first point
	 * @param second the second point
	 * @return the distance
	 */
    static double distance(Point2D first, Point2D second);
    /**
	 * Calculates vector from points.
	 *
	 * @param first the first point
	 * @param second the second point
	 * @return the point2D vector
	 */
    static Point2D* vector(Point2D* first, Point2D* second);

    friend std::ostream& operator <<(std::ostream& os, Point2D& point)
    {
        os <<"X: "<<point.X<<"Y: "<< point.Y;
        return os;
    }
};

#endif // POINT2D_H
