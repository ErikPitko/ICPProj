#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include "myrect.h"
#include <vector>
#include <iostream>
#include "block.h"
#include "blockdialog.h"
#include "eeditblock.h"
#include <QMenu>
using namespace std;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    static vector<Block*> *BlockList;
    static Point2D *ClickPos;
    static Block *EditBlock;
    static int stepCounter;
    static bool isDebug;
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    void ShowContextMenu(const QPoint&);
private slots:
    void Edit();
    void DeleteBlock();
    void Exit();
private:
    QPainter painter;
    Ui::Widget *ui;
    QRect *rect;
    bool wasInPort = false;
    Port* clickedPort = nullptr;
    Link *deleteLink = nullptr;
    EEditBlock typeOfEdit = NONE;

    Point2D *endDrag = nullptr;
    QMenu myMenu;
};



#endif // WIDGET_H
