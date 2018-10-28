#include "warn.h"
#include "ui_warn.h"
#include "menu.h"

Warn::Warn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Warn)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~ Qt::WindowMinMaxButtonsHint);

    setWindowFlags(windowFlags()&~ Qt::WindowCloseButtonHint);   //Qt::WindowCloseButtonHint其实是一个值 0x00080000


}

Warn::~Warn()
{
    delete ui;
}



void Warn::mousePressEvent (QMouseEvent* event) {
    // 判断是否是左键按下
    if (event->button () == Qt::LeftButton) {
        this->close();
    }
}
