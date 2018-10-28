#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include <QGraphicsAnchor>
MainWindow::MainWindow(Game* game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    game1 = game;
    ui->setupUi(this);
    resize(500, 750);
    int preslevel = game1->getpresLevel();
    game1->getlevel()->loadChessboard(preslevel);
    game1->getlevel()->searchChessboard(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    int x=e->x();
    int y=e->y();
    if (e->x()>50&&e->x()<450&&e->y()>150&&e->y()<650)
    {
        if(e->buttons()==Qt::LeftButton)
        {
            game1->setQ((e->x()-50)/100,(e->y()-150)/100);
            game1->setnowChess(game1->getlevel()->getChessboard(game1->getQx(),game1->getQy()));
        }
        else if(e->buttons()==Qt::RightButton)
        {
            game1->setnowChess(0);
        }
        qDebug()<<x<<","<<y;
    }
}


//将图片画在label
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix1;
    pix1.load("./pic/北京.png");//图片的位置
    painter.drawPixmap(0,-10,500,750,pix1);
    game1->getlevel()->paintQ(this);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_R)
    {
        game1->reChessboard(this);
    }
    else
    {
        game1->getlevel()->move(game1->getnowChess(),event->key());
    }
    game1->levelClear(this);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
        update();
}
