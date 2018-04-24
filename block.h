#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "drawableobject.h"
#include "EBlock.h"
#include "myrect.h"
#include "port.h"
#include <vector>
#include <iostream>
#include "link.h"

class Block : public DrawableObject
{
    EBlock _eBlock;
    MyRect *_rect= nullptr;
    MyRect *_resizeRect= nullptr;
    QImage image;
    std::vector<Port*> inPorts = std::vector<Port*>();
    Port *_outPort = nullptr;
    double value = 0;
    bool calculated = false;
//    Text debugDisp;
//    Text disp;

    void calculatePortsToMiddle();
    bool recalculateHeights();

public:
    static const int MINBLOCKSIZE = 100;
    static const int MAXBLOCKSIZE = 400;
    static int stepCounter;

    Block(EBlock, MyRect*);
    Block(EBlock, MyRect*, double);
    virtual ~Block();
    void genInPort();
    /***
     * @brief Recursive searching for loops
     * @param comparing Always left null
     * @param block Block to be checked for loop in tree
     * @returns true if loop is found
     */
    static bool isCycled(Block*, Block*);
    static double compute(Block*);
    static void unsetCalculated(Block*);
    std::vector<Port*> getInPorts();
    Port* getOutPort();
    void setOutPort(Port*);
    void setInPorts(std::vector<Port*>);
    void setInPort(int, Port*);
    double getValue() const;
    void setValue(double);
    MyRect* getResizeRect();
    EBlock getType() const;
    void setRectPosition(Point2D*);
    MyRect* getRect() const;
    void setRect(MyRect*);
    void setType(EBlock);
    void Move(double, double);
    void Resize(double, double);
    void virtual Draw(QPainter*) override;

    friend std::istream& operator >>(std::istream& is, Block& block)
    {
        MyRect* rect = new MyRect(0,0,0,0);
        is >> *rect;
        block.setRect(rect);

        double temp;
        is >> temp;

        int type;
        is >> type;
        block.setType(static_cast<EBlock>(type));
        block.setValue(temp);
        return is;
    }

    friend std::ostream& operator <<(std::ostream& os, const Block& block)
    {
        os << *block.getRect() << block.getValue() << block.getType();
        return os;
    }
};

#endif // BLOCK_H
