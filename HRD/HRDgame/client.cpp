#include "client.h"
#include "ui_client.h"
#include <QDebug>
#include <QMessageBox>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    //ui->setupUi(this);
    //建立套接字, 并与服务器建立连接
    mSocket = new QTcpSocket();

    //connect(mSocket, SIGNAL(readyRead()), this, SLOT(()));

    //connect(mSocket, SIGNAL(connected()), this, SLOT(sonnect_suc()));
    //connect(mSocket, SIGNAL(disconnected()), this, SLOT(client_dis()));
    mSocket->connectToHost("10.128.255.171", 8000); //服务器IP地址
}

Client::~Client()
{
    delete ui;
    delete this->mSocket;
}

void Client::sendAndRecv(QString request){
    mSocket->write(request.toUtf8());
    recvData = mSocket->readAll();

    qDebug() << request;
    qDebug() << recvData;
}

void Client::client_dis(){
    QMessageBox::critical(NULL, "错误", "与服务器连接失败, 请重试.", "确定");
}
