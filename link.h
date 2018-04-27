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

#ifndef LINK_H
#define LINK_H

class Port;
#include <vector>
#include "port.h"
#include "drawableobject.h"
#include <QtGui>
/**
 * The Link class.
 */
class Link : public DrawableObject
{
private:
	/** The input port. */
    Port *inPort = nullptr;
    /** The output port. */
    Port *outPort = nullptr;
    /** The graphical line representation */
    QLine *line = nullptr;
    /** The loop flag */
    bool isCycled;
    //static std::vector<Line> cycledLinks = new std::vector<Line>();
public:
    /**
	 * Instantiates a new link.
	 */
    Link();
    /**
	 * Instantiates a new link from existing link.
	 *
	 * @param link the old link
	 */
    Link(const Link& link);
    /**
	 * Instantiates a new link and links given ports.
	 *
	 * @param inPort the input port of Link (output port of Port)
	 * @param outPort the output port of Link (input port of Port)
	 */
    Link(Port* inPort, Port* outPort);
    /**
     * Desctructor that deletes dynamic alloc of instance.
     */
    virtual ~Link();
    /**
	 * Gets the input port.
	 *
	 * @return the input port
	 */
    Port* getInPort();
    /**
	 * Gets the output port.
	 *
	 * @return the output port
	 */
    Port* getOutPort();
    /**
	 * Sets the input port.
	 *
	 * @param inPort the new input port
	 */
    void setInPort(Port* inPort);
    /**
	 * Sets the output port.
	 *
	 * @param outPort the new output port
	 */
    void setOutPort(Port* outPort);
    /**
	 * Gets the graphics line.
	 *
	 * @return the line
	 */
    QLine* getLine();
    /**
	 * Checks if the link is cycled.
	 *
	 * @return true, if successful
	 */
    bool IsCycled();
    /**
	 * Sets the link loop flag.
	 */
    void SetCycled();
    /**
	 * Set loop flag to false.
	 */
    void UnSetCycled();
    /**
	 * @see Graphics.DrawableObject#Draw(QPainter*)
	 */
    void virtual Draw(QPainter*) override;
    static bool IsPointOnLine(QLine *line, Point2D *point);

};
std::ostream& operator <<(std::ostream& os, Link& link);

#endif // LINK_H
