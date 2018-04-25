#include "port.h"
#include <algorithm>
#include <iostream>

    std::vector<Link*>* Port::GetLinks()
    {
        return _link;
    }

    Link* Port::GetFirstLink()
    {
        if(_link->size()>0)
            return _link->front();
        return nullptr;
    }

    void Port::setLink(Link *link)
    {
        if(std::find(_link->begin(),_link->end(),link) == _link->end())
           this->_link->push_back(link);
    }

    void Port::unSetLink()
    {
        for (int i =0;i<_link->size();)
        {

            Link *middle = (*_link)[i];
            if(middle->getOutPort() != nullptr)
                Block::unsetCalculated(middle->getOutPort()->GetBlock());
            Port *in = middle->getOutPort();
            if(in != nullptr) {
                std::vector<Link*>::iterator pos = std::find(in->GetLinks()->begin(), in->GetLinks()->end(), middle);
                if(pos != _link->end())
                {
                    in->GetLinks()->erase(in->GetLinks()->begin()+std::distance(_link->begin(),pos));
                }
            }
            std::vector<Link*>::iterator pos = std::find(_link->begin(), _link->end(), middle);
            if(pos != _link->end())
            {
                _link->erase(_link->begin()+std::distance(_link->begin(),pos));
            }
        }
    }

    Block* Port::GetBlock()
    {
        return _block;
    }

    Port::Port(MyRect* rect, Block* block) : DrawableObject()
    {
        _link = new std::vector<Link*>();
        Rect = rect;
        this->_block = block;
    }

    Port::~Port()
    {
        delete Rect;
        for(Link* link : (*_link))
        {
            delete link;
        }
        _link->clear();
        std::cout << "\tPort: " << this << " deleted." << std::endl;
    }

    void Port::Draw(QPainter *p)
    {
        p->drawRect(*Rect);
    }
