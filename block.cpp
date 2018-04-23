#include "block.h"

Block::Block(EBlock eBlock, Rect rect) : DrawableObject()
{
    eBlock = eBlock;
    _rect = rect;
    _outPort = new Port(new Rect(_rect.XMax()-(Port.PORT_SIZE+Port.PORT_SIZE/2),_rect.getY()+_rect.getHeight()/2-Port.PORT_SIZE/2,Port.PORT_SIZE,Port.PORT_SIZE),this,Color.RED);
}

Block::Block(EBlock eBlock, Rect rect, double value) : DrawableObject()
{
    eBlock = eBlock;
    _rect = rect;
    value = value;
    _outPort = new Port(new Rect(_rect.XMax()-(Port.PORT_SIZE+Port.PORT_SIZE/2),_rect.getY()+_rect.getHeight()/2-Port.PORT_SIZE/2,Port.PORT_SIZE,Port.PORT_SIZE),this,Color.RED);
}

void Block::calculatePortsToMiddle() {
    recalculateHeights();
    double step = _rect.getHeight() / inPorts.size();
    double div = step / 2;
    for (int i = 0; i < inPorts.size(); i++)
    {
        inPorts.get(i).Rect.setY((int) (_rect.getY() + (i + 1) * step - div- Port.PORT_SIZE / 2));
    }
}

bool Block::recalculateHeights()
    {
        if(inPorts.size()*Port.PORT_SIZE >= _rect.getHeight()-10)
        {
            _rect.setY(inPorts.size()*Port.PORT_SIZE + inPorts.size()*15);
            _outPort.Rect.setY(_rect.getY()+_rect.getHeight()/2-Port.PORT_SIZE/2);
            return true;
        }
        return false;
    }
