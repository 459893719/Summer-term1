#include "server.h"
#include "ui_server.h"
#include <QDebug>

//能够获取表中总共有几行, 用来返回用户的id
int queryRowCount(QSqlQuery query)
{
    int initialPos = query.at();
    int pos = 0;
    if (query.last()){
        pos = query.at() + 1;
    }else{
        pos = 0;
    }
    query.seek(initialPos);
    return pos;
}


//ConnectDB()   连接SQlite数据库
void Server::ConnectDB(){
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("GameDB.db");
    if (!database.open())
    {
        ui->te_recv->append("Error: Failed to connect database." + database.lastError().text());
    }
    else
    {
        ui->te_recv->append("Succeed to connect database.") ;
    }

    //创建表格  创建一次就可以了
/*
    QSqlQuery sql_query;

    //创建游戏所需的表
    //totalTable 存所有用户的总过关数   level1 ~ level10  每关中每一个用户的最优过关数

    sql_query.exec("create table totalTable(id integer primary key AUTOINCREMENT, name text, totalLevels int)");
    QString str;
    for(int i=1;i<=10;i++){

        sql_query.exec("create table level" + str.number(i) +  "(id int primary key, name text, minSteps int)");
    }
*/


}

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    //初始化Server对象
    tcpServer = new QTcpServer(this);


    //自动获取本机的IP
    ui->le_ip->setText(QNetworkInterface().allAddresses().at(6).toString());

    ui->btn_connect->setEnabled(true);

    //当有客户端连接到服务器时, 执行槽函数
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));

    ConnectDB();

}

Server::~Server()
{
    delete ui;
}


//NewConnectionSlot()  将新的客户端添加到列表中, 将它数据存取的信号与槽函数绑定, 同时能够处理断线的情况
void Server::NewConnectionSlot()
{
    //将新的客户端添加到列表中
    currentClient = tcpServer->nextPendingConnection();
    tcpClient.append(currentClient);

    //客户端准备存取数据时, 数据存取的信号与槽函数绑定
    connect(currentClient, SIGNAL(readyRead()), this, SLOT(ReadAndSendData()));
    //处理断线的情况
    connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}

//ReadAndSendData()  读取客户端数据并将结果发送给指定客户端
void Server::ReadAndSendData()
{
    //读取数据
    // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
    for(int i=0; i<tcpClient.length(); i++)
    {
        QByteArray buffer = tcpClient[i]->readAll();
        if(buffer == ""){continue;}
        QString request = buffer;
        QStringList list = request.split(' ');

        static QString IP_Port;
        IP_Port = tr("[%1:%2]:").arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                                     .arg(tcpClient[i]->peerPort());

        ui->te_recv->append("\n" + IP_Port+" "+buffer);


        QSqlQuery query;
        if(buffer.isEmpty())    continue;
        else{
            //根据用户不同的请求来处理和发送数据到客户端
            int req = list[0].toInt();
            switch(req){ //处理请求
            case 1:{//1号请求: 在totalTable中创建一个新纪录, 客户端提供用户名


                QString name = list[1];
                //插入用户名为name的纪录, 总过关数为0
                if(!query.exec("insert into totalTable values(null, \""+name+"\", 0)" )){
                    //操作失败, 打印原因
                     ui->te_recv->append("Error: Fail to insert into table." + query.lastError().text());
                }
                else{
                    ui->te_recv->append("Successfully insert " + name + " into table!");

                    //操作成功, 返回用户的新id到客户端
                    query.exec("select * from totalTable");
                    int id = queryRowCount(query);
                    ui->te_recv->append("return id " + QString::number(id) + " to " + IP_Port);
                    QString idStr = QString::number(id);
                    tcpClient[i]->write(idStr.toUtf8());
                }
                break;
            }

            case 2:{//2号请求: 在totalTable中修改纪录中的总过关数, 客户端提供id与总过关数

                //由于客户端的2号请求和3号请求同时发送, 所以处理完应该立即处理3号请求
                QString id = list[1];
                QString num = list[2];

                if(!query.exec("update totalTable set totalLevels = " + num + " where id = " + id)){
                    ui->te_recv->append("Error: Fail to update record." + query.lastError().text());
                }
                else{
                    ui->te_recv->append("Successfully update data in table!");

                }

            }

            case 3:{//3号请求: 在某个level表中创建新纪录, 客户端提供表名, id, 用户名, 该关的最佳步数


                QString table = list[4];
                QString id = list[5];
                QString name = list[6];
                QString num = list[7];



                if(!query.exec("insert into " + table + " values(" + id + ", \"" + name + "\", " + num + ")")){
                    ui->te_recv->append("Error: Fail to insert into table." + query.lastError().text());
                }
                else{
                    ui->te_recv->append("Successfully insert record into table!");


                }
                break;
            }
            case 4:{//4号请求: 在某个level表中更新一个记录, 客户端提供表名, id, 该关的最佳步数


                QString table = list[1];
                QString id = list[2];
                QString num = list[3];

                if(!query.exec("update " + table + " set minSteps = " + num + " where id = " + id)){
                    ui->te_recv->append("Error: Fail to update record." + query.lastError().text());
                }
                else{
                    ui->te_recv->append("Successfully update record in table!");


                }
                break;
            }
            case 5:{//5号请求: 获得totalTable中排序好的前100个记录(以总过关数降序排序)


                QString buffer;//使用buffer存要发送的数据

                //返回数据的类型为QString
                if(!query.exec("select * from totalTable order by totalLevels desc, name asc, id asc limit 100")){
                    ui->te_recv->append("Error: Fail to select records." + query.lastError().text());
                }
                else{
                    ui->te_recv->append("Successfully select records in table!");

                    //发送排行榜数据到客户端
                    while(query.next())
                    {
                        QString id = query.value(0).toString();
                        QString name = query.value(1).toString();
                        QString tot = query.value(2).toString();
                        buffer.append(id + " " + name + " " + tot + " ");
                    }

                    //qDebug() << buffer;

                }
                break;
            }
            case 6:{//6号请求: 获得某个level表中排序好的20个记录(以最佳步数升序排序)


                QString buffer;
                QString table = list[1];

                if(!query.exec("select * from " + table + " order by minSteps asc, name asc, id asc limit 20")){
                    ui->te_recv->append("Error: Fail to select records." + query.lastError().text());
                }
                else{
                    ui->te_recv->append("Successfully select records in table!");
                    while(query.next())
                    {
                        QString id = query.value(0).toString();
                        QString name = query.value(1).toString();
                        QString tot = query.value(2).toString();
                        buffer.append(id + " " + name + " " + tot + " ");
                    }

                    //qDebug() << buffer;
                    tcpClient[i]->write(buffer.toUtf8());

                }
                break;
            }
            }
        }

    }




}


//disconnectedSlot()  处理断线时的情况
void Server::disconnectedSlot()
{

    ui->te_recv->append("connection failed");
    //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            // 删除存储在tcpClient列表中的客户端信息
             tcpClient[i]->destroyed();
             tcpClient.removeAt(i);
        }
    }
}


//进行连接, 服务器开始监听模式
void Server::on_btn_connect_clicked()
{
    if(ui->btn_connect->text()=="连接"){ //开启监听模式
        bool ok = tcpServer->listen(QHostAddress::Any, ui->le_port->text().toInt());
        if(ok)
        {
            ui->btn_connect->setText("断开");

        }
    }
    else  //关闭监听模式
    {
        for(int i=0; i<tcpClient.length(); i++)//断开所有连接
        {
            tcpClient[i]->disconnectFromHost();
            tcpClient[i]->waitForDisconnected(1000);
            tcpClient.removeAt(i);  //从保存的客户端列表中取去除
        }
        tcpServer->close();     //不再监听端口
        ui->btn_connect->setText("连接");
    }
}
