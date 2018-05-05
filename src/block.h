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
    /**
     * Backward recursive searching for loops.
     *
     * Builds list of blocks it goes through and searches for two identical blocks.
     * Goes in a reverse direction, searches on all input ports.
     *
     * @param newVec empty vector
     * @param block Root block from which to start loop search
     * @returns true if loop is found
     */
    static bool isCycled(std::vector<Block*> newVec, Block* block);
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
     * Deletes debug mark on a block.
     *
     * calls {@link #CalculatePortsToMiddle()}
     */
    static void delDebugRect();
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
     * Checks if block is already calculated.
     *
     * @return true if block is calculated
     */
    bool getCalculated();
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
     * Checks for the loops in scheme and if none are found calls compute()
     *
     * @see Block::compute()
     *
     * @param block root block to be calculated
     * @return true, if no loop is found
     */
    static bool Compute(Block* block);
    /**
     * Set blocks to be recalculated after a change in links or blocks.
     *
     * Recursively calls each block from given port and sets {@link #calculated} to false.
     * @param block changed block
     * @return true if no loop was found
     */
    static void UnsetCalculated(Block* block);
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
