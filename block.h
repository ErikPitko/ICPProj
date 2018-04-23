#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "drawableobject.h"
#include "EBlock.h"
#include "rect.h"

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

public:
    static const int MINBLOCKSIZE = 100;
    static const int MAXBLOCKSIZE = 400;

    Block(EBlock, Rect);
    Block(EBlock, Rect, double);
};

#endif // BLOCK_H
