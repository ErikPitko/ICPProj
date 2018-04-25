#ifndef LOADMANAGER_H
#define LOADMANAGER_H

#include "block.h"
#include "widget.h"
#include <iostream>
#include <fstream>
#include <map>

class LoadManager
{
    LoadManager() {}
public:
    static bool saveScene();
    static void loadScene();
};

#endif // LOADMANAGER_H
