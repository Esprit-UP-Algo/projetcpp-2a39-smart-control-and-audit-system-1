#include "certeficat.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QDate>

Certificat::Certificat(QString titulaire,int numero,int referentiel,QDate date_validite_debut,QDate date_validite_fin,QString validite,QString signiataire,QString domaine)
{
    this->titulaire=titulaire;
    this->numero=numero;
    this->referentiel=referentiel;
    this->date_validite_debut=date_validite_debut;
    this->date_validite_fin=date_validite_fin;
    this->validite=validite;
    this->signiataire=signiataire;
    this->domaine=domaine;

}


bool Certificat::ajouter()
{
    QSqlQuery query;
    QString nv_numero = QString::number(numero);
    QString nv_referentiel = QString::number(referentiel);
    // Convert QDate to a string with the desired format
    if(numero>0)
{
    query.prepare("INSERT INTO CERTIFICAT(NUMERO, REFERENTIEL, TITULAIRE, DOMAINE, VALIDITE, DATE_VALIDITE_DEBUT, DATE_VALIDITE_FIN, SIGNIATAIRE) "
                  "VALUES (:numero, :referentiel, :titulaire, :domaine, :validite, :date_validite_debut, :date_validite_fin, :signiataire)");
    query.bindValue(":numero", nv_numero);
    query.bindValue(":referentiel", nv_referentiel);
    query.bindValue(":titulaire", titulaire);
    query.bindValue(":domaine", domaine);
    query.bindValue(":validite", validite);
    query.bindValue(":date_validite_debut", date_validite_debut);
    query.bindValue(":date_validite_fin", date_validite_fin);
    query.bindValue(":signiataire", signiataire);
}
    return query.exec(); // exec() sends the query to execute
}


QSqlQueryModel *Certificat::afficher()
{

  QSqlQueryModel *model=new QSqlQueryModel();
  model->setQuery("select * from CERTIFICAT");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMERO"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("REFERENTIEL"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("TITULAIRE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DOMAINE"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("VALIDITE"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_VALIDITE_DEBUT"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_VALIDITE_FIN"));
       model->setHeaderData(6,Qt::Horizontal,QObject::tr("SIGNIATAIRE"));


 return model;
}

bool Certificat::supprimer(int numero)
{

    QSqlQuery query;
    QString nv_numero =QString::number(numero);
    query.prepare("Delete from CERTIFICAT where NUMERO= :numero ");

          query.bindValue(":numero", nv_numero);
            return  query.exec();

}
#include <QDateTime>

bool Certificat::ajouteretatcoffre(  int numero)
{
    QString nv_numero = QString::number(numero);
    QSqlQuery query;

        // Get the current date and time
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString datetimeOuverture = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

        query.prepare("UPDATE CERTIFICAT SET COFFRE = :datetimeOuverture WHERE NUMERO = :numero");
        query.bindValue(":numero", nv_numero);
        query.bindValue(":datetimeOuverture", "opened " + datetimeOuverture);

        if (!query.exec()) {
            qDebug() << "Error updating CERTIFICAT:" << query.lastError().text();
            return false;
        }

        return true;
    }
bool Certificat::ajouteretatcoffreclosed(  int numero)
{
    QString nv_numero = QString::number(numero);
    QSqlQuery query;

   // if (data == "0")
    //{
        // Get the current date and time
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString datetimeOuverture = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

        query.prepare("UPDATE CERTIFICAT SET COFFRE = :datetimeOuverture WHERE NUMERO = :numero");
        query.bindValue(":numero", nv_numero);
        query.bindValue(":datetimeOuverture", "OPEN " + datetimeOuverture);

        if (!query.exec()) {
            qDebug() << "Error updating CERTIFICAT:" << query.lastError().text();
            return false;
        }

        return true;
    }

    // Handle other cases or provide an error message if needed
    //return false;
//}


QSqlQueryModel *Certificat::affichercoffre()
{

    QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT NUMERO, COFFRE FROM CERTIFICAT");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUMERO"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("COFFRE"));

        return model;
}
bool Certificat::verifierExistence(int value)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CERTIFICAT WHERE NUMERO = :value");
    query.bindValue(":value", value);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError().text();
        return false;
    }

    if (query.next()) {
        qDebug() << "La valeur existe dans la base de données.";
        return true;
    } else {
        return false;
    }
}






