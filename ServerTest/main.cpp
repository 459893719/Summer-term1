#include "server.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Server w;
    w.show();

    return a.exec();
}
