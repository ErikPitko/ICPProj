#ifndef PORT_H
#define PORT_H

#include <vector>
#include "block.h"
#include "link.h"
#include "myrect.h"
#include "drawableobject.h"
class Port : public DrawableObject
{
private:
    Block* _block;
    std::vector<Link> _link;
    //Color _backgroundColor;
public:
    MyRect* Rect;
    static const int PORT_SIZE = 15;
    std::vector<Link> GetLinks();
    Link* GetFirstLink();
    Block* GetBlock();
    Port (MyRect*,Block*);
    Port (MyRect*, Block*/*,Color*/);
    void setLink(Link*);
    void unSetLink();
    void virtual Draw(/*AnchorPane pane*/) override;
};

#endif // PORT_H
