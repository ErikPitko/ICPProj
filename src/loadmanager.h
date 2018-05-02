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

/**
 * Collection of static functions used for saving and loading scene.
 */
class LoadManager
{
    LoadManager() {}
public:
    /**
	 * Saves scene in a file.
     *
     * @param path the absolute path with file name.
     *
	 * @return true if it ends successfully.
	 */
    static bool saveScene(string path);
    /**
	 * Loads scene from the file.
	 *
     * @param path the absolute path with file name.
     *
	 * @return true if it ends successfully.
	 */
    static void loadScene(string path);
};

#endif // LOADMANAGER_H
