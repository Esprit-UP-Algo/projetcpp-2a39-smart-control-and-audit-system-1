#ifndef CONECTION_H
#define CONECTION_H


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Connection
{
public:
    QSqlDatabase db;
    Connection();
    bool createconnect();
    void closeConnect();
};


#endif // CONECTION_H
