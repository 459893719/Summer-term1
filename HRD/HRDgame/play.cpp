#include "play.h"
#include "ui_play.h"
#include "game.h"
#include <QGraphicsAnchor>
#include "cleardialog.h"
#include "cleardialog1.h"
#include "levelrank.h"


play::play(Game* game, QStringList levelnamelist, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::play)
{
    this->game = game;
    this->levelNameList = levelnamelist;

    int preslevel = this->game->getpresLevel();
    this->game->getlevel()->loadChessboard(preslevel);
    this->game->getlevel()->searchChessboard(this);


    ui->setupUi(this);

    setWindowFlags(windowFlags()&~ Qt::WindowMinMaxButtonsHint);

    setWindowFlags(windowFlags()&~ Qt::WindowCloseButtonHint);   //Qt::WindowCloseButtonHint其实是一个值 0x00080000



    connect(ui->btn_back, SIGNAL(clicked(bool)), this, SLOT(returnToDialog()));
    connect(ui->btn_autoplay, SIGNAL(clicked(bool)), this, SLOT(showSolution()));
    connect(ui->btn_reset, SIGNAL(clicked(bool)), this, SLOT(winReset()));



    ui->lab_levelName->setText(levelNameList[preslevel - 1]);
    resize(500, 750);


    ui->num_present->display(this->game->getstepNum());

    load fileLoad;
    this->game->getuser()->loadPbest(preslevel, fileLoad);
    ui->num_yourbest->display(this->game->getuser()->getpBestStepNum_());

    fileLoad.loadBSN(preslevel);
    ui->num_best->display(fileLoad.getBSN());



}

play::~play()
{
    delete ui;
}

void play::mousePressEvent(QMouseEvent *e)
{
    //int x=e->x();
    //int y=e->y();
    if (e->x()>50&&e->x()<450&&e->y()>150&&e->y()<650)
    {
        if(e->buttons()==Qt::LeftButton)
        {
            game->setQ((e->x()-50)/100,(e->y()-150)/100);
            game->setnowChess(game->getlevel()->getChessboard(game->getQx(),game->getQy()));
            update();
        }
        else if(e->buttons()==Qt::RightButton)
        {
            game->setnowChess(0);
            update();
        }
       // qDebug()<<x<<","<<y;
    }
}


//将图片画在label
void play::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix1;
    pix1.load("./pic/背景.png");//图片的位置
    painter.drawPixmap(0,0,500,750,pix1);
    game->getlevel()->paintQ(this);
    game->getlevel()->paintF(this,game->getnowChess());
}

void play::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_R)
    {
        game->reChessboard(this);
    }
    else
    {
        if(1==game->getlevel()->move(game->getnowChess(),event->key())){
            game->moveStep();
            ui->num_present->display(this->game->getstepNum());
        }
    }

    switch(game->levelClear(this)){
    case 1:{
        clearDialog clearDia(this);
        clearDia.exec();
        game->nextLevel(this);
        //过关之后, 修改总过关数
        ui->lab_levelName->setText(levelNameList[game->getpresLevel() - 1]);
        ui->num_present->display(0);
        ui->num_best->display(game->getlevel()->getBSN());
        ui->num_yourbest->display(game->getuser()->getpBestStepNum_());

        break;
    }
    case 2:{
        clearDialog1 clearDia1(this);
        clearDia1.exec();


        break;
    }
    }
}

void play::keyReleaseEvent(QKeyEvent *event)
{
        update();
}



void play::winReset()
{

    game->reChessboard(this);
    update();
    ui->num_present->display(0);
    //qDebug() << "ok";
}

void play::showSolution()
{
    qDebug() << "ok2";
    this->hide();
    Solution* solu = new Solution(game->getpresLevel(), game->getlevel(), levelNameList[game->getpresLevel() - 1], this);
    connect(solu, SIGNAL(sendsignal2()), this, SLOT(reshow()));
    solu->show();
}

void play::returnToDialog()
{

    //返回菜单时, 当前步数清零
    game->setStepNum(0);

    emit sendsignal1();
    this->close();
}



void play::on_pushButton_clicked()
{
    this->hide();
    LevelRank* r = new LevelRank(game->getClient(), game->getpresLevel(), this);
    connect(r, SIGNAL(sendsignal()), this, SLOT(reshow()));
    r->show();

}

void play::reshow(){
    this->show();
}
/*
void play::on_btn_autoplay_clicked()
{
    this->hide();
    Solution* solu = new Solution(game->getpresLevel(), game->getlevel(), this);
    connect(solu, SIGNAL(sendsignal2()), this, SLOT(reshow()));
    solu->show();
}*/
