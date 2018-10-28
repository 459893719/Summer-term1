#include "levelrank.h"
#include "ui_levelrank.h"

LevelRank::LevelRank(Client* client, int level, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LevelRank)
{
    ui->setupUi(this);

    this->client = client;
    this->level = level;

    setWindowFlags(windowFlags()&~ Qt::WindowMinMaxButtonsHint);

    setWindowFlags(windowFlags()&~ Qt::WindowCloseButtonHint);   //Qt::WindowCloseButtonHint其实是一个值 0x00080000

    model = new QStandardItemModel();

    model->setColumnCount(3);
    model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("名次"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("昵称"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromUtf8("步数"));

    ui->table_rank->resizeColumnsToContents();
    ui->table_rank->setModel(model);
    //表头信息显示居左

    ui->table_rank->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);

    ui->table_rank->verticalHeader()->hide();
    ui->table_rank->horizontalHeader()->hide();

    ui->table_rank->setColumnWidth(0, 70);
    ui->table_rank->setColumnWidth(1, 260);
    ui->table_rank->setColumnWidth(2, 70);

    this->showRank();
}

LevelRank::~LevelRank()
{
    delete ui;
}

//排行榜的用户数据封装成结构体
struct user{
    QString rank;
    QString name;
    QString stepNum;
    user(): rank("0") {} //初始化时将排名初始化为0
    user(QString rank, QString name, QString stepNum): rank(rank), name(name), stepNum(stepNum) {}
};

//显示排行榜
void LevelRank::showRank()
{
    //向服务器发送请求, 获取排行榜数据
    user userList[105] = {user("1", "orion111", "3")};
/*
    client->sendAndRecv("6 level" + QString::number(level));
    QString buffer = client->getRecvData();
    QStringList dataList = buffer.split(" ");

    for(int i=0;i<dataList.size();i++){
        userList[i].rank = dataList[i*3];
        userList[i].name = dataList[i*3 + 1];
        userList[i].stepNum = dataList[i*3 + 2];
    }
*/

    model->setItem(0, 0, new QStandardItem("名次"));
    model->item(0,0)->setTextAlignment(Qt::AlignCenter);
    model->item(0, 0)->setFont(QFont("华文新魏", 12, QFont::Bold));

    model->setItem(0, 1, new QStandardItem("昵称"));
    model->item(0,1)->setTextAlignment(Qt::AlignCenter);
    model->item(0, 1)->setFont(QFont("华文新魏", 12, QFont::Bold));

    model->setItem(0, 2, new QStandardItem("步数"));
    model->item(0,2)->setTextAlignment(Qt::AlignCenter);
    model->item(0, 2)->setFont(QFont("华文新魏", 12, QFont::Bold));

    //显示表格数据
   for(int i=1;i<=100;i++){

       if(userList[i-1].rank == "0"){
           break;
       }
       //逐条显示数据
       model->setItem(i, 0, new QStandardItem(userList[i-1].rank));
       model->item(i,0)->setTextAlignment(Qt::AlignCenter);
       model->item(i, 0)->setFont(QFont("华文新魏", 12, QFont::Bold));

       model->setItem(i, 1, new QStandardItem(userList[i-1].name));
       model->item(i,1)->setTextAlignment(Qt::AlignCenter);
       model->item(i, 1)->setFont(QFont("华文新魏", 12, QFont::Bold));

       model->setItem(i, 2, new QStandardItem(userList[i-1].stepNum));
       model->item(i,2)->setTextAlignment(Qt::AlignCenter);
       model->item(i, 2)->setFont(QFont("华文新魏", 12, QFont::Bold));
   }
}



void LevelRank::on_btn_return_clicked()
{
    emit sendsignal();
    this->close();
}
