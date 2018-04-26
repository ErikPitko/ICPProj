/*******************************************************************************
 *
 * VUT FIT Brno - ICP project BlockDiagram
 *
 * Copyright (C) 2018, Adam Petras (xpetra19)
 * Copyright (C) 2018, Erik Pitko (xpitko00)
 *
 * Contributors:
 * 		Adam Petras - GUI, base application implementation, Doxygen doc
 * 		Erik Pitko - base application implementation, save/load scene
 *
 ******************************************************************************/

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
