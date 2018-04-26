#include "widget.h"
#include "ui_widget.h"
#include "block.h"
#include "blockdialog.h"
Widget::Widget(QWidget *parent) : QWidget(parent),ui(new Ui::Widget)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    myMenu.addAction("Edit", this, SLOT(Edit()));
    myMenu.addAction(tr("Delete"), this, SLOT(DeleteBlock()));
    myMenu.addAction(tr("Exit"), this, SLOT(Exit()));
}
vector<Block*>* Widget::BlockList = new vector<Block*>();
Point2D *Widget::ClickPos = nullptr;
Block *Widget::EditBlock = nullptr;
bool Widget::isDebug = false;
int Widget::stepCounter = 0;
Widget::~Widget()
{
    delete ui;
}

void Widget::clearBlocks()
{
    for (Block* block : *Widget::BlockList)
    {
        delete block;
    }
    Widget::BlockList->clear();
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter.begin(this);
    for (int i = 0;i<Widget::BlockList->size();i++)
    {
        (*Widget::BlockList)[i]->Draw(&painter);
    }
    for(int i = 0;i<Widget::BlockList->size();i++)
    {
        if((*Widget::BlockList)[i]->getOutPort() != nullptr)
        {
            for(Link *link : (*(*Widget::BlockList)[i]->getOutPort()->GetLinks()))
            {
                link->Draw(&painter);
            }
        }
        for (Port *port: (*Widget::BlockList)[i]->getInPorts())
        {
            for (Link *link: *(port->GetLinks()))
            {
                if(link!= nullptr)
                {
                    link->Draw(&painter);
                }
            }
        }
    }
    painter.end();
}

void Widget::ShowContextMenu(const QPoint &pos) // this is a slot
{
    // for most widgets
    QPoint globalPos = this->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);
    myMenu.exec(globalPos);
}
void Widget::Edit()
{
    BlockDialog block;
    block.move(this->x()+ClickPos->X,this->y()+ClickPos->Y);
    block.setModal(true);
    block.exec();
}

void Widget::DeleteBlock()
{
    EditBlock->completeDeleteBlock();
    EditBlock = nullptr;
}

void Widget::Exit()
{
    myMenu.hide();
}

void Widget::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Return)
    {
        for(int i = 0; i < Widget::BlockList->size(); i++)
        {
            if((*Widget::BlockList)[i]->getType() == OUT)
                Block::compute((*Widget::BlockList)[i]);
        }
    }
    if(event->key() == Qt::Key_Space)
    {
        isDebug = true;

        Block *outBlock = nullptr;
        for(int i = 0; i < Widget::BlockList->size(); i++)
        {
            if((*Widget::BlockList)[i]->getType() == OUT && (*Widget::BlockList)[i]->getValue() == 0)
                outBlock = (*Widget::BlockList)[i];
        }
        if(outBlock != nullptr)
        {
            stepCounter++;
            Block::compute(outBlock);
        }
        else isDebug = false;
    }
    repaint();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    EditBlock = nullptr;
    typeOfEdit = NONE;
    repaint();
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(endDrag!= nullptr)
        delete endDrag;
    endDrag = new Point2D(event->x(),event->y());
    if(EditBlock != nullptr && typeOfEdit == RESIZE)
    {
        EditBlock->Resize(Point2D::vector(ClickPos,endDrag));
    }
    else if(EditBlock != nullptr && typeOfEdit == MOVE)
    {
       EditBlock->Move(Point2D::vector(ClickPos,endDrag));
    }
    else if(typeOfEdit == PLANEMOVE)
    {
        for (int i = 0;i < BlockList->size();i++)
        {
            (*BlockList)[i]->Move(Point2D::vector(ClickPos,endDrag));
        }
    }
    if(ClickPos != nullptr)
        delete ClickPos;
    ClickPos = new Point2D(event->x(),event->y());
    repaint();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(deleteLink != nullptr)
    {
        delete deleteLink;
    }
    deleteLink = nullptr;
    repaint();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    ClickPos = new Point2D(event->x(),event->y());
    if(event->button() == Qt::LeftButton)
    {
        for (int i = 0;i < BlockList->size();i++)
        {
            if((*BlockList)[i]->getResizeRect()->contains(new Point2D(event->x(),event->y())))
            {
                typeOfEdit = RESIZE;
                EditBlock = (*BlockList)[i];
                goto end;
            }
            if((*BlockList)[i]->getOutPort() != nullptr)
            {
                if((*BlockList)[i]->getOutPort()->Rect->contains(new Point2D(event->x(),event->y())))   //spojení outporty
                {
                    if(clickedPort != nullptr)      //pokud neni nakliknutý žádný port
                    {
                        if(clickedPort->GetBlock() != (*BlockList)[i] && wasInPort)  //pokud spojím 2 porty na stejném blocku
                        {
                            new Link((*BlockList)[i]->getOutPort(),clickedPort);    //spojení linků
                            wasInPort = false;
                        }
                        if(clickedPort != (*BlockList)[i]->getOutPort())    //pokud kliknu 2x na stejný port nevynuluje se ukazatel(je tam pořád uložen ten stejný
                            clickedPort = nullptr;
                        goto end;   //vyskočím z vyhledávání
                    }
                    else    //pokud neni nakliknutý
                    {
                        clickedPort = (*BlockList)[i]->getOutPort();        //nastavím nakliknutý port
                        wasInPort = false;      //a byl to inport
                        goto end;   //vyskočím z vyhledávání
                    }
                }
            }
            for(int j = 0;j<(*BlockList)[i]->getInPorts().size();j++)       //projdu všechny inpoty
            {
                if((*BlockList)[i]->getInPorts()[j]->Rect->contains(new Point2D(event->x(),event->y())))    //spojení inporty
                {
                    if(clickedPort != nullptr)  //pokud je nakliknutý null
                    {
                        if(clickedPort->GetBlock() != (*BlockList)[i] && !wasInPort)    //pokud kliknu na stejný plok a blok nebyl inport
                        {
                            if((*BlockList)[i]->getInPorts()[j]->GetLinks()->size() == 0)
                                new Link(clickedPort,(*BlockList)[i]->getInPorts()[j]); //vytvořím link
                            clickedPort = nullptr;
                            wasInPort = false;
                            goto end;
                        }
                        if(clickedPort != (*BlockList)[i]->getInPorts()[j]) //pokud kliknu 2x na stejný port nevynuluje se ukazatel(je tam pořád uložen ten stejný
                            clickedPort = nullptr;
                        goto end;   //vyskočím z vyhledávání
                    }
                    else
                    {
                        if((*BlockList)[i]->getInPorts()[j]->GetLinks()->size()==0)
                        {
                            clickedPort = (*BlockList)[i]->getInPorts()[j]; //nastavím nakliknutý port
                            wasInPort = true;   //a nebyl to inport
                        }
                        else
                        {
                            clickedPort = nullptr;
                            wasInPort = false;
                        }
                        goto end;   //vyskočím z vyhledávání
                    }
                }
            }
            if((*BlockList)[i]->getRect()->contains(new Point2D(event->x(),event->y())))
            {
                typeOfEdit = MOVE;
                EditBlock = (*BlockList)[i];
                goto end;
            }
            if((*BlockList)[i]->getOutPort() != nullptr)
            {
                for(Link *link : (*(*BlockList)[i]->getOutPort()->GetLinks()))
                {
                    if(Link::IsPointOnLine(link->getLine(),new Point2D(event->x(),event->y())))
                    {
                        deleteLink = link;
                    }
                }
            }
        }
        typeOfEdit = PLANEMOVE;
    }
    end:
    if(event->button() == Qt::RightButton)
    {
        for (int i = 0;i < BlockList->size();i++)
        {
            if((*BlockList)[i]->getRect()->contains(new Point2D(event->x(),event->y())))
            {
                typeOfEdit = EDIT;
                EditBlock = (*BlockList)[i];
                ShowContextMenu(event->pos());
                goto end2;
            }
        }
        Edit();
    }
    end2:
    repaint();
}





