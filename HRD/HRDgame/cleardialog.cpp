#include "cleardialog.h"
#include "ui_cleardialog.h"

clearDialog::clearDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clearDialog)
{
    ui->setupUi(this);

    //setWindowFlags(windowFlags()&~ Qt::WindowMinMaxButtonsHint);

    //setWindowFlags(windowFlags()&~ Qt::WindowCloseButtonHint);   //Qt::WindowCloseButtonHint其实是一个值 0x00080000

}

clearDialog::~clearDialog()
{
    delete ui;
}

void clearDialog::on_btn_next_clicked()
{
    emit nextLevelSignal();
    this->close();
}

void clearDialog::on_btn_cancel_clicked()
{
    this->close();
}
