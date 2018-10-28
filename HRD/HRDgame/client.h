#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);

    void sendAndRecv(QString request);
    void client_dis();
    QString getRecvData(){
        return recvData;
    }

    ~Client();

private:
    Ui::Client *ui;
    QTcpSocket* mSocket;
    QString recvData;
};

#endif // CLIENT_H
