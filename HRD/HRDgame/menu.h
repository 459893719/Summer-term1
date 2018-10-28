#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include"rank.h"
#include"help.h"
#include"play.h"
#include "bgm.h"
class Game;

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(Client* client, QWidget *parent = 0);
    ~Menu();


public slots:
    void on_btn_rank_clicked();
    
    void on_btn_help_clicked();
    
    void on_btn_enter_clicked();

    void reshow();
    
private slots:
    void on_btn_exit_clicked();


    void on_btn_sound_toggled(bool checked);

private:
    Ui::Menu *ui;
    Game* game;

};

#endif // MENU_H
