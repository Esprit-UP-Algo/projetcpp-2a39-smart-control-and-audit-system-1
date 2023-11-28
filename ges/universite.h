#ifndef UNIVERSITE_H
#define UNIVERSITE_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlError>



class universite
{private:
int id,nb_etudiants;
float budget_annuel;
QString nom, adresse;
QDate date_visite;

public:
universite();
universite(int,QString,QString,int,QDate,float);
int getid();
QString getnom();
QString getadresse();
int getnb_etudiants();
QDate getdate_visite();
float getbudget_annuel();
void setid(int);
void setnom(QString);
void setadresse(QString);
void setnb_etudiants(int);
void setdate_visite(QDate);
void setbudget_annuel(float);
bool ajouter_universite();
QSqlQueryModel* afficher();
QSqlQueryModel* afficher_id();
QSqlQueryModel* afficherH();
bool supprimer_universite(int);
bool modifier_universite(int,QString,QString,int,QDate,float);
QSqlQueryModel* rechercher(QString);
QSqlQueryModel * tri_id() ;
QSqlQueryModel * tri_adresse() ;
QSqlQueryModel * tri_date_visite() ;





};



#endif // UNIVERSITE_H
