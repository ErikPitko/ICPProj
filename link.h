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

#ifndef LINK_H
#define LINK_H

class Port;
#include <vector>
#include "port.h"
#include "drawableobject.h"
#include <QtGui>

class Link : public DrawableObject
{
private:
    Port *inPort = nullptr;
    Port *outPort = nullptr;
    QLine *line = nullptr;
    bool isCycled;
    //static std::vector<Line> cycledLinks = new std::vector<Line>();
public:
    //Rectangle tmpPane;
    //Text txt;
    Link();
    Link(const Link&);
    Link(Port*, Port*);
    virtual ~Link();
    Port* getInPort();
    Port* getOutPort();
    void setInPort(Port*);
    void setOutPort(Port*);
    QLine* getLine();
    bool IsCycled();
    void SetCycled();
    void UnSetCycled();
    void virtual Draw(QPainter*) override;
    static bool IsPointOnLine(QLine *line, Point2D *point);

};
std::ostream& operator <<(std::ostream& os, Link& link);

#endif // LINK_H
