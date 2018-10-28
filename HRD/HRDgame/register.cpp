#include "register.h"
#include "ui_register.h"
#include<QString>
#include<QDebug>
#include<QMessageBox>

#include "fileOn.h"

Register::Register(Client* client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    this->client = client;

    on_btn_cancel_clicked();
}

Register::~Register()
{
    delete ui;
}

void Register::on_btn_right_clicked()//按下确定键后
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


    /*switch(ret)
    {
        case QMessageBox::Save:
            break;
        case QMessageBox::Cancel:
            break;
         default:
            break;
    }*/

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

/*
void register::clearUserIntreface()
{
    this->ui->line_name->clear();
}
void register::writeToFile(QString cnt){
    QFile file("user.txt");
    if(!file.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！",'确定');
        return;
    }
    QTextStream out(&file);
    out<<cnt;
    file.close();
}//liuzihao
*/

void Register::on_btn_cancel_clicked()
{
    this->close();
}
