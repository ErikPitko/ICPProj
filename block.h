#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "drawableobject.h"
#include "EBlock.h"
#include "rect.h"
#include <vector>

class Block : public DrawableObject
{
    EBlock _eBlock;
    Rect _rect;
    Rect _resizeRect;
    ImageView image;
    std::vector<Port> inPorts = new std::vector<Port>();
    Port _outPort;
    double value = 0;
    bool calculated = false;
    Text debugDisp;
    Text disp;

    void calculatePortsToMiddle();
    bool recalculateHeights();
    void setValue(double);



public:
    static const int MINBLOCKSIZE = 100;
    static const int MAXBLOCKSIZE = 400;

    Block(EBlock, Rect);
    Block(EBlock, Rect, double);
    void genInPort();
    /***
     * @brief Recursive searching for loops
     * @param comparing Always left null
     * @param block Block to be checked for loop in tree
     * @returns true if loop is found
     */
    static bool isCycled(Block, Block);
    static double compute(Block);
    static void unsetCalculated(Block);
    std::vector<Port> getInPorts();
    Port getOutPort();
    void setOutPort(Port);
    void setInPorts(std::vector<Port>);
    void setInPort(int, Port);
    double getValue();
    Rect getResizeRect();
    EBlock getType();
    void setRectPosition(Point2D);
    Rect getRect();
    void setType(EBlock);
    void Move(double, double);
    void Resize(double, double);
    void DeleteBlock();
    void virtual Draw() override;
};

#endif // BLOCK_H
