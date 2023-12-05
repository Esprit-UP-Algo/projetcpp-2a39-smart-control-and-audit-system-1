#include "formateur.h"


QSqlQueryModel * formation::rechercheridentifiant(QString ID_F)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select ID_F, TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR from FORMATION where ID_F like '"+ID_F+"' ");
    q.exec();
    model->setQuery(q);
    return (model);

}
QSqlQueryModel * formation::recherchernom(QString TYPE_FORMATION)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select ID_F, NOM_FORMATION, NOM_FORMATEUR from FORMATION where TYPE_FORMATION like '"+TYPE_FORMATION+"' ");
    q.exec();
    model->setQuery(q);
    return (model);

}

QSqlQueryModel * formation::recherchernomf(QString NOM_FORMATION)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare(" select ID_F, TYPE_FORMATION, NOM_FORMATEUR from FORMATION where NOM_FORMATION like '"+NOM_FORMATION+"' ");
    q.exec();
    model->setQuery(q);
    return (model);

}
QSqlQueryModel * formation::recherchernomff(QString NOM_FORMATEUR)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare(" select ID_F, TYPE_FORMATION, NOM_FORMATION from FORMATION where NOM_FORMATEUR like '"+NOM_FORMATEUR+"' ");
    q.exec();
    model->setQuery(q);
    return (model);

}
/*QSqlQueryModel * formation::rechercherage(QString age)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select identifiant, nom, prenom, age from EMPLOYEHSAN where age like '"+age+"' ");
    q.exec();
    model->setQuery(q);
    return (model);

}
*/

