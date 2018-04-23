#include "block.h"

Block::Block(EBlock eBlock, Rect rect) : DrawableObject()
{
    eBlock = eBlock;
    _rect = rect;
    _outPort = new Port(new Rect(_rect.XMax()-(Port.PORT_SIZE+Port.PORT_SIZE/2),_rect.getY()+_rect.getHeight()/2-Port.PORT_SIZE/2,Port.PORT_SIZE,Port.PORT_SIZE),this,Color.RED);
}

Block::Block(EBlock eBlock, Rect rect, double value) : DrawableObject()
{
    eBlock = eBlock;
    _rect = rect;
    value = value;
    _outPort = new Port(new Rect(_rect.XMax()-(Port.PORT_SIZE+Port.PORT_SIZE/2),_rect.getY()+_rect.getHeight()/2-Port.PORT_SIZE/2,Port.PORT_SIZE,Port.PORT_SIZE),this,Color.RED);
}

void Block::calculatePortsToMiddle()
{
    recalculateHeights();
    double step = _rect->getHeight() / inPorts.size();
    double div = step / 2;
    for (int i = 0; i < inPorts.size(); i++)
    {
        inPorts.get(i).Rect.setY((int) (_rect.getY() + (i + 1) * step - div- Port.PORT_SIZE / 2));
    }
}

bool Block::recalculateHeights()
{
    if(inPorts.size()*Port.PORT_SIZE >= _rect.getHeight()-10)
    {
        _rect.setY(inPorts.size()*Port.PORT_SIZE + inPorts.size()*15);
        _outPort.Rect.setY(_rect.getY()+_rect.getHeight()/2-Port.PORT_SIZE/2);
        return true;
    }
    return false;
}

void Block::genInPort() {
    Rect newport = new Rect(_rect.getX()+Port.PORT_SIZE/2,_rect.getY()+Port.PORT_SIZE/2 + Port.PORT_SIZE +5*inPorts.size(),Port.PORT_SIZE,Port.PORT_SIZE);
    this.inPorts.add(new Port(newport, this));
    CalculatePortsToMiddle();
}

void Block::setValue(double value) {
    this.value = value;
    if(debugDisp != null) {
        debugDisp.setText(String.valueOf(value));
        debugDisp.setX(_rect.getX() + _rect.getWidth() - debugDisp.getBoundsInLocal().getWidth());
    }
    if(disp != null) {
        disp.setText(String.valueOf(value));
        disp.setX(_rect.Center().X - disp.getBoundsInLocal().getWidth()/2);
    }
}

static bool Block::isCycled(Block comparing, Block block) {
        boolean found = false;

        if(comparing == null) {
            comparing = block;
        }else {
            if(comparing == block)
                return true;
        }
        if(block == null)
            return found;

        for (Port port : block.getInPorts()) {
            Link frontLink = port.GetFirstLink();
            if (frontLink != null) {
                found = isCycled(comparing, frontLink.getInPort().GetBlock());
                if(found)
                    break;
            }
        }
        return found;
}

static double Block::compute(Block block) {
    if(isCycled(null, block)) {
        System.err.println("CYCLE !");
        return 0;
    }
    boolean first = true;
    if (block.calculated)
        return block.value;
    for (Port port : block.getInPorts()) {
        Link frontLink = port.GetFirstLink();
        if (frontLink != null) {
            double value = compute(frontLink.getInPort().GetBlock());
            if(Block.stepCounter == Panel.stepCounter) {
                return value;
            }
            else
            {
                ImageView image = block.getImageView();
                ColorAdjust blackout = new ColorAdjust();
                blackout.setBrightness(-0.5);
                image.setEffect(blackout);
                image.setCache(true);
                image.setCacheHint(CacheHint.SPEED);

            }

            System.out.println(Block.stepCounter);
            if (first) {
                first = false;
                block.setValue(value);
                continue;
            }
            switch (block.getType()) {
            case ADD:
                block.setValue(block.value + value);
                break;
            case SUB:
                block.setValue(block.value - value);
                break;
            case MUL:
                block.setValue(block.value * value);
                break;
            case DIV:
                block.setValue(block.value / value);
                break;
            default:
                block.setValue(value);
            }
        }
    }
    if(block.getType()!= EBlock.IN)
        Block.stepCounter++;
    block.calculated = true;
    return block.value;
}

static void Block::unsetCalculated(Block block) {
    if(block == null)
        return;
    if(block.getType() == EBlock.IN)
        return;
    block.calculated = false;
    block.setValue(0);
    if(block._outPort== null)
        return;
    for(int i= 0;i<block._outPort.GetLinks().size();i++) {
        Link link = block._outPort.GetLinks().get(i);
        if (link == null || link.getOutPort() == null)
            return;
        unsetCalculated(link.getOutPort().GetBlock());
    }
}

std::vector<Port> getInPorts()
{
    return inPorts;
}

Port Block::GetOutPort(){ return _outPort; }

void Block::SetOutPort(Port p)
{
    _outPort = p;
}

void Block::SetInPorts(List<Port> portList)
{
    inPorts.clear();
    inPorts.addAll(portList);
}

void Block::SetInPort(int index, Port newInPort)
{
    inPorts.set(index,newInPort);
    CalculatePortsToMiddle();
}

double getValue() {
    return value;
}

Rect Block::GetResizeRect(){return _resizeRect;}

EBlock Block::getType() {
    return _eBlock;
}

void Block::setRectPosition(Point2D position)
{
    _rect.setX(position.X);
    _rect.setY(position.Y);
}

Rect Block::getRect()
{
    return _rect;
}

void Block::setType(EBlock eBlock) {
    _eBlock = eBlock;
    unsetCalculated(this);
}

void Block::Move(double deltaX, double deltaY)
{
//    _rect.setX(_rect.getX() + deltaX);
//    _rect.setY(_rect.getY() + deltaY);
//    _resizeRect.setX(_resizeRect.getX() + deltaX);
//    _resizeRect.setY(_resizeRect.getY() + deltaY);
//    if(_outPort != null) {
//        _outPort.Rect.setX(_outPort.Rect.getX() + deltaX);
//        _outPort.Rect.setY(_outPort.Rect.getY() + deltaY);
//    }
//    image.setX(image.getX() + deltaX);
//    image.setY(image.getY() + deltaY);
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

void Block::Resize(double deltaX,double deltaY)
{
//    boolean anyIntersects = false;
//    if(_rect.getWidth() + deltaX > MINBLOCKSIZE  && _rect.getWidth()+deltaX < MAXBLOCKSIZE)
//    {
//        for(int i =0 ;i< Panel.BlockList.size();i++)
//        {
//            if (Panel.BlockList.get(i) != this)
//                if (new Rect(_rect.getX(),_rect.getY(),_rect.getWidth()+deltaX,_rect.getHeight()).Intersect(Panel.BlockList.get(i).getRect()))
//                    anyIntersects = true;
//            if(anyIntersects == true)
//                break;
//        }
//        if(!anyIntersects)
//            _rect.setWidth(_rect.getWidth() + deltaX);
//    }
//    anyIntersects = false;
//    if(_rect.getHeight()+deltaY >= inPorts.size()*(Port.PORT_SIZE+5))
//        if(_rect.getHeight() + deltaY > MINBLOCKSIZE && _rect.getHeight()+deltaY < MAXBLOCKSIZE)
//        {
//            for(int i =0 ;i< Panel.BlockList.size();i++)
//            {
//                if (Panel.BlockList.get(i) != this)
//                    if (new Rect(_rect.getX(),_rect.getY(),_rect.getWidth(),_rect.getHeight()+deltaY).Intersect(Panel.BlockList.get(i).getRect()))
//                        anyIntersects = true;
//                if(anyIntersects == true)
//                    break;
//            }
//            if(!anyIntersects)
//                _rect.setHeight(_rect.getHeight() + deltaY);
//        }
//    _resizeRect.setX(_rect.XMax()-8);
//    _resizeRect.setY(_rect.YMax()-8);
//    debugDisp.setX(_rect.getX() + _rect.getWidth() - debugDisp.getBoundsInLocal().getWidth());
//    debugDisp.setY(_rect.getY() - 5);
//    if(disp != null)
//    {
//        disp.setX(_rect.Center().X - disp.getBoundsInLocal().getWidth() / 2);
//        disp.setY(_rect.Center().Y + 5);
//    }
//    CalculatePortsToMiddle();
//    if(_outPort!= null)
//    {
//        _outPort.Rect.setX(_rect.XMax() - Port.PORT_SIZE - 5);
//        _outPort.Rect.setY(_rect.Center().Y - Port.PORT_SIZE / 2);
//        for (Link outLinks : _outPort.GetLinks()) {
//            outLinks.getLine().setStartX(_outPort.Rect.Center().X + Port.PORT_SIZE / 2);
//            outLinks.getLine().setStartY(_outPort.Rect.Center().Y);
//        }
//    }

//    for (Port inport: inPorts)
//    {
//        for (Link inLinks: inport.GetLinks())
//        {
//            inLinks.getLine().setEndX(inport.Rect.Center().X-Port.PORT_SIZE/2);
//            inLinks.getLine().setEndY(inport.Rect.Center().Y);
//        }
//    }
//    image.setFitWidth(_rect.getWidth());
//    image.setFitHeight(_rect.getHeight());
}

void Block::DeleteBlock()
{
//    FXMLExampleController.AnchorPanel.getChildren().remove(_rect);
//    FXMLExampleController.AnchorPanel.getChildren().remove(image);
//    FXMLExampleController.AnchorPanel.getChildren().remove(debugDisp);
//    if(disp != null)
//        FXMLExampleController.AnchorPanel.getChildren().remove(disp);
    if(_outPort!= null)
    {
        for (int i = 0; i < _outPort.GetLinks().size(); i++) {
            unsetCalculated(_outPort.GetBlock());
            _outPort.unSetLink();
        }
//        FXMLExampleController.AnchorPanel.getChildren().remove(_outPort.Rect);
    }
    for (int i = 0; i < inPorts.size();i++)
    {
        inPorts.get(i).unSetLink();
//        FXMLExampleController.AnchorPanel.getChildren().remove(inPorts.get(i).Rect);
    }
//    FXMLExampleController.AnchorPanel.getChildren().remove(_resizeRect);
//    Panel.BlockList.remove(this);
}

void Block::Draw()
{
//    image = new ImageView(new Image(getClass().getResourceAsStream("/Res/"+_eBlock.toString()+".png")));
//    image.setFitHeight(_rect.getHeight());
//    image.setFitWidth(_rect.getWidth());
//    image.setX(_rect.getX());
//    image.setY(_rect.getY());
//    Font font = null;
//    try {
//        font = Font.loadFont(new FileInputStream(new File("src/Res/fonts/Crasns.ttf")), 15);
//    } catch (FileNotFoundException e) {
//        e.printStackTrace();
//    }

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
//    _resizeRect = new Rect(_rect.XMax()-8,_rect.YMax()-8,8,8);
//    _resizeRect.setFill(Color.WHITE);
//    _resizeRect.setStroke(Color.BLACK);
//    pane.getChildren().add(_resizeRect);
//    for (Port p: inPorts)
//    {
//        p.Draw(pane);
//        for (Link link: p.GetLinks()) {
//            if(link!= null)
//            {
//                link.Draw(pane);
//            }
//        }
//    }
//    if(_outPort!= null)
//        _outPort.Draw(pane);
}
