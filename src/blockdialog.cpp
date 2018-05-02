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
    QDir dir;
    ui->setupUi(this);
    ui->lineEdit->hide();
    ui->label_2->hide();
    ui->ADD->setIcon(QIcon(QString(dir.absolutePath()+"/Resources/ADD.png")));
    ui->ADD->setIconSize(QSize(64,64));

    ui->SUB->setIcon(QIcon(QString(dir.absolutePath()+"/Resources/SUB.png")));
    ui->SUB->setIconSize(QSize(64,64));

    ui->MUL->setIcon(QIcon(QString(dir.absolutePath()+"/Resources/MUL.png")));
    ui->MUL->setIconSize(QSize(64,64));

    ui->DIV->setIcon(QIcon(QString(dir.absolutePath()+"/Resources/DIV.png")));
    ui->DIV->setIconSize(QSize(64,64));

    ui->IN->setIcon(QIcon(QString(dir.absolutePath()+"/Resources/IN.png")));
    ui->IN->setIconSize(QSize(64,64));

    ui->OUT->setIcon(QIcon(QString(dir.absolutePath()+"/Resources/OUT.png")));
    ui->OUT->setIconSize(QSize(64,64));
    selected = ADD;
    ui->numOfPorts->setText(QString(std::to_string(ui->horizontalSlider->value()).c_str()));
}

BlockDialog::~BlockDialog()
{
    delete ui;
}

void BlockDialog::on_ADD_clicked()
{
    selected = ADD;
    ui->lineEdit->hide();
    ui->label_2->hide();
    ui->horizontalSlider->show();
    ui->label->show();
    ui->numOfPorts->show();
}

void BlockDialog::on_SUB_clicked()
{
    selected = SUB;
    ui->lineEdit->hide();
    ui->label_2->hide();
    ui->horizontalSlider->show();
    ui->label->show();
    ui->numOfPorts->show();
}

void BlockDialog::on_MUL_clicked()
{
    selected = MUL;
    ui->lineEdit->hide();
    ui->label_2->hide();
    ui->horizontalSlider->show();
    ui->label->show();
    ui->numOfPorts->show();
}

void BlockDialog::on_DIV_clicked()
{
    selected = DIV;
    ui->lineEdit->hide();
    ui->label_2->hide();
    ui->horizontalSlider->show();
    ui->label->show();
    ui->numOfPorts->show();
}

void BlockDialog::on_IN_clicked()
{
    selected = IN;
    ui->horizontalSlider->hide();
    ui->label->hide();
    ui->numOfPorts->hide();
    ui->lineEdit->show();
    ui->label_2->show();
}

void BlockDialog::on_OUT_clicked()
{
    selected = OUT;
    ui->lineEdit->hide();
    ui->label_2->hide();
    ui->horizontalSlider->show();
    ui->label->show();
    ui->numOfPorts->show();
}

void BlockDialog::on_Apply_clicked()
{
    QString value=ui->lineEdit->text();
    Block *bl;
    if(Widget::EditBlock != nullptr)
    {
       bl = new Block(selected,new MyRect(Widget::EditBlock->getRect()->x(),Widget::EditBlock->getRect()->y(),100,100));
    }
    else bl = new Block(selected,new MyRect( *Widget::ClickPos,100,100));
    if(selected != IN)
    {
        for (int i = 0;i <portCount;i++ )
        {
            bl->genInPort();
        }
    }
    else
        bl->setValue(value.toDouble());
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
    std::cout<<position<<std::endl;
    ui->numOfPorts->setText(QString(std::to_string(position).c_str()));
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
