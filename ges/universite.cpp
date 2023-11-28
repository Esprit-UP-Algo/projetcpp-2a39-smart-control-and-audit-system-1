#include "universite.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QSqlError>


universite::universite()
{id=0; nom=" "; adresse=" "; nb_etudiants=0; date_visite=date_visite.currentDate();; budget_annuel=0.0f;}


universite::universite(int id, QString nom, QString adresse, int nb_etudiants, QDate date_visite, float budget_annuel)
{this->id=id; this->nom=nom; this->adresse=adresse; this->nb_etudiants=nb_etudiants; this->date_visite=date_visite;
this->budget_annuel=budget_annuel;}


int universite::getid() {return id;}
QString universite::getnom(){return nom;}
QString universite::getadresse() {return adresse;}
int universite::getnb_etudiants() {return nb_etudiants;}
QDate universite::getdate_visite() {return date_visite;}
float universite::getbudget_annuel() {return budget_annuel;}
void universite::setid(int id){this->id=id;}
void universite::setnom(QString nom){this->nom=nom;}
void universite::setadresse(QString adresse){this->adresse=adresse;}
void universite::setnb_etudiants(int nb_etudiants){this->nb_etudiants=nb_etudiants;}
void universite::setdate_visite(QDate date_visite){this->date_visite=date_visite;}
void universite::setbudget_annuel(float budget_annuel){this->budget_annuel=budget_annuel;}


bool universite::ajouter_universite()
{
    QString id_string = QString::number(id);
       QString nb_etudiants_string = QString::number(nb_etudiants);
       QString budget_annuel_string = QString::number(budget_annuel);
    QSqlQuery query;
   query.prepare("INSERT INTO UNIVERSITE (id, nom, adresse, nb_etudiants, date_visite, budget_annuel) "
                             "VALUES (:id, :nom, :adresse, :nb_etudiants, :date_visite, :budget_annuel)");
               query.bindValue(0, id_string);
               query.bindValue(1, nom);
               query.bindValue(2, adresse);
               query.bindValue(3, nb_etudiants_string);
               query.bindValue(4, date_visite);
               query.bindValue(5, budget_annuel_string);

            return query.exec();
    }



bool universite::supprimer_universite(int id)
{QSqlQuery query;
QString id_string = QString::number(id);
query.prepare("Delete FROM universite where id=:id");
query.bindValue(0, id);
return query.exec();}







QSqlQueryModel* universite::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT* FROM universite");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom de l'université"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse de l'université "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre d'étudiants"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de visite"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Budget annuel"));
return model;}

QSqlQueryModel* universite::afficher_id()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, nom FROM universite");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom de l'université"));
    return model;
}



QSqlQueryModel* universite::afficherH()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM historique");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom de l'université"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse de l'université "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre d'étudiants"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de visite"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Budget annuel"));

    return model;
}



bool universite::modifier_universite(int id, QString nom, QString adresse, int nb_etudiants, QDate date_visite, float budget_annuel)
{
QString id_string = QString::number(id);
QString etudiants_string = QString::number(nb_etudiants);
QString budget_string=QString::number(budget_annuel);
QSqlQuery query;
query.prepare("UPDATE universite SET id=:id, nom=:nom, adresse=:adresse, nb_etudiants=:nb_etudiants, date_visite=:date_visite, budget_annuel=:budget_annuel WHERE id=:id");
query.bindValue(":id",id_string);
query.bindValue(":nom",nom);
query.bindValue(":adresse",adresse);
query.bindValue(":nb_etudiants",etudiants_string);
query.bindValue(":date_visite",date_visite);
query.bindValue(":budget_annuel",budget_string);
return query.exec();}

QSqlQueryModel *universite::tri_id()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from  universite ORDER BY id");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom de l'université"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse de l'université "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre d'étudiants"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de visite"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Budget annuel"));
return model;
}

QSqlQueryModel *universite::tri_adresse()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from  universite ORDER BY adresse");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom de l'université"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse de l'université "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre d'étudiants"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de visite"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Budget annuel"));
return model;
}

QSqlQueryModel *universite::tri_date_visite()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM universite ORDER BY date_visite DESC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom de l'université"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse de l'université"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre d'étudiants"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de visite"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Budget annuel"));

    return model;
}

QSqlQueryModel *universite::rechercher(QString nom)
{
QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("SELECT * FROM UNIVERSITE WHERE  nom LIKE '%"+nom+"%'" );

model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom de l'université"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse de l'université"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre d'étudiants"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de visite"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Budget annuel"));

return model;
}

