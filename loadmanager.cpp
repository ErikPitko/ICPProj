#include "loadmanager.h"

using namespace std;
bool LoadManager::saveScene()
{
//    Widget::BlockList
    for (Block* block: *Widget::BlockList)
    {
        cout << "block" << endl;
        cout << block << ':' << *block << endl;
    }

    cout << "link" << endl;

    for (Block* block: *Widget::BlockList)
    {
        if (block->getOutPort() == nullptr)
            continue;
        for (Link* link : *block->getOutPort()->GetLinks())
        {
            cout << "\t" << *link << endl;
        }
    }

    return true;
}

void LoadManager::loadScene()
{
    std::map<size_t, Block*> blockPair;
    for (Block* block : *Widget::BlockList)
    {
        delete block;
    }
    Widget::BlockList->clear();
    string op;
    char trash;

    cout << "blocks:" << endl;
    while(true)
    {
        cin >> op;
        if (op.compare("block"))
            break;

        size_t oldPtr;
        Block* tempB = new Block(IN, new MyRect(0,0,0,0));
        cin >> hex >> oldPtr >> trash;
        cin >> *tempB;

        blockPair[oldPtr] = tempB;
        Widget::BlockList->push_back(tempB);
        cout << hex << oldPtr;
        cout << " new_value: " << blockPair.find(oldPtr)->second;
        cout << " : " << *tempB << endl;
    }

    size_t blockin;
    size_t blockout;
    int idxInPort;
    cout << "links:" << endl;

    while(cin >> hex >> blockin >> trash >> dec >> idxInPort >> trash >> hex >> blockout)
    {
        new Link(blockPair.find(blockin)->second->getOutPort(),
                 blockPair.find(blockout)->second->getInPorts()[idxInPort]);
        cout << hex << blockin << " : " << blockout;
        cout << " <- " << idxInPort << endl;
    }
}
