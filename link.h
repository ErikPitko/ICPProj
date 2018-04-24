#ifndef LINK_H
#define LINK_H

class Port;
#include <vector>
#include "port.h"
#include "drawableobject.h"

class Link : public DrawableObject
{
private:
    Port *inPort;
    Port *outPort;
    //Line line;
    bool isCycled;
    //static std::vector<Line> cycledLinks = new std::vector<Line>();
public:
    //Rectangle tmpPane;
    //Text txt;
    Link();
    Link(const Link&);
    Link(Port*, Port*);
    Port* getInPort();
    Port* getOutPort();
    void setInPort(Port*);
    void setOutPort(Port*);
    //Line getLine();
    void Remove();
    bool IsCycled();
    void SetCycled();
    void UnSetCycled();
    void virtual Draw(/*AnchorPane pane*/) override;
};

#endif // LINK_H
