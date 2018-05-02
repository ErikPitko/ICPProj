#include "block.h"

int Block::stepCounter;
Block* Block::debug = nullptr;
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
    else
        disp = new QLabel("");
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
    if(inPorts.size() != 0)
    {
        double step = _rect->height() / inPorts.size();
        double div = step / 2;
        for (int i = 0; i < inPorts.size(); i++)
        {
            inPorts[i]->Rect->setY((int) (_rect->y() + (i + 1) * step - div- Port::PORT_SIZE / 2));
            inPorts[i]->Rect->setHeight(Port::PORT_SIZE);
        }
    }
}

bool Block::completeDeleteBlock()
{
    std::vector<Block*>::iterator pos = std::find(Widget::BlockList->begin(),Widget::BlockList->end(),this);
    if(pos != Widget::BlockList->end())
    {
        Widget::BlockList->erase(Widget::BlockList->begin()+std::distance(Widget::BlockList->begin(),pos));
        delete this;
        return true;
    }
    return false;
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
            if(Block::stepCounter == Widget::stepCounter)
            {
                return value;
            }
            else
            {
                debug = block;
            }
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
    Block::stepCounter = 0;
    Widget::stepCounter = 0;
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
    calculatePortsToMiddle();
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
}

void Block::Resize(Point2D *resize)
{
    if(resize == nullptr)
        return;
    if(_rect->width()+resize->X > Block::MINBLOCKSIZE && _rect->width()+resize->X < Block::MAXBLOCKSIZE)
    {
        _rect->setWidth(_rect->width()+resize->X);
    }
    if(_rect->height()+resize->Y >= inPorts.size()*(Port::PORT_SIZE+2))
        if(_rect->height() + resize->Y > Block::MINBLOCKSIZE && _rect->height()+resize->Y < Block::MAXBLOCKSIZE)
        {
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
    if(debug != nullptr)
        if(this == debug)
        {
            p->setPen(QPen(Qt::yellow, 5));
            p->drawRect(*_rect);
            p->setPen(QPen(Qt::black, 1));
        }
    _resizeRect = new MyRect(_rect->XMax()-8,_rect->YMax()-8,8,8);
    QBrush brush(Qt::white);
    p->fillRect(*_resizeRect,brush);
    p->drawRect(*_resizeRect);
    if(Widget::isDebug)
        p->drawText(_rect->x(),_rect->y(),std::to_string(value).c_str());
    if(_eBlock == OUT)
        p->drawText(_rect->x()+_rect->width()/5,_rect->y()+_rect->height()/2 ,std::to_string(value).c_str());
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
}

std::istream& operator >>(std::istream& is, Block& block)
{
    char trash;
    if(block.getRect() != nullptr)
        delete block.getRect();
    MyRect* rect = new MyRect(0,0,0,0);
    is >> *rect;
    block.setRect(rect);
    block.getOutPort()->Rect->moveTo(rect->XMax() - (Port::PORT_SIZE+Port::PORT_SIZE/2), rect->y() + rect->height()/2-Port::PORT_SIZE/2);
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
    os << *block.getRect() << ';' << ((block.getType() == IN) ? block.getValue() : 0) << ';' << block.getInPorts().size() << ';' << block.getType();
    return os;
}
