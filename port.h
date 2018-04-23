#ifndef PORT_H
#define PORT_H

#include <vector>
#include "drawableobject.h"
class Port : DrawableObject
{
private:
    Block _block;
    std::vector<Link> _link;
    Color _backgroundColor;
public:
    Rect Rect;
    static const int PORT_SIZE = 15;
    std::vector<Link> GetLinks();
    Link GetFirstLink();
    Block GetBlock();
    Port(Rect,Block);
    Port(Rect, Block,Color);
    void setLink(Link);
    void unSetLink();
    void virtual Draw(/*AnchorPane pane*/) override;
};

#endif // PORT_H
