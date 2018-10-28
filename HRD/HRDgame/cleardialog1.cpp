#include "cleardialog1.h"
#include "ui_cleardialog1.h"

clearDialog1::clearDialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clearDialog1)
{
    ui->setupUi(this);
}

clearDialog1::~clearDialog1()
{
    delete ui;
}

void clearDialog1::on_btn_ok_clicked()
{
    this->close();
}
