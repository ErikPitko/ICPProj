#include "link.h"
#include <iostream>
#include <vector>
Link::Link() : DrawableObject()
{
        line = new QLine();
        isCycled = false;
}
Link::Link(const Link& link) : DrawableObject()
{
    line = link.line;
    setOutPort(link.outPort);
    setInPort(link.inPort);
    isCycled = link.isCycled;
}

Link::Link(Port *inPort, Port *outPort) : DrawableObject()
{
    setInPort(inPort);
    line = new QLine();
    setOutPort(outPort);
    isCycled = false;
}

Link::~Link()
{
    this->outPort->unSetLink();
    std::vector<Link*>* outLinks = this->inPort->GetLinks();
    int pos = std::find(outLinks->begin(), outLinks->end(), this) - outLinks->begin();
    outLinks->erase(outLinks->begin()+pos);
//    TODO delete line
    std::cout << "\tLink: " << this << " deleted." << std::endl;
}

Port* Link::getInPort()
{
       return inPort;
}

void Link::setInPort(Port *inPort)
{
   if (this->outPort != nullptr && inPort != nullptr)
       Block::unsetCalculated(outPort->GetBlock());
   this->inPort = inPort;
   if (inPort != nullptr)
       inPort->setLink(this);
}
Port* Link::getOutPort()
{
   return outPort;
}

void Link::setOutPort(Port *outPort)
{
   if (this->outPort != nullptr && outPort != nullptr)
       Block::unsetCalculated(outPort->GetBlock());
   this->outPort = outPort;
   if (outPort != nullptr)
       outPort->setLink(this);
}

QLine* Link::getLine() {
   return line;
}

bool Link::IsCycled()
{
   return isCycled;
}

void Link::SetCycled()
{
   isCycled = true;
   //cycledLinks.push_back(line);
}

void Link::UnSetCycled()
{
   isCycled = false;
   //cycledLinks.erase(line);
}

void Link::Draw(QPainter *p)
{
   if(inPort == nullptr||outPort== nullptr)
       return;
   p->setPen(QPen(Qt::black, 3));
   line = new QLine(inPort->Rect->Center()->X+7,inPort->Rect->Center()->Y,outPort->Rect->Center()->X-7,outPort->Rect->Center()->Y);
   p->drawLine(*line);
   p->setPen(QPen(Qt::black, 1));
}

std::ostream& operator <<(std::ostream& os, Link& link)
{
    Block* outBlock = link.getOutPort()->GetBlock();
    std::vector<Port*> inPorts = outBlock->getInPorts();

    int idxInputPort = std::find(inPorts.begin(), inPorts.end(), link.getOutPort()) - inPorts.begin();

    os << link.getInPort()->GetBlock() << "-";
    os << idxInputPort << ":";
    os << outBlock;
    return os;
}
