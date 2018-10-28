#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QCheckBox>
#include <QProgressBar>
#include <QFile>
#include <QGroupBox>
#include <QLabel>
#include <QScrollArea>
#include <QSizePolicy>
#include <QFont>
#include <QPushButton>
#include <QSignalMapper>
#include <QPainter>
#include <QKeyEvent>


#include "load.h"
#include "fileOn.h"

class Game;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Game* game, QWidget *parent = 0);
    ~Dialog();

private slots:
    void returnToMenu();

    void chooseLevel(int num);

    void reshow();

    void on_btn_return_clicked();


signals:
    void sendsignal();

private:
    static const int num = 10;
    Ui::Dialog *ui;
    QSignalMapper* signalMapper;
    Game* game;
    QStringList levelNameList;
    QPushButton* btn[num];



protected:
    void paintEvent(QPaintEvent *);
};

#endif // DIALOG_H
