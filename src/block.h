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

#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "drawableobject.h"
#include "EBlock.h"
#include "myrect.h"
#include "port.h"
#include <vector>
#include <iostream>
#include <QLabel>
#include "widget.h"
#include "link.h"
#include "resources.h"

/**
 * Class of block
 */
class Block : public DrawableObject
{
    /** Enum block type.*/
    EBlock _eBlock;
    /** Graphic properties (position, size).*/
    MyRect *_rect= nullptr;
    /** Graphic properties of resizing box.*/
    MyRect *_resizeRect= nullptr;
    /** Background image.*/
    QImage image;
    /** List of input ports.*/
    std::vector<Port*> *inPorts = new std::vector<Port*>();
    /** The out port. */
    Port *_outPort = nullptr;
    /** Stored value inside block. */
    double value = 0;
    /** Variable used for optimization. Individual block is not calculated multiple times in one calculation cycle.*/
    bool calculated = false;
    /**Static variale used to draw the rectangle over image, when debug is running.*/
    static Block* debug;
    /** Block value inside display block.*/
    QLabel *disp;
    /**
	 * Centers input ports in the block.
	 */
    void calculatePortsToMiddle();
    /**
	 * Calculates block size according to number of input ports and centers output block.
	 * @return false if block is too small to contain all input ports
	 */
    bool recalculateHeights();

public:
    /** The Constant MINBLOCKSIZE. */
    static const int MINBLOCKSIZE = 100;
    /** The Constant MAXBLOCKSIZE. */
    static const int MAXBLOCKSIZE = 400;
    /**
	 * Counter used in debug mode.
	 * Each individual block calculation rises counter by 1.
	 * Calculation proceeds until it matches {@link Graphics.Panel#stepCounter}
	 */
    static int stepCounter;
    /**
	 * @param eBlock type of the block
	 * @param rect graphic properties of the block
	 */
    Block(EBlock eBlock, MyRect* rect);
    /**
	 *
	 * @param eBlock type of the block
	 * @param rect graphic properties of the block
	 * @param value internal value of block used by input block
	 */
    Block(EBlock eBlock, MyRect* rect, double value);

    virtual ~Block();
    /**
	 * Generates one input port.
	 *
	 * calls {@link #CalculatePortsToMiddle()}
	 */
    void genInPort();
    /**
     * Recursive searching for loops
     * @param comparing Always left null
     * @param block Block to be checked for loop in tree
     * @returns true if loop is found
     */
    static bool isCycled(Block* comparing, Block* block);
    /**
	 * Recursive block calculation from root.
	 *
	 * Recursively calls all blocks on all input ports and calculates its values.
	 * @param block root block to be calculated
	 * @return value of given root block
	 */
    static double compute(Block* block);
    /**
	 * Set blocks to be recalculated after a change in links or blocks.
	 *
	 * Recursively calls each block from given port and sets {@link #calculated} to false.
	 * @param block changed block
	 */
    static void unsetCalculated(Block* block);
    /**
	 * Gets the input ports.
	 *
	 * @return the input ports
     */
    std::vector<Port*> *getInPorts();
    /**
	 * Gets the output port.
	 *
	 * @return the output port
	 */
    Port* getOutPort();
    /**
	 * Sets the output port.
	 *
	 * @param p the output port
	 */
    void setOutPort(Port* p);
    /**
	 * Sets new vector of input ports.
	 *
	 * @param portvector new input port vector
	 */
    void setInPorts(std::vector<Port*> portvector);
    /**
	 * Sets new input port and calls {@link #CalculatePortsToMiddle()}.
	 *
	 * @param index index of input port to be changed
	 * @param newInPort new input port
	 */
    void setInPort(int index, Port* newInPort);
    /**
	 * Gets the value.
	 *
	 * @return the value
	 */
    double getValue() const;
    /**
	 * Assigns value and changes {@link #debugDisp} and {@link #disp}.
	 * @param value value to be assigned
	 */
    void setValue(double value);
    /**
	 * Gets the resizing rectangle.
	 *
	 * @return the rectangle
	 */
    MyRect* getResizeRect();
    /**
	 * Gets the type.
	 *
	 * @return the type
	 */
    EBlock getType() const;
    /**
	 * Sets new position, does not redraw in GUI.
	 * @param position new position
	 */
    void setRectPosition(Point2D*position);
    /**
	 * Gets the rectangle.
	 *
	 * @return the rectangle
	 */
    MyRect* getRect() const;
    /**
     * Sets the rectangle.
     *
     * @param rect new rectangle
     */
    void setRect(MyRect* rect);
    /**
	 * Changes type of a block and calls {@link #unsetCalculated(Block)}.
	 *
	 * @param eBlock new block type
	 */
    void setType(EBlock eBlock);
    /**
	 * Moves block by value.
	 *
	 * @param delta pixels on X and Y axis
	 */
    void Move(Point2D* delta);
    /**
	 * Resizes block by value.
	 *
	 * calls {@link #CalculatePortsToMiddle()}
	 * @param delta pixels on X and Y axis
	 */
    void Resize(Point2D*);
    /**
	 * Draws block by QPainter.
	 * @param painter the pane
	 * @see Graphics.DrawableObject#Draw(QPainter*)
	 */
    void virtual Draw(QPainter* painter) override;
    /**
	 * Calls destructor on block. Deletes Block including all its ports and links.
	 */
    bool completeDeleteBlock();

};

std::istream& operator >>(std::istream& is, Block& block);
std::ostream& operator <<(std::ostream& os, Block& block);

#endif // BLOCK_H
