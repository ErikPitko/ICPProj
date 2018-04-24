#include "widget.h"
#include <QApplication>
#include "block.h"
#include "blockdialog.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    Widget w;
    w.show();
    return App.exec();
}
