
#define FORMATEUR_H
#define FORMATEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>



using namespace std;

class formation
{

    QString ID_F ,TYPE_FORMATION , NOM_FORMATION,NOM_FORMATEUR;

public:
    //Constructuers
    formation();
    formation(QString, QString, QString, QString );

    //Getter
    QString getID_F() {return ID_F;}
    QString getTYPE_FORMATION() {return TYPE_FORMATION;}
    QString getNOM_FORMATION() {return NOM_FORMATION;}
    QString getNOM_FORMATEUR() {return NOM_FORMATEUR;}





    //Setter
    void setID_F (QString ID_F) {this->ID_F=ID_F;}
    void setTYPE_FORMATION (QString TYPE_FORMATION) {this->TYPE_FORMATION=TYPE_FORMATION;}
    void setNOM_FORMATION (QString NOM_FORMATION){this->NOM_FORMATION=NOM_FORMATION;}
    void setNOM_FORMATEUR(QString NOM_FORMATEUR){this->NOM_FORMATEUR=NOM_FORMATEUR;}

    //CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier();
bool supprimerTout();

    QSqlQueryModel*  tester();

    QSqlQueryModel * rechercheridentifiant(QString ID_F) ;
        QSqlQueryModel * recherchernom(QString TYPE_FORMATION) ;
        QSqlQueryModel * recherchernomf(QString NOM_FORMATION) ;
        QSqlQueryModel * recherchernomff(QString NOM_FORMATEUR) ;
///////////////////////////

        QSqlQueryModel * tricroissant_ID_F() ;
            QSqlQueryModel * tricroissant_nom() ;
            QSqlQueryModel * tricroissant_prenom() ;
            QSqlQueryModel * tricroissant_age() ;

            QSqlQueryModel * tridecroissant_identifiant() ;
            QSqlQueryModel * tridecroissant_nom() ;
            QSqlQueryModel * tridecroissant_prenom() ;
            QSqlQueryModel * tridecroissant_age() ;



};
 // FORMATEUR_H
