#include "widget.h"
#include "ui_widget.h"
#include "block.h"
#include "blockdialog.h"
#include "loadmanager.h"
#include "aboutdialog.h"
#include "helpdialog.h"
vector<Block*>* Widget::BlockList = new vector<Block*>();
Point2D *Widget::ClickPos = nullptr;
Block *Widget::EditBlock = nullptr;
bool Widget::isDebug = false;
bool Widget::isCycleDetected = false;
int Widget::stepCounter = 0;
Widget* Widget::storeWidget;
QAction *Widget::ActionRun = nullptr;
QAction *Widget::ActionClear = nullptr;
QAction *Widget::ActionDebug = nullptr;
QAction *Widget::ActionNextStep = nullptr;
QAction *Widget::ActionExitDebug = nullptr;
Widget::Widget(QWidget *parent) : QWidget(parent),ui(new Ui::Widget)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    InstantiateMenu();
    storeWidget = this;
    myMenu.addAction("Edit", this, SLOT(Edit()));
    myMenu.addAction(tr("Delete"), this, SLOT(DeleteBlock()));
    myMenu.addAction(tr("Exit"), this, SLOT(Exit()));
    QLabel label;
    label.setText("AAA");
    label.setGeometry(100,100,100,100);
    label.show();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InstantiateMenu()
{
    QVBoxLayout *boxLayout = new QVBoxLayout(this); // Main layout of widget
    QMenuBar* menuBar = new QMenuBar();

    fileMenu = new QMenu("File");
    menuBar->addMenu(fileMenu);
    fileMenu->addAction("Open",this, SLOT(Load()));
    fileMenu->addAction("Save",this, SLOT(Save()));
    fileMenu->addAction("Exit",this, SLOT(ExitAll()));

    editMenu = new QMenu("Edit");
    menuBar->addMenu(editMenu);
    editMenu->addAction("Clear",this, SLOT(clearBlocks()));

    schemeMenu = new QMenu("Scheme");
    menuBar->addMenu(schemeMenu);
    ActionRun = schemeMenu->addAction("Run", this, SLOT(Run()),QKeySequence(tr("Shift+R")));
    ActionClear = schemeMenu->addAction("Clear run", this, SLOT(Clear()),QKeySequence(tr("Shift+C")));
    ActionDebug = schemeMenu->addAction("Debug", this, SLOT(StartDebug()),QKeySequence(tr("Shift+D")));
    ActionNextStep = schemeMenu->addAction("Next step", this, SLOT(Debug()),QKeySequence(tr("Shift+Space")));
    ActionExitDebug = schemeMenu->addAction("Exit debug", this, SLOT(ExitDebug()),QKeySequence(tr("Shift+Q")));

    helpMenu = new QMenu("Help");
    menuBar->addMenu(helpMenu);
    helpMenu->addAction("Show help",this,SLOT(ShowHelp()));
    helpMenu->addAction("About",this,SLOT(About()));
    this->layout()->setMenuBar(menuBar);

    ActionNextStep->setEnabled(false);
    ActionExitDebug->setEnabled(false);
}

void Widget::clearBlocks()
{
    unsigned blockVecSize = Widget::BlockList->size();
    for(unsigned i = 0; i < blockVecSize; i++)
    {
        (*Widget::BlockList)[0]->completeDeleteBlock();
    }
    storeWidget->repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter.begin(this);
    for (unsigned i = 0;i<Widget::BlockList->size();i++)
    {
        (*Widget::BlockList)[i]->Draw(&painter);
    }
    for(unsigned i = 0;i<Widget::BlockList->size();i++)
    {
        if((*Widget::BlockList)[i]->getOutPort() != nullptr)
        {
            for(Link *link : (*(*Widget::BlockList)[i]->getOutPort()->GetLinks()))
            {
                link->Draw(&painter);
            }
        }
        for (Port *port: (*(*Widget::BlockList)[i]->getInPorts()))
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
    if(isCycleDetected)
    {
        painter.setPen(Qt::red);
        painter.setFont(QFont("times",14));
        painter.drawText(QRect(this->rect().width()-125,this->rect().height()-25,125,100),"Cycle detected!");
        painter.setPen(Qt::white);
    }
    painter.end();
}

void Widget::Load()
{
    QString fileName = QFileDialog::getOpenFileName(storeWidget,
        tr("Open file"), "", tr("Scheme Files (*.icp)"));
    LoadManager::loadScene(fileName.toStdString());
    storeWidget->repaint();
}

void Widget::Save()
{
    QString fileName = QFileDialog::getSaveFileName(storeWidget,
        tr("Save file"), "", tr("Scheme Files (*.icp)"));
    if(!fileName.contains(".icp"))
        fileName.append(".icp");
    LoadManager::saveScene(fileName.toStdString());
    storeWidget->repaint();
}

void Widget::ShowContextMenu(const QPoint &pos) // this is a slot
{
    QPoint globalPos = this->mapToGlobal(pos);
    myMenu.exec(globalPos);
}
void Widget::Edit()
{
    BlockDialog blockDialog;
    blockDialog.setWindowTitle("Block edit");
    blockDialog.setFixedSize(192,210);
    blockDialog.move(this->x()+ClickPos->X,this->y()+ClickPos->Y);
    blockDialog.setModal(true);
    blockDialog.exec();
}

void Widget::Clear()
{
    for(unsigned i = 0; i< Widget::BlockList->size();i++)
    {
        Block::UnsetCalculated((*Widget::BlockList)[i]);
    }
    storeWidget->repaint();
}

void Widget::ExitAll()
{
    clearBlocks();
    storeWidget->hide();
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

void Widget::ShowHelp()
{
    HelpDialog helpWindow;
    helpWindow.setWindowTitle("Help");
    helpWindow.setFixedSize(400,300);
    helpWindow.move(this->x()+this->rect().center().x()-helpWindow.rect().width()/2,this->y()+this->rect().center().y()-helpWindow.rect().height()/2);
    helpWindow.setModal(true);
    helpWindow.exec();
}

void Widget::About()
{
    AboutDialog aboutWindow;
    aboutWindow.setWindowTitle("About");
    aboutWindow.setFixedSize(260,130);
    aboutWindow.setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
    aboutWindow.move(this->x()+this->rect().center().x()-aboutWindow.rect().width()/2,this->y()+this->rect().center().y()-aboutWindow.rect().height()/2);
    aboutWindow.setModal(true);
    aboutWindow.exec();
}

void Widget::Run()
{
    Clear();
    Widget::stepCounter = INT_MAX-1;
    for(unsigned i = 0; i < Widget::BlockList->size(); i++)
    {
        if((*Widget::BlockList)[i]->getType() == OUT)
        {
            Block::Compute((*Widget::BlockList)[i]);
        }
    }
    storeWidget->repaint();
}

void Widget::Debug()
{
    Block *outBlock = nullptr;
    for(unsigned i = 0; i < Widget::BlockList->size(); i++)
    {
        if((*Widget::BlockList)[i]->getType() == OUT && (*Widget::BlockList)[i]->getCalculated() == false)
        {
            outBlock = (*Widget::BlockList)[i];
            break;
        }
    }
    if(outBlock != nullptr)
    {
        stepCounter++;
        Block::Compute(outBlock);
    }
    else ExitDebug();
    storeWidget->repaint();
}

void Widget::StartDebug()
{
    Clear();
    ActionRun->setEnabled(false);
    ActionDebug->setEnabled(false);
    ActionNextStep->setEnabled(true);
    ActionExitDebug->setEnabled(true);
    isDebug = true;
    storeWidget->repaint();
}

void Widget::ExitDebug()
{
    for(unsigned i = 0; i< Widget::BlockList->size();i++)
    {
        Block::UnsetCalculated((*Widget::BlockList)[i]);
    }
    ActionRun->setEnabled(true);
    ActionDebug->setEnabled(true);
    ActionNextStep->setEnabled(false);
    ActionExitDebug->setEnabled(false);
    Block::delDebugRect();
    isDebug = false;
    storeWidget->repaint();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    EditBlock = nullptr;
    typeOfEdit = NONE;
    this->setCursor(Qt::ArrowCursor);
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
        this->setCursor(Qt::SizeFDiagCursor);
    }
    else if(EditBlock != nullptr && typeOfEdit == MOVE)
    {
       this->setCursor(Qt::SizeAllCursor);
       EditBlock->Move(Point2D::vector(ClickPos,endDrag));
    }
    else if(typeOfEdit == PLANEMOVE)
    {
        this->setCursor(Qt::SizeAllCursor);
        for (unsigned i = 0;i < BlockList->size();i++)
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
        for (unsigned i = 0;i < BlockList->size();i++)
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
                            Block::UnsetCalculated(clickedPort->GetBlock());
                            new Link((*BlockList)[i]->getOutPort(),clickedPort);    //spojení linků
                            wasInPort = false;
                        }
                        if(clickedPort != (*BlockList)[i]->getOutPort())    //pokud kliknu 2x na stejný port nevynuluje se ukazatel(je tam pořád uložen ten stejný
                        {
                            if(clickedPort != nullptr)
                                clickedPort->SetIsClicked(false);
                            clickedPort = nullptr;
                        }
                        goto end;   //vyskočím z vyhledávání
                    }
                    else    //pokud je nakliknutý port
                    {
                        clickedPort = (*BlockList)[i]->getOutPort();        //nastavím nakliknutý port
                        clickedPort->SetIsClicked(true);
                        wasInPort = false;      //a byl to inport
                        goto end;   //vyskočím z vyhledávání
                    }
                }
            }
            for(unsigned j = 0;j<(*BlockList)[i]->getInPorts()->size();j++)       //projdu všechny inpoty
            {
                if((*(*BlockList)[i]->getInPorts())[j]->Rect->contains(new Point2D(event->x(),event->y())))    //spojení inporty
                {
                    if(clickedPort != nullptr)  //pokud je nakliknutý null
                    {
                        if(clickedPort->GetBlock() != (*BlockList)[i] && !wasInPort)    //pokud kliknu na stejný plok a blok nebyl inport
                        {
                            if((*(*BlockList)[i]->getInPorts())[j]->GetLinks()->size() == 0)
                            {
                                Block::UnsetCalculated((*(*BlockList)[i]->getInPorts())[j]->GetBlock());
                                new Link(clickedPort,(*(*BlockList)[i]->getInPorts())[j]); //vytvořím link
                            }
                            if(clickedPort != nullptr)
                                clickedPort->SetIsClicked(false);
                            clickedPort = nullptr;
                            wasInPort = false;
                            goto end;
                        }
                        if(clickedPort != (*(*BlockList)[i]->getInPorts())[j]) //pokud kliknu 2x na stejný port nevynuluje se ukazatel(je tam pořád uložen ten stejný
                        {
                            if(clickedPort != nullptr)
                                clickedPort->SetIsClicked(false);
                            clickedPort = nullptr;
                        }
                        goto end;   //vyskočím z vyhledávání
                    }
                    else
                    {
                        if((*(*BlockList)[i]->getInPorts())[j]->GetLinks()->size()==0)
                        {
                            clickedPort = (*(*BlockList)[i]->getInPorts())[j]; //nastavím nakliknutý port
                            clickedPort->SetIsClicked(true);
                            wasInPort = true;   //a nebyl to inport
                        }
                        else
                        {
                            if(clickedPort != nullptr)
                                clickedPort->SetIsClicked(false);
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
        if(clickedPort != nullptr)
            clickedPort->SetIsClicked(false);
        clickedPort = nullptr;
        typeOfEdit = PLANEMOVE;
    }
    end:
    if(event->button() == Qt::RightButton)
    {
        for (unsigned i = 0;i < BlockList->size();i++)
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





