#include "widget.h"
#include <QApplication>
#include "block.h"
#include "blockdialog.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    Widget w;
    w.resize(800,600);
    w.show();
    return App.exec();

//    Block* in1 = new Block(IN, new MyRect(0, 0, 0, 0), 2);
//        Block* in2 = new Block(IN, new MyRect(0, 0, 0, 0), 3);

//        Block* bl1 = new Block(ADD, new MyRect(0, 0, 0, 0));
//        bl1->genInPort();
//        bl1->genInPort();

//        Block* disp = new Block(OUT, new MyRect(0, 0, 0, 0));
//        disp->genInPort();

//        new Link(in1->getOutPort(), bl1->getInPorts()[0]);
//        new Link(in2->getOutPort(), bl1->getInPorts()[1]);
//        new Link(bl1->getOutPort(), disp->getInPorts()[0]);

//        Block::compute(disp);
//        cout << disp->getValue() << endl;


//        delete in1;

//        Block::compute(disp);
//        cout << disp->getValue() << endl;

//        cout << "disp: " << *disp << endl;

//        Block* qq = new Block(IN, new MyRect(0,0,0,0));
//        qq->setValue(5);
//        cout << "QQ: " << *qq << endl;
//        cin >> *qq;
//        cout << "QQ: " << *qq << endl << qq->getValue() << endl;


//        return EXIT_SUCCESS;
}
