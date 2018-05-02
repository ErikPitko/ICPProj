#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
