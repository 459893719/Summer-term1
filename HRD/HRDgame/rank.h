#ifndef RANK_H
#define RANK_H

#include <QMainWindow>
#include<QFile>
#include<QList>
#include<QString>
#include <QStandardItemModel>
#include "client.h"


namespace Ui {
class rank;
}

class rank : public QMainWindow
{
    Q_OBJECT

public:
    explicit rank(Client* client, QWidget *parent = 0);
    ~rank();
    void showRank();

private slots:
    void on_btn_return_clicked();

signals:
    void sendsignal();

private:
    Ui::rank *ui;
    QStandardItemModel* model;
    Client* client;

};

#endif // RANK_H
