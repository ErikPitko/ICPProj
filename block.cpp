#include "block.h"

int Block::stepCounter;

Block::Block(EBlock eBlock, MyRect* rect) : DrawableObject()
{
    this->_eBlock = eBlock;
    _rect = rect;
    stepCounter = 0;
    if(_eBlock!= OUT)
        _outPort = new Port(new MyRect(_rect->XMax()-(Port::PORT_SIZE+Port::PORT_SIZE/2),_rect->y()+_rect->height()/2-Port::PORT_SIZE/2,Port::PORT_SIZE,Port::PORT_SIZE),this);
}

Block::Block(EBlock eBlock, MyRect* rect, double value) : DrawableObject()
{
    this->_eBlock = eBlock;
    _rect= rect;
    this->value = value;
    stepCounter = 0;
    if(_eBlock!= OUT)
        _outPort = new Port(new MyRect(_rect->XMax()-(Port::PORT_SIZE+Port::PORT_SIZE/2),_rect->y()+_rect->height()/2-Port::PORT_SIZE/2,Port::PORT_SIZE,Port::PORT_SIZE),this);
}

Block::~Block()
{
    std::cout << std::endl;
//    if(_outPort != nullptr)
//    {
//        for (int i = 0; i < _outPort->GetLinks().size(); i++) {
//            unsetCalculated(_outPort->GetBlock());
//            _outPort->unSetLink();
//        }
//    }
//    for (int i = 0; i < inPorts.size();i++)
//    {
//        inPorts[i]->unSetLink();
//    }

    if (_rect != nullptr)
        delete _rect;
    for(Port* port:inPorts)
    {
        delete port;
    }
    inPorts.clear();
    if(_outPort != nullptr)
        delete _outPort;
    if(_resizeRect != nullptr)
        delete _resizeRect;
    std::cout << "\tBlock: " << this << " deleted." << std::endl;
    std::cout << std::endl;
}

void Block::calculatePortsToMiddle()
{
    recalculateHeights();
    double step = _rect->height() / inPorts.size();
    double div = step / 2;
    for (int i = 0; i < inPorts.size(); i++)
    {
        inPorts[i]->Rect->setY((int) (_rect->y() + (i + 1) * step - div- Port::PORT_SIZE / 2));
        inPorts[i]->Rect->setHeight(Port::PORT_SIZE);
    }
}

void Block::completeDeleteBlock()
{
    Widget::BlockList->erase(std::find(Widget::BlockList->begin(),Widget::BlockList->end(),Widget::EditBlock));
    delete this;
}

bool Block::recalculateHeights()
{
    if(inPorts.size()*Port::PORT_SIZE >= _rect->height()-10)
    {
        //_rect->setY(inPorts.size()*Port::PORT_SIZE + inPorts.size()*15);
        _rect->setHeight(inPorts.size()*(Port::PORT_SIZE+5));
        if(_outPort!= nullptr)
        {
            _outPort->Rect->setY(_rect->y()+_rect->height()/2-Port::PORT_SIZE/2);
            _outPort->Rect->setHeight(Port::PORT_SIZE);
        }
        return true;
    }
    return false;
}

void Block::genInPort() {
    MyRect* newport = new MyRect(_rect->x()+Port::PORT_SIZE/2,_rect->y()+Port::PORT_SIZE/2 + Port::PORT_SIZE +15*inPorts.size(),Port::PORT_SIZE,Port::PORT_SIZE);
    this->inPorts.push_back(new Port(newport, this));
    calculatePortsToMiddle();
}

void Block::setValue(double value) {
    this->value = value;
//    if(debugDisp != null) {
//        debugDisp.setText(String.valueOf(value));
//        debugDisp.setX(_rect.getX() + _rect.getWidth() - debugDisp.getBoundsInLocal().getWidth());
//    }
//    if(disp != null) {
//        disp.setText(String.valueOf(value));
//        disp.setX(_rect.Center().X - disp.getBoundsInLocal().getWidth()/2);
//    }
}

bool Block::isCycled(Block* comparing, Block* block) {
        bool found = false;

        if(comparing == nullptr) {
            comparing = block;
        }else {
            if(comparing == block)
                return true;
        }
        if(block == nullptr)
            return found;

        for (Port *port : block->getInPorts()) {
            Link* frontLink = port->GetFirstLink();
            if (frontLink != nullptr) {
                found = isCycled(comparing, frontLink->getInPort()->GetBlock());
                if(found)
                    break;
            }
        }
        return found;
}

double Block::compute(Block* block) {
    if(isCycled(nullptr, block))
    {
        std::cerr << "cycle detected" << std::endl;
        return 0;
    }
    bool first = true;
    if (block->calculated)
        return block->value;
    for (Port *port : block->getInPorts()) {
        Link* frontLink = port->GetFirstLink();
        if (frontLink != nullptr) {
            double value = compute(frontLink->getInPort()->GetBlock());
//            if(Block.stepCounter == Panel.stepCounter)
//            {
//                return value;
//            }
//            else
//            {
//                ImageView image = block.getImageView();
//                ColorAdjust blackout = new ColorAdjust();
//                blackout.setBrightness(-0.5);
//                image.setEffect(blackout);
//                image.setCache(true);
//                image.setCacheHint(CacheHint.SPEED);
//            }

//            System.out.println(Block.stepCounter);
            if (first) {
                first = false;
                block->setValue(value);
                continue;
            }
            switch (block->getType()) {
            case ADD:
                block->setValue(block->value + value);
                break;
            case SUB:
                block->setValue(block->value - value);
                break;
            case MUL:
                block->setValue(block->value * value);
                break;
            case DIV:
                block->setValue(block->value / value);
                break;
            default:
                block->setValue(value);
            }
        }
    }
    if(block->getType()!= IN)
        stepCounter++;
    block->calculated = true;
    return block->value;
}

void Block::unsetCalculated(Block* block) {
    if(block == nullptr)
        return;
    if(block->getType() == IN)
        return;
    block->calculated = false;
    block->setValue(0);
    if(block->_outPort == nullptr)
        return;
    for(unsigned i= 0;i<block->_outPort->GetLinks()->size();i++) {
        Link* link = (*block->_outPort->GetLinks())[i];
        if (link == nullptr || link->getOutPort() == nullptr)
            return;
        unsetCalculated(link->getOutPort()->GetBlock());
    }
}

std::vector<Port*> Block::getInPorts()
{
    return this->inPorts;
}

Port* Block::getOutPort(){ return _outPort; }

void Block::setOutPort(Port* p)
{
    _outPort = p;
}

void Block::setInPorts(std::vector<Port*> portList)
{
    inPorts.clear();
    inPorts.insert(inPorts.end(), portList.begin(), portList.end());
}

void Block::setInPort(int index, Port* newInPort)
{
    inPorts[index] = newInPort;
    //calculatePortsToMiddle();
}

double Block::getValue() const {
    return value;
}

MyRect* Block::getResizeRect(){return _resizeRect;}

EBlock Block::getType() const{
    return _eBlock;
}

void Block::setRectPosition(Point2D* position)
{
    _rect->setX(position->X);
    _rect->setY(position->Y);
}

MyRect* Block::getRect() const
{
    return _rect;
}

void Block::setRect(MyRect* rect)
{
    _rect = rect;
}

void Block::setType(EBlock eBlock) {
    _eBlock = eBlock;
    unsetCalculated(this);
}

void Block::Move(Point2D *move)
{
    _rect->moveTo(_rect->x() + move->X,_rect->y() + move->Y);
    _resizeRect->moveTo(_resizeRect->x() + move->X,_resizeRect->y() + move->Y);
    if(_outPort != nullptr) {
        _outPort->Rect->moveTo(_outPort->Rect->x() + move->X,_outPort->Rect->y() + move->Y);
    }
    for (Port *inport: inPorts)
    {
        inport->Rect->moveTo(inport->Rect->x() + move->X,inport->Rect->y() + move->Y);
    }
//    debugDisp.setX(debugDisp.getX()+deltaX);
//    debugDisp.setY(debugDisp.getY()+deltaY);
//    if(disp != null)
//    {
//        disp.setX(disp.getX() + deltaX);
//        disp.setY(disp.getY() + deltaY);
//    }
//    if(_outPort != null)
//        for(int i = 0;i<_outPort.GetLinks().size();i++)
//            if(_outPort.GetLinks().get(i)!= null)
//            {
//                FXMLExampleController.AnchorPanel.getChildren().remove(_outPort.GetLinks().get(i).getLine());
//                _outPort.GetLinks().get(i).Draw(FXMLExampleController.AnchorPanel);
//            }
//    for (Port inport: inPorts)
//    {
//        inport.Rect.setX(inport.Rect.getX()+deltaX);
//        inport.Rect.setY(inport.Rect.getY()+deltaY);
//        for(int i = 0;i<inport.GetLinks().size();i++)
//            if(inport.GetLinks().get(i)!= null)
//            {
//                FXMLExampleController.AnchorPanel.getChildren().remove(inport.GetLinks().get(i).getLine());
//                inport.GetLinks().get(i).Draw(FXMLExampleController.AnchorPanel);
//            }
//    }
}

void Block::Resize(Point2D *resize)
{
    if(resize == nullptr)
        return;
    bool anyIntersects = false;

    if(_rect->width()+resize->X > Block::MINBLOCKSIZE && _rect->width()+resize->X < Block::MAXBLOCKSIZE)
    {
        for(int i =0 ;i< Widget::BlockList->size();i++)
        {
            if ((*Widget::BlockList)[i] != this)
                if (MyRect(_rect->x(),_rect->y(),_rect->width()+resize->X,_rect->height()).intersect((*Widget::BlockList)[i]->getRect()))
                    anyIntersects = true;
            if(anyIntersects == true)
                break;
        }
        if(!anyIntersects)
            _rect->setWidth(_rect->width()+resize->X);
    }
    anyIntersects = false;
     std::cout << _rect->height()<<std::endl;
    if(_rect->height()+resize->Y >= inPorts.size()*(Port::PORT_SIZE+2))
        if(_rect->height() + resize->Y > Block::MINBLOCKSIZE && _rect->height()+resize->Y < Block::MAXBLOCKSIZE)
        {
            for(int i =0 ;i< Widget::BlockList->size();i++)
            {
                if ((*Widget::BlockList)[i] != this)
                    if (MyRect(_rect->x(),_rect->y(),_rect->width(),_rect->height()+resize->Y).intersect((*Widget::BlockList)[i]->getRect()))
                        anyIntersects = true;
                if(anyIntersects == true)
                    break;
            }
            if(!anyIntersects)
                _rect->setHeight(_rect->height() + resize->Y);
        }
    _resizeRect->setX(_rect->XMax()-8);
    _resizeRect->setY(_rect->YMax()-8);
    _resizeRect->setWidth(8);
    _resizeRect->setHeight(8);
    calculatePortsToMiddle();
    if(_outPort!= nullptr)
    {
        _outPort->Rect->setX(_rect->XMax() - Port::PORT_SIZE - 5);
        _outPort->Rect->setY(_rect->Center()->Y - Port::PORT_SIZE / 2);
        _outPort->Rect->setWidth(Port::PORT_SIZE);
        _outPort->Rect->setHeight(Port::PORT_SIZE);
    }
//    debugDisp.setX(_rect.getX() + _rect.getWidth() - debugDisp.getBoundsInLocal().getWidth());
//    debugDisp.setY(_rect.getY() - 5);
//    if(disp != null)
//    {
//        disp.setX(_rect.Center().X - disp.getBoundsInLocal().getWidth() / 2);
//        disp.setY(_rect.Center().Y + 5);
//    }
}

void Block::Draw(QPainter *p)
{
    switch (_eBlock)
      {
      case 0: { image = QImage("./ADD.png"); } break;
      case 1: { image = QImage("./SUB.png"); } break;
      case 2: { image = QImage("./MUL.png"); } break;
      case 3: { image = QImage("./DIV.png"); } break;
      case 4: { image = QImage("./IN.png"); } break;
      case 5: { image = QImage("./OUT.png"); } break;
      }
    p->drawImage(*_rect,image);
    _resizeRect = new MyRect(_rect->XMax()-8,_rect->YMax()-8,8,8);
    QBrush brush(Qt::white);
    p->fillRect(*_resizeRect,brush);
    p->drawRect(*_resizeRect);
    if(_outPort!= nullptr)
    {
        QBrush brush(Qt::red);
        p->fillRect(*_outPort->Rect,brush);
        _outPort->Draw(p);
    }
    for (Port *port: inPorts)
    {
        QBrush brush(Qt::white);
        p->fillRect(*port->Rect,brush);
        port->Draw(p);
    }

//    debugDisp = new Text(String.valueOf(value));
//    //debugDisp.setFont(font);
//    debugDisp.setX(_rect.getX() + _rect.getWidth() - debugDisp.getBoundsInLocal().getWidth());
//    debugDisp.setY(_rect.getY() - 5);
//    debugDisp.setMouseTransparent(true);
//    if (_eBlock == EBlock.OUT) {
//        disp = new Text(String.valueOf(value));
//        disp.setMouseTransparent(true);
//        disp.setFont(font);
//        disp.setX(_rect.Center().X - disp.getBoundsInLocal().getWidth()/2);
//        disp.setY(_rect.Center().Y + 5);
//        disp.setTextAlignment(TextAlignment.CENTER);
//        pane.getChildren().addAll(_rect, image, debugDisp, disp);
//    }else
//        pane.getChildren().addAll(_rect, image, debugDisp);
}

std::istream& operator >>(std::istream& is, Block& block)
{
    char trash;
    if(block.getRect() != nullptr)
        delete block.getRect();
    MyRect* rect = new MyRect(0,0,0,0);
    is >> *rect;
    block.setRect(rect);
    is >> trash;

    double temp;
    is >> temp;
    is >> trash;

    unsigned numInPorts;
    is >> numInPorts;
    is >> trash;
    for (unsigned i = 0; i < numInPorts; i++)
    {
        block.genInPort();
    }

    int type;
    is >> type;
    block.setType(static_cast<EBlock>(type));
    block.setValue(temp);
    return is;
}

std::ostream& operator <<(std::ostream& os, Block& block)
{
    os << *block.getRect() << ';' << block.getValue() << ';' << block.getInPorts().size() << ';' << block.getType();
    return os;
}
