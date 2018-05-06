#include "port.h"
#include <algorithm>
#include <iostream>

    std::vector<Link*>* Port::GetLinks()
    {
        return _link;
    }

    Link* Port::GetFirstLink()
    {
        if(_link!= nullptr)
            if(_link->size() != 0)
                return (*_link)[0];
        return nullptr;
    }

    void Port::setLink(Link *link)
    {
        if(std::find(_link->begin(),_link->end(),link) == _link->end())
           this->_link->push_back(link);
    }

    void Port::unSetLink()
    {
        for (unsigned i =0;i<_link->size();)
        {

            Link *middle = (*_link)[i];
            if(middle->getOutPort() != nullptr)
                Block::UnsetCalculated(middle->getOutPort()->GetBlock());
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
        isClicked = false;
        this->_block = block;
    }

    void Port::SetIsClicked(bool value)
    {
        isClicked = value;
    }

    bool Port::GetIsClicked()
    {
        return isClicked;
    }

    Port::~Port()
    {
        delete Rect;
        unsigned linkSize = _link->size();
        for (unsigned i = 0; i < linkSize; i++)
        {
            delete (*_link)[0];
        }
        _link->clear();
//        std::cout << "\tPort: " << this << " deleted." << std::endl;
    }

    void Port::Draw(QPainter *p)
    {
        if(isClicked)
        {
            QBrush brush(Qt::yellow);
            p->fillRect(*Rect,brush);
        }
        p->drawRect(*Rect);
        QBrush brush(Qt::white);
    }
