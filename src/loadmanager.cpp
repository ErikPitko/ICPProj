#include "loadmanager.h"

using namespace std;
bool LoadManager::saveScene(string path)
{
    ofstream fOut (path);
    if (!fOut.is_open())
        return false;
    for (Block* block: *Widget::BlockList)
    {
        fOut << "block" << endl;
        fOut << block << ':' << *block << endl;
    }

    fOut << "link" << endl;

    for (Block* block: *Widget::BlockList)
    {
        if (block->getOutPort() == nullptr)
            continue;
        for (Link* link : *block->getOutPort()->GetLinks())
        {
            fOut << *link << endl;
        }
    }

    return true;
}

void LoadManager::loadScene(string path)
{
    ifstream fIn (path);
    if (!fIn.is_open())
        return;
    std::map<size_t, Block*> blockPair;
    Widget::clearBlocks();
    string op;
    char trash;

    cout << "blocks:" << endl;
    while(true)
    {
        fIn >> op;
        if (op.compare("block"))
            break;

        size_t oldPtr;
        Block* tempB = new Block(IN, new MyRect(0,0,0,0));
        fIn >> hex >> oldPtr >> trash;
        fIn >> *tempB;

        blockPair[oldPtr] = tempB;
        Widget::BlockList->push_back(tempB);
        ios_base::fmtflags f( cout.flags() );
        cout << "\t" << hex << oldPtr;
        cout << " new_value: " << blockPair.find(oldPtr)->second;
        cout << " : " << *tempB << dec << endl;
        cout.flags(f);
    }

    size_t blockin;
    size_t blockout;
    int idxInPort;
    cout << "links:" << endl;

    while(fIn >> hex >> blockin >> trash >> dec >> idxInPort >> trash >> hex >> blockout)
    {
        if (!blockPair.find(blockin)->second || !blockPair.find(blockout)->second){
            return;
        }
        new Link(blockPair.find(blockin)->second->getOutPort(),
                 (*blockPair.find(blockout)->second->getInPorts())[idxInPort]);
        cout << "\t" << blockPair.find(blockin)->second << " <--> " << blockPair.find(blockout)->second;
        cout << " <- " << idxInPort << endl;
    }
}
