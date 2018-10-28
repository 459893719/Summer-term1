#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

class Game;
class User;
class Chess;
class Level;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Game* game, QWidget *parent = 0);
    ~MainWindow();
    void setgame1(Game* game){
        game1 = game;
    }
private:
    Ui::MainWindow *ui;
    QLabel *picLabel;
    Game* game1;
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent* e);


};

#endif // MAINWINDOW_H
