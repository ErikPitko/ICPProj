#include "port.h"
#include <algorithm>

    Port::std::vector<Link> GetLinks()
    {
        return _link;
    }

    Port::Link GetFirstLink()
    {
        if(_link.size()>0)
            return _link[0];
        return nullptr;
    }

    void Port::setLink(Link link)
    {
        if(std::find(_link.begin(),_link.end(),link) == _link.end())
            this._link.add(link);
    }

    void Port::unSetLink()
    {
        for (int i =0;i<_link.size();)
        {
            Link middle = _link[i];
            if(middle.getOutPort() != nullptr)
                Block.unsetCalculated(middle.getOutPort().GetBlock());
            Port in = middle.getOutPort();
            if(in != nullptr) {
                in.GetLinks().erase(middle);
            }
            _link.erase(middle);
            //FXMLExampleController.AnchorPanel.getChildren().remove(middle.tmpPane);
            //FXMLExampleController.AnchorPanel.getChildren().remove(middle.txt);
            //FXMLExampleController.AnchorPanel.getChildren().remove(middle.getLine());
            middle.Remove();
        }
    }

    Port::Block GetBlock()
    {
        return _block;
    }

    Port::Port(Rect rect, Block block)
    {
        _link = new std::vector<Link>();
        Rect = rect;
        _block = block;
        _backgroundColor = Color.WHITE;
    }

    Port::Port(Rect rect, Block block,Color color)
    {
        _link = new std::vector<Link>();
        Rect = rect;
        _block = block;
        _backgroundColor = color;
    }

    void virtual Port::Draw(/*AnchorPane pane*/)
    {
        //Rect.setFill(_backgroundColor);
        //Rect.setStroke(Color.BLACK);
        //pane.getChildren().add(Rect);
    }
