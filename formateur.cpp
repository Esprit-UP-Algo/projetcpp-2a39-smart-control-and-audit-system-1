#include<formateur.h>

#include <QString>
formation::formation(){};

formation::formation(QString ID_F, QString TYPE_FORMATION, QString NOM_FORMATION, QString NOM_FORMATEUR  )
{
    this->ID_F=ID_F;
    this->TYPE_FORMATION=TYPE_FORMATION;
    this->NOM_FORMATION=NOM_FORMATION;
    this->NOM_FORMATEUR=NOM_FORMATEUR;
};
bool formation::ajouter()
{


    QSqlQuery query;


    query.prepare("insert into FORMATION (ID_F, TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR) values (:ID_F, :TYPE_FORMATION, :NOM_FORMATION, :NOM_FORMATEUR)");
    query.bindValue(":ID_F", ID_F);
    query.bindValue(":TYPE_FORMATION", TYPE_FORMATION);
    query.bindValue(":NOM_FORMATION", NOM_FORMATION);
    query.bindValue(":NOM_FORMATEUR", NOM_FORMATEUR);

    return query.exec();

};


bool formation::supprimer(QString ID_F)
{

    QSqlQuery query;

    query.prepare("delete from FORMATION where ID_F=:ID_F");
    query.bindValue(":ID_F", ID_F);

    return query.exec();

};

QSqlQueryModel * formation:: afficher()
{

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select ID_F, TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR from FORMATION" );

    return model;
};

bool formation::modifier ()
{

    QSqlQuery query;

    query.prepare("update FORMATION set TYPE_FORMATION=:TYPE_FORMATION, NOM_FORMATION=:NOM_FORMATION, NOM_FORMATEUR=:NOM_FORMATEUR where ID_F=:ID_F");
    query.bindValue(":ID_F", ID_F);
    query.bindValue(":TYPE_FORMATION",TYPE_FORMATION);
    query.bindValue(":NOM_FORMATION", NOM_FORMATION);
    query.bindValue(":NOM_FORMATEUR", NOM_FORMATEUR);

    return query.exec();

};

bool formation::supprimerTout()
{
    QSqlQuery query;

    query.prepare("delete from FORMATION ");

    return query.exec();

}


QSqlQueryModel* formation::tester()
{
   QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT ID_F FROM FORMATION");

   return model;
}
