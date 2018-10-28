#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include<QFile>
#include<QTextStream>
#include<QIODevice>

#include "client.h"
namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(Client* client, QWidget *parent = 0);
    ~Register();
    void clearUserInterface();
    void writeToFile(QString cnt);

private slots:
    void on_btn_right_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::Register *ui;
    Client* client;
};

#endif // REGISTER_H
