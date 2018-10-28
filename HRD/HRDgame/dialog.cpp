#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QStringList>
#include <QString>

#include "game.h"
#include "play.h"


Dialog::Dialog(Game* game, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~ Qt::WindowMinMaxButtonsHint);

    setWindowFlags(windowFlags()&~ Qt::WindowCloseButtonHint);   //Qt::WindowCloseButtonHint其实是一个值 0x00080000


    this->game = game;

    signalMapper = new QSignalMapper();


    connect(ui->btn_return, SIGNAL(clicked(bool)), this, SLOT(returnToMenu()));

    //QScrollArea* scroll = new QScrollArea();
    ui->scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->scroll->setWidgetResizable(true);
    ui->scroll->setStyleSheet("background-color:transparent;");


    //QVBoxLayout* totlayout = new QVBoxLayout();
    //totlayout->addWidget(title);
    //totlayout->addWidget(btn_return);
    //totlayout->addWidget(scroll);

    //this->setLayout(totlayout);


    levelNameList = load::loadLevelName();

    QGroupBox* gb[num];
    QVBoxLayout* layout[num];
    QLabel* label1[num], *label2[num];
    QHBoxLayout* layout1[num];
    for(int i=0;i<num;i++){
        gb[i] = new QGroupBox();
        layout[i] = new QVBoxLayout();

        label1[i] = new QLabel("第" + QString::number(i+1) + "关");
        label1[i]->setStyleSheet("color: rgb(200, 0, 0);");
        label1[i]->setFont(QFont("Microsoft YaHei", 10, 60));

        label2[i] = new QLabel(levelNameList[i]);
        label2[i]->setFont(QFont("隶书", 30, 50));
        label2[i]->setStyleSheet("color: #c85b01;");

        layout1[i] = new QHBoxLayout();
        layout1[i]->addWidget(label1[i]);
        layout1[i]->addWidget(label2[i]);

        layout[i]->addLayout(layout1[i]);

        //border-image: url(:/image/btn.jpg);
//color: rgb(255, 85, 0);
//font: 18pt "华文新魏";

        //qDebug() << this->game->getuser()->getlevelNum();
        if(i > this->game->getuser()->getlevelNum()){
            btn[i] = new QPushButton("无法挑战");
            btn[i]->setStyleSheet("border-image: url(:/image/btn.jpg);font: 20pt \"隶书\";color:#6b6b6b;");
            btn[i]->setEnabled(false);
        }
        else{
            btn[i] = new QPushButton("挑战");
            btn[i]->setStyleSheet("border-image: url(:/image/btn.jpg);font: 20pt \"隶书\";color: rgb(255, 85, 0);");
        }

        connect(btn[i], SIGNAL(clicked()), signalMapper, SLOT(map()) );
        signalMapper->setMapping(btn[i], i+1);

        layout[i]->addWidget(btn[i]);
        gb[i]->setLayout(layout[i]);

        gb[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    }

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(chooseLevel(int)));

    QVBoxLayout* vlayout = new QVBoxLayout();


    for(int i=0;i<num;i++){
        vlayout->addWidget(gb[i]);
    }

    QWidget* widget = new QWidget();
    widget->setLayout(vlayout);
    ui->scroll->setWidget(widget);
    //this->resize(500, 750);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::returnToMenu()
{
    emit sendsignal();
    this->close();
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix1;
    pix1.load("./pic/背景.png");//图片的位置
    painter.drawPixmap(0,0,500,750,pix1);
}

void Dialog::chooseLevel(int num){

    qDebug() << num;

    game->setPresLevel(num);

    this->hide();
    play* w = new play(game,levelNameList, this);
    connect(w, SIGNAL(sendsignal1()), this, SLOT(reshow()));
    //qDebug() << levelNameList[num-1];
    w->show();

    //qDebug() << num;
}

void Dialog::reshow(){
qDebug() << this->game->getuser()->getlevelNum();
    for(int i=0;i<num;i++){
        if(i > this->game->getuser()->getlevelNum()){
            btn[i]->setText("无法挑战");
            btn[i]->setStyleSheet("border-image: url(:/image/btn.jpg);font: 20pt \"隶书\";color:#6b6b6b;");
            btn[i]->setEnabled(false);
        }
        else{
            btn[i]->setText("挑战");
            btn[i]->setStyleSheet("border-image: url(:/image/btn.jpg);font: 20pt \"隶书\";color: rgb(255, 85, 0);");
        }
    }
    this->show();
}


void Dialog::on_btn_return_clicked()
{

    emit sendsignal();
    this->close();
}

