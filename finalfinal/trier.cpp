#include "formateur.h"



QSqlQueryModel * formation::tricroissant_ID_F()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select ID_F,TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR from FORMATION ORDER BY ID_F ASC");

    return model;

}


QSqlQueryModel * formation::tricroissant_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select ID_F,TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR from FORMATION ORDER BY TYPE_FORMATION ASC");

    return model;
}

QSqlQueryModel * formation::tricroissant_prenom()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select ID_F,TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR from FORMATION ORDER BY ID_F NOM_FORMATION");


    return model;
}

QSqlQueryModel * formation::tricroissant_age()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select ID_F,TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR from FORMATION ORDER BY NOM_FORMATEUR ASC");

    return model;
}




QSqlQueryModel * formation::tridecroissant_identifiant()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select ID_F,TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR from FORMATION ORDER BY ID_F DESC");

    return model;

}


QSqlQueryModel * formation::tridecroissant_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select ID_F,TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR from FORMATION  ORDER BY TYPE_FORMATION DESC");


    return model;
}

QSqlQueryModel * formation::tridecroissant_prenom()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select ID_F,TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR from FORMATION ORDER BY NOM_FORMATION DESC");


    return model;
}

QSqlQueryModel * formation::tridecroissant_age()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select ID_F,TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR from FORMATION ORDER BY NOM_FORMATEUR DESC");


    return model;
}
