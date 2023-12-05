#ifndef RAPPORT_H
#define RAPPORT_H

#include <QString>
#include <QDate>
#include "ui_mainwindow.h"
#include "mainwindow.h"
class Rapport
{
public:
    Rapport();
    Rapport(int, QString, QString,QDate, QString, QString);
    QString getnom(){return nom;}
    QString getrapport(){return rapport;}
    QString getidemployee(){return idemployee;}
    QString getiduni(){return iduni;}
    QDate getdatee(){return datee;}
    int getid(){return id;}
    void setnom(QString nom){this->nom=nom;}
    void setrapport(QString rapport){this->rapport=rapport;}
    void setidemployee(QString idemployee){this->idemployee=idemployee;}
    void setiduni(QString iduni){this->iduni=iduni;}
    void setdatee(QDate datee){this->datee=datee;}
    void setid(int id){this->id=id;}
bool ajouter();
bool supprimer(QString id);
bool modifier();
void afficher(Ui::MainWindow *ui);

private :
    QString nom,rapport,idemployee,iduni;
    int id;
    QDate datee;

};class statt{
public:
    QString id,nom;

};

#endif // RAPPORT_H
