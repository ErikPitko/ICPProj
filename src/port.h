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

#ifndef PORT_H
#define PORT_H
class Block;
class Port;
class Link;
#include <vector>
#include "block.h"
#include "link.h"
#include "port.h"
#include "myrect.h"
#include "drawableobject.h"
/**
 * The Port class.
 */
class Port : public DrawableObject
{
private:
    /** The block in which port resides. */
    Block* _block = nullptr;
    /** The vector of links connected to the port. */
    std::vector<Link*> *_link;
    /** Stores value if on port was clicked. */
    bool isClicked;
public:
    /** @see Block#_rect */
    MyRect* Rect = nullptr;
    /** The Constant PORT_SIZE. */
    static const int PORT_SIZE = 15;
    /**
	 * Gets the vector of links.
	 *
	 * @return the vector of links
	 */
    std::vector<Link*>* GetLinks();
    /**
	 * Gets the first link in vector.
	 *
	 * @return the link
	 */
    Link* GetFirstLink();
    /**
	 * Gets the block.
	 *
	 * @return the block
	 */
    Block* GetBlock();
    /**
     * Gets if port is clicked
     * @return if port is clicked
     */
    bool GetIsClicked();
    /**
     * Sets if port is clicked
     * @param if port is clicked
     */
    void SetIsClicked(bool value);

    /**
	 * Instantiates a new port.
	 *
	 * @param rect graphic properties of the port
	 * @param block the block in which given port resides
	 */
    Port (MyRect* rect,Block* block);
    /**
     * Destructor of port that is called from Block.
     */
    virtual ~Port();
    /**
	 * Adds link to port if it does not exist already.
	 *
	 * @param link the new link
	 */
    void setLink(Link*);
    /**
	 * Deletes all links connected to the port.
	 */
    void unSetLink();
	/**
	 * @see Graphics.DrawableObject#Draw(QPainter*)
	 */
    void virtual Draw(QPainter*) override;

    friend std::ostream& operator <<(std::ostream& os, Port& port)
    {
        os << port.GetBlock() << ';' << &port;
        return os;
    }
};

#endif // PORT_H
