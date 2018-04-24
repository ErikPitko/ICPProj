#include "link.h"
#include <iostream>
   Link::Link() : DrawableObject()
   {
            //line = new Line();
            isCycled = false;
   }
   Link::Link(const Link& link) : DrawableObject()
   {
            //line = link.line;
            setOutPort(link.outPort);
            setInPort(link.inPort);
            isCycled = link.isCycled;
        }

   Link::Link(Port *inPort, Port *outPort) : DrawableObject()
   {
            setInPort(inPort);
            //line = new Line();
            setOutPort(outPort);
            isCycled = false;
   }
   Port* Link::getInPort()
   {
           return inPort;
   }

   void Link::setInPort(Port *inPort)
   {
       std::cout << outPort->GetFirstLink()<<std::endl;
       if (outPort != nullptr && inPort != nullptr)
           Block::unsetCalculated(outPort->GetBlock());
       this->inPort = inPort;
       if (inPort != nullptr)
           inPort->setLink(this);
   }
   Port* Link::getOutPort()
   {
       return outPort;
   }

   void Link::setOutPort(Port *outPort)
   {
       if (this->outPort != nullptr && outPort != nullptr)
           Block::unsetCalculated(outPort->GetBlock());
       this->outPort = outPort;
       if (outPort != nullptr)
           outPort->setLink(this);
   }

   /*Link::Line getLine() {
       return line;
   }*/

   void Link::Remove()
   {
       this->outPort = nullptr;
       this->inPort = nullptr;
   }

   bool Link::IsCycled()
   {
       return isCycled;
   }

   void Link::SetCycled()
   {
       isCycled = true;
       //cycledLinks.push_back(line);
   }

   void Link::UnSetCycled()
   {
       isCycled = false;
       //cycledLinks.erase(line);
   }
   void Link::Draw(/*AnchorPane pane*/)
   {
       /*if(inPort == null||outPort== null)
           return;
       if(!pane.getChildren().contains(line))
       {
           line.setStartX(inPort.Rect.Center().X + Port.PORT_SIZE / 2 + 1);
           line.setStartY(inPort.Rect.Center().Y);
           line.setEndX(outPort.Rect.Center().X - (Port.PORT_SIZE / 2 + 1));
           line.setEndY(outPort.Rect.Center().Y);
           if(isCycled)
               line.setStroke(Color.RED);
           else line.setStroke(Color.BLACK);
           line.setStrokeWidth(3);
           line.setOnMouseEntered(event ->
           {
               tmpPane = new Rectangle();
               tmpPane.setX(event.getX()+1);
               tmpPane.setY(event.getY()+1);
               txt = new Text();
               txt.setText(String.valueOf(inPort.GetBlock().getValue()));
               txt.setFill(Color.BLACK);
               txt.setX(event.getX()+txt.getBoundsInLocal().getWidth()/2);
               txt.setY(event.getY()-txt.getBoundsInLocal().getHeight()/3);
               tmpPane.setX(event.getX()+1);
               tmpPane.setY(event.getY()-txt.getBoundsInLocal().getHeight());
               tmpPane.setHeight(txt.getBoundsInLocal().getHeight());
               tmpPane.setWidth(txt.getBoundsInLocal().getWidth()+20);
               tmpPane.setFill(Color.WHITE);
               tmpPane.setStroke(Color.BLACK);
               pane.getChildren().add(tmpPane);
               pane.getChildren().add(txt);

           });
           line.setOnMouseExited(event ->
           {
               pane.getChildren().remove(tmpPane);
               pane.getChildren().remove(txt);
           });
           pane.getChildren().add(line);
       }*/
   }

