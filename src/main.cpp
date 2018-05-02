#include "widget.h"
#include <QApplication>
#include "block.h"
#include "blockdialog.h"
#include <iostream>
#include "loadmanager.h"
int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    Widget w;
    w.resize(800,600);
    w.show();
    return App.exec();

//    Block* in1 = new Block(IN, new MyRect(0, 0, 0, 0), 20);
//    Block* in2 = new Block(IN, new MyRect(0, 0, 0, 0), 5);

//    Block* bl1 = new Block(MUL, new MyRect(0, 0, 0, 0));
//    bl1->genInPort();
//    bl1->genInPort();
//    bl1->genInPort();

//    Block* disp = new Block(OUT, new MyRect(0, 0, 0, 0));
//    disp->genInPort();

//    new Link(in1->getOutPort(), bl1->getInPorts()[0]);
//    new Link(in1->getOutPort(), bl1->getInPorts()[1]);
//    new Link(in2->getOutPort(), bl1->getInPorts()[2]);
//    new Link(bl1->getOutPort(), disp->getInPorts()[0]);

//    Widget::BlockList->push_back(in1);
//    Widget::BlockList->push_back(in2);
//    Widget::BlockList->push_back(bl1);
//    Widget::BlockList->push_back(disp);

//    in2->completeDeleteBlock();

//    Block::compute(Widget::BlockList->back());
//    cout << "disp: " << Widget::BlockList->back()->getValue() << endl;

//    LoadManager::loadScene();
//    LoadManager::saveScene();


//    Block::compute(Widget::BlockList->back());
//    cout << "disp: " << Widget::BlockList->back()->getValue() << endl;

//    Widget::clearBlocks();
//    return EXIT_SUCCESS;
}
