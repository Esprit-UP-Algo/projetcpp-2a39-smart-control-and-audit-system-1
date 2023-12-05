#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDate>


class employe
{
    QString Nom,Prenom,Poste,mail,Adresse,mdp;
    int id,salaire,tel;
    QDate date;
public:



    employe();
    employe(int,QString, QString,QDate,int, QString,QString,int,QString,QString);
    QString getNom(){return Nom;}
    QString getAdresse(){return Adresse;}
    QString getmdp(){return mdp;}
    void setmdp(QString t){mdp=t;}

    int getsalaire(){return salaire;}
    int gettel(){return tel;}

    QString getPrenom(){return Prenom;}
    int getID(){return id;}
    QString getmail(){return mail;}
    void setmail(QString t){mail=t;}
    void settel(int d){tel=d;}

    QString getPoste(){return Poste;}
    void setsalaire(int d){salaire=d;}
    void setAdresse(QString t){Adresse=t;}

    void setNom(QString d){Nom=d;}
    void setPrenom(QString t){Prenom=t;}
    void setID(int id){this->id=id;}
     void setPoste(QString Poste){this->Poste=Poste;}
    bool ajouter();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel * afficher();
void trie();
};
#endif // EMPLOYE_H
