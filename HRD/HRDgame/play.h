#ifndef PLAY_H
#define PLAY_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include "solution.h"

class Game;

namespace Ui {
class play;
}

class play : public QMainWindow
{
    Q_OBJECT

public:
    explicit play(Game* game, QStringList levelnamelist, QWidget *parent = 0);
    ~play();
    void setgame(Game* game){
        this->game = game;
    }
   // void setlevelName(QString name){
     //   levelName = name;
    //}

private:
    Ui::play *ui;
    QLabel *picLabel;
    Game* game;
    QStringList levelNameList;

signals:
    void sendsignal1();


protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent* e);



private slots:
    void winReset();
    void showSolution();
    void returnToDialog();
    void on_pushButton_clicked();
    void reshow();
    //void on_btn_autoplay_clicked();
};

#endif // PLAY_H
