#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "block.h"
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    Block *bl1 = new Block(IN,new MyRect(0,0,0,0),10);
    Block *bl2 = new Block(ADD,new MyRect(0,0,0,0));
    bl2->genInPort();
    Link *l1 = new Link(bl1->getOutPort(),bl2->getInPorts()[0]);
    cout<<bl2->getValue() <<endl;
    Block *bl3 = new Block(ADD,new MyRect(0,0,0,0));
    return app.exec();
}

