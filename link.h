#ifndef LINK_H
#define LINK_H

#include <vector>
#include "port.h"
#include "drawableobject.h"
class Link : public DrawableObject
{
private:
    Port inPort;
    Port outPort;
    //Line line;
    bool isCycled;
    //static std::vector<Line> cycledLinks = new std::vector<Line>();
public:
    //Rectangle tmpPane;
    //Text txt;
    Link();
    Link(const Link&);
    Link(Port inPort, Port outPort);
    Port getInPort();
    void setOutPort();
    //Line getLine();
    void Remove();
    bool IsCycled();
    void SetCycled();
    void UnSetCycled();
    void virtual Draw(/*AnchorPane pane*/) override;
};

#endif // LINK_H
