#include "port.h"
#include <algorithm>

    std::vector<Link> Port::GetLinks()
    {
        return _link;
    }

    Link* Port::GetFirstLink()
    {
        if(_link.size()>0)
            return &_link[0];
        return nullptr;
    }

    void Port::setLink(Link *link)
    {
        if(std::find(_link.begin(),_link.end(),*link) == _link.end())
            this->_link.push_back(*link);
    }

    void Port::unSetLink()
    {
        for (int i =0;i<_link.size();)
        {
            Link middle = _link[i];
            if(middle.getOutPort() != nullptr)
                Block::unsetCalculated(middle.getOutPort()->GetBlock());
            Port *in = middle.getOutPort();
            if(in != nullptr) {
                int pos = std::find(in->GetLinks().begin(), in->GetLinks().end(), middle) - in->GetLinks().begin();
                in->GetLinks().erase(in->GetLinks().begin()+pos);
            }
            int pos = std::find(_link.begin(), _link.end(), middle) - _link.begin();
            _link.erase(_link.begin()+pos);
            //FXMLExampleController.AnchorPanel.getChildren().remove(middle.tmpPane);
            //FXMLExampleController.AnchorPanel.getChildren().remove(middle.txt);
            //FXMLExampleController.AnchorPanel.getChildren().remove(middle.getLine());
            middle.Remove();
        }
    }

    Block* Port::GetBlock()
    {
        return _block;
    }

    Port::Port(MyRect* rect, Block* block) : DrawableObject()
    {
        _link = std::vector<Link>();
        Rect = rect;
        _block = block;
        //_backgroundColor = Color.WHITE;
    }

    /*Port::Port(MyRect* rect, Block* block,Color color)
    {
        _link = new std::vector<Link>();
        Rect = rect;
        _block = block;
        //_backgroundColor = color;
    }*/

    void Port::Draw(/*AnchorPane pane*/)
    {
        //Rect.setFill(_backgroundColor);
        //Rect.setStroke(Color.BLACK);
        //pane.getChildren().add(Rect);
    }
