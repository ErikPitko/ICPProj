#ifndef BLOCKDIALOG_H
#define BLOCKDIALOG_H

#include <QDialog>
#include "block.h"
namespace Ui {
class BlockDialog;
}

class BlockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlockDialog(QWidget *parent = 0);
    ~BlockDialog();

private slots:
    void on_ADD_clicked();

    void on_SUB_clicked();

    void on_MUL_clicked();

    void on_DIV_clicked();

    void on_IN_clicked();

    void on_OUT_clicked();

    void on_Apply_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_Cancel_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    EBlock selected;
    double value;
    int portCount = 2;
    Ui::BlockDialog *ui;
};

#endif // BLOCKDIALOG_H
