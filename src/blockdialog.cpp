#include "blockdialog.h"
#include "ui_blockdialog.h"
#include "widget.h"
#include "block.h"
#include <iostream>
#include "resources.h"
using namespace std;
BlockDialog::BlockDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlockDialog)
{
    ui->setupUi(this);
    ui->lineEdit->hide();
    ui->label_2->hide();

    QImage img(256, 256, QImage::Format_RGB32);
//    ADD
    img.loadFromData((const uchar*)&ADD_png, ADD_png_len, "PNG");
    ui->ADD->setIcon(QIcon(QPixmap::fromImage(img)));
    ui->ADD->setIconSize(QSize(64,64));

//    SUB
    img.loadFromData((const uchar*)&SUB_png, SUB_png_len, "PNG");
    ui->SUB->setIcon(QIcon(QPixmap::fromImage(img)));
    ui->SUB->setIconSize(QSize(64,64));

//    MUL
    img.loadFromData((const uchar*)&MUL_png, MUL_png_len, "PNG");
    ui->MUL->setIcon(QIcon(QPixmap::fromImage(img)));
    ui->MUL->setIconSize(QSize(64,64));

//    DIV
    img.loadFromData((const uchar*)&DIV_png, DIV_png_len, "PNG");
    ui->DIV->setIcon(QIcon(QPixmap::fromImage(img)));
    ui->DIV->setIconSize(QSize(64,64));

//    IN
    img.loadFromData((const uchar*)&IN_png, IN_png_len, "PNG");
    ui->IN->setIcon(QIcon(QPixmap::fromImage(img)));
    ui->IN->setIconSize(QSize(64,64));

//    OUT
    img.loadFromData((const uchar*)&OUT_png, OUT_png_len, "PNG");
    ui->OUT->setIcon(QIcon(QPixmap::fromImage(img)));
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
    ui->horizontalSlider->hide();
    ui->label->hide();
    ui->numOfPorts->hide();
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
        if(selected != OUT)
        {
            for (int i = 0;i <portCount;i++ )
            {
                bl->genInPort();
            }
        }
        else bl->genInPort();
    }
    else
        bl->setValue(value.toDouble());
    if(Widget::EditBlock != nullptr)
    {
        if(Widget::EditBlock->getOutPort()!= nullptr)
        {
            std::vector<Port*> outPort = std::vector<Port*>();

            if(Widget::EditBlock->getOutPort()->GetLinks() != nullptr)
                for (unsigned i = 0; i < Widget::EditBlock->getOutPort()->GetLinks()->size();i++)
                {
                    outPort.push_back((*Widget::EditBlock->getOutPort()->GetLinks())[i]->getOutPort());
                }
            for (unsigned i = 0; i < Widget::EditBlock->getInPorts()->size();i++)
            {
                if(i == bl->getInPorts()->size())
                    break;
                for(unsigned j=0;j < (*Widget::EditBlock->getInPorts())[i]->GetLinks()->size();j++)
                {
                    new Link((*(*Widget::EditBlock->getInPorts())[i]->GetLinks())[j]->getInPort(),(*bl->getInPorts())[i]);
                }
            }
            for(Port *p : outPort)
            {
                if (bl->getOutPort() != nullptr)
                    new Link(bl->getOutPort(),p);
            }
        }
        Block::UnsetCalculated(bl);
        Widget::EditBlock->completeDeleteBlock();
    }
    Widget::BlockList->push_back(bl);
    Widget::EditBlock = nullptr;
    close();

}

void BlockDialog::on_horizontalSlider_sliderMoved(int position)
{
    //std::cout<<position<<std::endl;
    ui->numOfPorts->setText(QString(std::to_string(position).c_str()));
    portCount = position;
}

void BlockDialog::on_Cancel_clicked()
{
    close();
}

void BlockDialog::on_lineEdit_textChanged(const QString &arg1)
{
    value = arg1.toDouble();
}
