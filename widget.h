#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include "myrect.h"
#include <vector>
#include <iostream>
#include "block.h"
#include "blockdialog.h"
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
    /*void createRect(MyRect rect,QPainter *painter);
    void createLine(Point2D startPos,Point2D endPos,QPainter *painter);
    void createImage(MyRect rect,QPainter *painter);*/
    void mousePressEvent(QMouseEvent *event);
private:
    QPainter painter;
    Ui::Widget *ui;
    QRect *rect;
};

#endif // WIDGET_H
