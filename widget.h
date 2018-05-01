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

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include "myrect.h"
#include <vector>
#include <iostream>
#include "block.h"
#include "blockdialog.h"
#include "eeditblock.h"
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QFileDialog>
using namespace std;
namespace Ui {
/**
 * Class of widget.
 */
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public slots:
    /**
     * Static method which deletes all block, ports and links and free the memory.
     */
    static void clearBlocks();
    /**
     * Loads the scene from selected file.
     */
    static void Load();
    /**
     * Saves the scene to selected file.
     */
    static void Save();
    /**
     * Runs calculate all blocks.
     */
    static void Run();
    /**
     * Steps the debug.
     */
    static void Debug();
    /**
     * Starts the debug.
     */
    static void StartDebug();
    /**
     * Exits the debug.
     */
    static void ExitDebug();
    /**
     * Exits all windows and frees the alocated memory.
     */
    static void ExitAll();
public:
	/**
	 * The constructor that construct the main window (widget)
	 * and than sets the parrent. Its default parameter as nullptr.
	 */
    explicit Widget(QWidget *parent = 0);
    /**
     * Destructor that destroy main window.
     */
	~Widget();
    /**
      *
      */
    void InstantiateMenu();
    /**
	 * Paint event is called if any drawable object moves or transform.
	 * Could be callen with method repaint();
	 */
    void paintEvent(QPaintEvent *event);
    /**
     * Static vector of blocks. Its stored in this vector and all are rendered in the same time.
     * It is used to find intersects with mouse cursor.
     */
    static vector<Block*> *BlockList;
    /**
     * The position where the mouse clicked.
     */
    static Point2D *ClickPos;
    /**
     * Block that is moved, edited, resized.
     */
    static Block *EditBlock;
    /**
     * Counter that calculates passage of debug.
     */
    static int stepCounter;
    /**
     * Bool variable that stores if is debug running.
     */
    static bool isDebug;
    /**
     * Event that is called when mouse buttons pressed.
     */
    void mousePressEvent(QMouseEvent*);
    /**
	 * Event that is called when mouse buttons released.
	 */
    void mouseReleaseEvent(QMouseEvent*);
    /**
     * Event that is called when mouse moved.
     */
    void mouseMoveEvent(QMouseEvent*);
    /**
	 * Event that is called when mouse buttons pressed.
	 */
    void mouseDoubleClickEvent(QMouseEvent*);
    /**
     * Shows the context menu if you will press on block with right mouse button
     */
    void ShowContextMenu(const QPoint&);
private slots:
	/**
	 * Shows dialog window where you can edit block.
	 */
    void Edit();
    /**
     * Deletes block.
     */
    void DeleteBlock();
    /**
     * Exits the context menu.
     */
    void Exit();
private:
    /**
     * Draws all objects on plane and redraw them every transform.
     */
    QPainter painter;
    /**
     * Shows all components that are added on panel.
     */
    Ui::Widget *ui;
    /**
     * Indicates if the last clicked port was input port.
     */
    bool wasInPort = false;
    /**
     * Stores last clicked port.
     */
    Port* clickedPort = nullptr;
    /**
     * Stores the link that will be deleted.
     */
    Link *deleteLink = nullptr;
    /**
     * The type of action that will happen.
     */
    EEditBlock typeOfEdit = NONE;
    /**
     * Position at witch drag is over.
     */
    Point2D *endDrag = nullptr;
    /**
     * Stores the context menu.
     */
    QMenu myMenu;
    /**
     * Stores file menu.
     */
    QMenu *fileMenu;
    /**
     * Action that will call on run.
     */
    static QAction *ActionRun;
    /**
     * Action that will call on debug.
     */
    static QAction *ActionDebug;
    /**
     * Action that will call on next step.
     */
    static QAction *ActionNextStep;
    /**
     * Action that will call on exit debug.
     */
    static QAction *ActionExitDebug;
    /**
     * Stores edit menu.
     */
    QMenu *editMenu;
    /**
     * Stores scheme menu.
     */
    QMenu *schemeMenu;
    /**
     * Store widget as static. I need it in static functions.
     */
    static Widget* storeWidget;
};



#endif // WIDGET_H
