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

#ifndef PORT_H
#define PORT_H
class Block;
class Port;
class Link;
#include <vector>
#include "block.h"
#include "link.h"
#include "port.h"
#include "myrect.h"
#include "drawableobject.h"
class Port : public DrawableObject
{
private:
    Block* _block = nullptr;
    std::vector<Link*> *_link;
    //Color _backgroundColor;
public:
    MyRect* Rect = nullptr;
    static const int PORT_SIZE = 15;
    std::vector<Link*>* GetLinks();
    Link* GetFirstLink();
    Block* GetBlock();
    Port (MyRect*,Block*);
    virtual ~Port();
    //Port (MyRect*, Block*/*,Color*/);
    void setLink(Link*);
    void unSetLink();
    void virtual Draw(QPainter*) override;

    friend std::ostream& operator <<(std::ostream& os, Port& port)
    {
        os << port.GetBlock() << ';' << &port;
        return os;
    }
};

#endif // PORT_H
