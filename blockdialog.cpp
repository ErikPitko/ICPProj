#include "blockdialog.h"
#include "ui_blockdialog.h"
#include "widget.h"
#include "block.h"
#include <iostream>
using namespace std;
BlockDialog::BlockDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlockDialog)
{
    ui->setupUi(this);
}

BlockDialog::~BlockDialog()
{
    delete ui;
}

void BlockDialog::on_ADD_clicked()
{
    selected = ADD;

}

void BlockDialog::on_SUB_clicked()
{
    selected = SUB;
}

void BlockDialog::on_MUL_clicked()
{
    selected = MUL;
}

void BlockDialog::on_DIV_clicked()
{
    selected = DIV;
}

void BlockDialog::on_IN_clicked()
{
    selected = IN;
}

void BlockDialog::on_OUT_clicked()
{
    selected = OUT;
}

void BlockDialog::on_Apply_clicked()
{
    Block *bl = new Block(selected,new MyRect( *Widget::ClickPos,100,100));
    if(selected != IN)
    {
        for (int i = 0;i <portCount;i++ )
        {
            bl->genInPort();
        }
    }else
        bl->setValue(value);
    if(Widget::EditBlock != nullptr)
    {
        if(Widget::EditBlock->getOutPort()!= nullptr)
        {
            for (int i = 0; i < Widget::EditBlock->getOutPort()->GetLinks()->size();i++)
            {
                new Link(bl->getOutPort(),(*Widget::EditBlock->getOutPort()->GetLinks())[i]->getOutPort());
            }
            for (int i = 0; i < Widget::EditBlock->getInPorts().size();i++)
            {
                if(i == bl->getInPorts().size())
                    break;
                for(int j=0;j < Widget::EditBlock->getInPorts()[i]->GetLinks()->size();j++)
                {
                    new Link((*Widget::EditBlock->getInPorts()[i]->GetLinks())[j]->getInPort(),bl->getInPorts()[i]);
                }

            }
            if(Widget::EditBlock != nullptr)
                Widget::EditBlock->completeDeleteBlock();
        }
    }
    Widget::BlockList->push_back(bl);
    if(this != nullptr)
        close();
}

void BlockDialog::on_horizontalSlider_sliderMoved(int position)
{
    portCount = position;
}

void BlockDialog::on_Cancel_clicked()
{
    if(this != nullptr)
        close();
}

void BlockDialog::on_lineEdit_textChanged(const QString &arg1)
{
    value = arg1.toDouble();
}
