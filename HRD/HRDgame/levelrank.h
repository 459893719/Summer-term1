#ifndef LEVELRANK_H
#define LEVELRANK_H

#include <QMainWindow>
#include<QFile>
#include<QList>
#include<QString>
#include <QStandardItemModel>
#include "client.h"

namespace Ui {
class LevelRank;
}

class LevelRank : public QMainWindow
{
    Q_OBJECT

public:
    explicit LevelRank(Client* client, int level, QWidget *parent = 0);
    ~LevelRank();
    void showRank();

private slots:
    void on_btn_return_clicked();

signals:
    void sendsignal();

private:
    Ui::LevelRank *ui;
    QStandardItemModel* model;
    Client* client;
    int level;
};

#endif // LEVELRANK_H
