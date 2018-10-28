#include "menu.h"
#include "ui_menu.h"
#include"dialog.h"
#include"help.h"
#include"rank.h"
#include "game.h"

Menu::Menu(Client* client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{

    game = new Game();
    game->setClient(client);


    load fileLoad;
    fileLoad.loadName();
    fileLoad.loadLevelNum();

    //从文件中读入用户的id和用户名
    game->getuser()->setId(fileLoad.getId());
    game->getuser()->setName(fileLoad.getName());
    game->getuser()->setLevelNum(fileLoad.getLevelNum());
    //qDebug() << fileLoad.getLevelNum();

    ui->setupUi(this);

    setWindowFlags(windowFlags()&~ Qt::WindowMinMaxButtonsHint);

    setWindowFlags(windowFlags()&~ Qt::WindowCloseButtonHint);   //Qt::WindowCloseButtonHint其实是一个值 0x00080000

}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_btn_rank_clicked()
{
    this->hide();
    rank* r = new rank(game->getClient());
    connect(r, SIGNAL(sendsignal()), this, SLOT(reshow()));
    //r.show();
    //r.exec();
    r->show();
}

void Menu::on_btn_help_clicked()
{
    this->hide();

    Help* h = new Help();
    connect(h, SIGNAL(sendsignal()), this, SLOT(reshow()));
    //h.show();
    //h.exec();
    h->show();
}

void Menu::on_btn_enter_clicked()
{
    this->hide();


    Dialog* p = new Dialog(game);
    connect(p, SIGNAL(sendsignal()), this, SLOT(reshow()));
    //p.show();
    //p.exec();
    p->show();
}

void Menu::reshow(){
    this->show();
}

void Menu::on_btn_exit_clicked()
{
    this->close();
}



void Menu::on_btn_sound_toggled(bool checked)
{

    if(!checked){
        ui->btn_sound->setStyleSheet("border-image: url(:/image/soundon.jpg);border-radius:20px;");

    }
    else{
        ui->btn_sound->setStyleSheet("border-image: url(:/image/soundoff.jpg);border-radius:20px;");
    }
    this->game->getBgm()->clickBgm();
}
