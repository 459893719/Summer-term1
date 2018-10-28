#include "login.h"
#include "ui_login.h"

#include "fileOn.h"

Login::Login(Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~ Qt::WindowMinMaxButtonsHint);

    setWindowFlags(windowFlags()&~ Qt::WindowCloseButtonHint);   //Qt::WindowCloseButtonHint其实是一个值 0x00080000

    this->client = client;
}

Login::~Login()
{
    delete ui;
}

void Login::on_btn_right_clicked()//按下确定键后
{
    //QString id=this->ui->line_id->text();
    QString name=this->ui->line_name->text();
    //QMessageBox msgBox;

    /*msgBox.setText("用户"+name+"("+id+")");
    msgBox.setInformativeText("是否登陆？");

    //msgBox.setStandardButtons(QMessageBox::确定|QMessageBox::取消);
    //msgBox.setDefaultButton(QMessageBox::确定);

    msgBox.addButton("确定",QMessageBox::AcceptRole);
    QPushButton*cbtn=msgBox.addButton("取消",QMessageBox::RejectRole);
    msgBox.setDefaultButton(cbtn);

    int ret=msgBox.exec();//弹出对话框*/

    //QMessageBox::aboutQt(this,"鸣谢");
    //QString cnt=name;
    if(name.length()<1){
        QMessageBox::critical(this,"错误","信息填写不完整，请重新填写","确定");
    }
    else{


        //客户端向服务器发请求
        client->sendAndRecv("1 " + name);

        int id = client->getRecvData().toInt();

        fileOn::writeName(id, name);

        this->close();
    }

}
