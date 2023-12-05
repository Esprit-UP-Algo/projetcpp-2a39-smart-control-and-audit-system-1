#ifndef CERTEFICAT_H
#define CERTEFICAT_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDate>
class Certificat
{
    private:

QString titulaire;
int numero;
int referentiel;
QDate date_validite_debut;
QDate date_validite_fin;
QString validite;
QString signiataire;
QString domaine;
void resetTableView();


public:

Certificat(){}
Certificat(QString,int,int,QDate,QDate,QString,QString,QString);

QString getTitulaire(){return titulaire;}
int getNumero(){return numero;}
int getReferentiel(){return referentiel;}
QDate getDate_validite_debut(){return date_validite_debut;}
QDate getDate_validite_fin(){return date_validite_fin;}
QString getvalidite(){return validite;}
QString getsigniataire(){return signiataire;}
QString getdomaine(){return domaine;}

void setTitulaire(QString tit){titulaire=tit;}
void setNumero(int num){numero=num;}
void setReferentiel(int ref){referentiel=ref;}
void setDate_validite_debut(QDate date_val_deb){date_validite_debut=date_val_deb;}
void setDate_validite_fin(QDate date_val_fin){date_validite_fin=date_val_fin;}
void setvalidite(QString val){validite=val;}
void setsigniataire(QString sign){signiataire=sign;}
void setdomaine(QString dom){domaine=dom;}
bool ajouteretatcoffre( int numero);
bool ajouter();
bool chercher(QString Id);
QSqlQueryModel * afficher();
bool supprimer(int numero);
QStandardItemModel *initialModel; // Declare the initial model
void generateStatistics();
QSqlQueryModel * affichercoffre();
bool ajouteretatcoffreclosed( int numero);
bool verifierExistence(int value);
void writelas();

};

#endif // CERTEFICAT_H
