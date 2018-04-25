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

//    Block* in1 = new Block(IN, new MyRect(0, 0, 0, 0), 2);
//    Block* in2 = new Block(IN, new MyRect(0, 0, 0, 0), 3);

//    Block* bl1 = new Block(ADD, new MyRect(0, 0, 0, 0));
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

//    Block::compute(Widget::BlockList->back());

//    LoadManager::loadScene();
//    LoadManager::saveScene();

//    Block::compute(Widget::BlockList->back());

//    cout << "block1: " << *in1 << endl;
//    cout << "block2: " << *bl1 << endl;
//    cout << "block1 outPort: " << *in1->getOutPort() << endl;
//    cout << "block2 inPort: " << *(bl1->getInPorts()[0]) << endl;
//    cout << "link: " << *in1->getOutPort()->GetFirstLink() << endl;

//    return EXIT_SUCCESS;
}
