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

#ifndef BLOCKDIALOG_H
#define BLOCKDIALOG_H

#include <QDialog>
#include "block.h"
namespace Ui {
/**
 * Class of block dialog
 */
class BlockDialog;
}

class BlockDialog : public QDialog
{
    Q_OBJECT

public:
	/**
	 * The explicit constructor to create new instance.
	 *
	 * @param parent parameter where it will be draw.
	 *
	 */
    explicit BlockDialog(QWidget *parent = 0);
    /**
     * Destructor that clears window and destroy all objects on it.
     *
     */
    ~BlockDialog();

private slots:
	/**
	 * Event calls by click on add button. It sets selected operation.
	 */
    void on_ADD_clicked();
    /**
	 * Event calls by click on SUB button. It sets selected operation.
	 */
    void on_SUB_clicked();
    /**
	 * Event calls by click on MUL button. It sets selected operation.
	 */
    void on_MUL_clicked();
    /**
	 * Event calls by click on DIV button. It sets selected operation.
	 */
    void on_DIV_clicked();
    /**
	 * Event calls by click on IN button. It sets selected operation.
	 */
    void on_IN_clicked();
    /**
	 * Event calls by click on OUT button. It sets selected operation.
	 */
    void on_OUT_clicked();
    /**
	 * Event calls by click on Apply button. Creates new block by selected type and closes the popup window.
	 */
    void on_Apply_clicked();
    /**
     * Event calls by moving slider on window.
     * Slider sets number of input ports on block.
     * Default value of slider is 2 and its hidden while IN block is selected, because IN block doesnt have any input ports.
     *
     * @param value returns value that slider have.
     */
    void on_horizontalSlider_sliderMoved(int value);
    /**
     * Event calls by click on Cancel button. It closes the window it its not needed.
     */
    void on_Cancel_clicked();
    /**
     * Event calls by writing text into textbox. The text should be only number.
     * The textbox is showed if the IN block is selected.
     *
     * @param arg1 returns value that IN block have to have.
     */
    void on_lineEdit_textChanged(const QString &arg1);

private:
    /**
     * Type of new block that buttons sets.
     */
    EBlock selected;
    /**
     * Value that IN block have on his out port.
     */
    double value;
    /**
     * Default value of ports it sets the slider.
     */
    int portCount = 2;
    /**
     * Ui variable that shows me available components on panel.
     */
    Ui::BlockDialog *ui;
};

#endif // BLOCKDIALOG_H
