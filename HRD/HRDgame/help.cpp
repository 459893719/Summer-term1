#include "help.h"
#include "ui_help.h"


Help::Help(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~ Qt::WindowMinMaxButtonsHint);

    setWindowFlags(windowFlags()&~ Qt::WindowCloseButtonHint);   //Qt::WindowCloseButtonHint其实是一个值 0x00080000

}

Help::~Help()
{
    delete ui;
}


void Help::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix1;
    pix1.load("./pic/help.jpg");//图片的位置
    painter.drawPixmap(0,0,500,750,pix1);
}


void Help::on_btn_return_clicked()
{
    emit sendsignal();
    this->close();
}
