#include "widget.h"
#include "ui_widget.h"
#include "block.h"
#include "blockdialog.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}
vector<Block*>* Widget::BlockList = new vector<Block*>();
Point2D *Widget::ClickPos = nullptr;
Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    painter.begin(this);
    for (int i = 0;i<Widget::BlockList->size();i++)
    {
        cout<<Widget::BlockList->size()<<endl;
        (*Widget::BlockList)[i]->Draw(&painter);
    }
    painter.end();
}
/*void Widget::createRect(MyRect rect,QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::black);
    painter->drawRect(rect);
}

void Widget::createLine(Point2D startPos,Point2D endPos,QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 3));
    QLine line = QLine(startPos.X,startPos.Y,endPos.X,endPos.Y);
    painter->drawLine(line);
}

void Widget::createImage(MyRect rect,QPainter *painter)
{
    QImage image = QImage("/home/adam/Stažené/ADD.png");
    painter->drawImage(rect,image);
}*/
void Widget::mousePressEvent(QMouseEvent *event)
{
    ClickPos = new Point2D(event->x(),event->y());
    if(event->button() == Qt::RightButton)
    {
        BlockDialog block;
        block.setModal(true);
        block.exec();
    }
    repaint();
}





