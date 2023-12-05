#include "employe.h"
#include <QSqlQuery>
#include <iostream>
#include <QDate>
using namespace std;


employe::employe()
{

    this->id=0;
        this->Prenom="";
    this->salaire=0;
    this ->Prenom="";
        this ->Nom="";
           this ->mail="";
        this ->Poste="";
           this ->Adresse="";
         this ->mdp="";
    this ->tel=0;

}
employe::employe(int id, QString Nom, QString Prenom,QDate date,int salaire , QString poste,QString mail,int tel,QString adresse,QString mdp)
{
this->id=id;
    this->Prenom=Prenom;
this->salaire=salaire;
this ->Prenom=Prenom;
   this ->date=date;
    this ->Nom=Nom;
    this ->tel=tel;

       this ->mail=mail;
    this ->Poste=poste;
       this ->Adresse=adresse;
     this ->mdp=mdp;
}
bool employe::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(id);
    QString res1=QString::number(tel);
    QString res2=QString::number(salaire);


    query.prepare("insert into employe (id,Nom,Prenom,datee,salaire,poste,mail,tel,adresse,mdp)""values(:id,:Nom,:Prenom,:datee,:salaire,:poste,:mail,:tel,:adresse,:mdp)");
    query.bindValue(":id", res);
            query.bindValue(":Prenom", Prenom);
    query.bindValue(":salaire", res2);
    query.bindValue(":Nom", Nom);
    query.bindValue(":mail", mail);
       query.bindValue(":datee", date);
       query.bindValue(":poste", Poste);
               query.bindValue(":tel", res1);
       query.bindValue(":adresse", Adresse);
       query.bindValue(":mdp", mdp);


return query.exec();
}


bool employe::supprimer(QString id)
{
QSqlQuery query;

query.prepare("Delete from employe where ID=:id");
query.bindValue(":id",id);
return query.exec();
}
bool employe::modifier()
{

    QSqlQuery query;
    QString res=QString::number(id);
    QString res1=QString::number(tel);
    QString res2=QString::number(salaire);
          query.prepare("UPDATE employe "" SET id=:id,Prenom=:Prenom,  Nom=:Nom, Poste=:Poste , datee=:datee, salaire=:salaire, mail=:mail, adresse=:adresse, tel=:tel,mdp=:mdp  where ID='"+res+"' ");

          query.bindValue(":id", res);
                  query.bindValue(":Prenom", Prenom);
          query.bindValue(":salaire", res2);
          query.bindValue(":Nom", Nom);
          query.bindValue(":mail", mail);
             query.bindValue(":datee", date);
             query.bindValue(":Poste", Poste);
                     query.bindValue(":tel", res1);
             query.bindValue(":adresse", Adresse);
             query.bindValue(":mdp", mdp);

        return    query.exec();
}

QSqlQueryModel * employe::afficher()
{

    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();

    qry->prepare("select * from employe");
    qry->exec();
    modal->setQuery(*qry);
    modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    modal->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    modal->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    modal->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
    modal->setHeaderData(4,Qt::Horizontal,QObject::tr("salaire"));
    modal->setHeaderData(5,Qt::Horizontal,QObject::tr("poste"));
    modal->setHeaderData(6,Qt::Horizontal,QObject::tr("mail"));
    modal->setHeaderData(7,Qt::Horizontal,QObject::tr("tel"));
    modal->setHeaderData(8,Qt::Horizontal,QObject::tr("adresse"));
    modal->setHeaderData(9,Qt::Horizontal,QObject::tr("mdp"));
return modal;


}




