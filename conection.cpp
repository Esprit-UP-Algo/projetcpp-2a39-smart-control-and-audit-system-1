#include "conection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("kjh");
db.setUserName("yoyo");//inserer nom de l'utilisateur
db.setPassword("eya100123");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;

    return  test;
}
void Connection::closeConnect(){db.close();}
