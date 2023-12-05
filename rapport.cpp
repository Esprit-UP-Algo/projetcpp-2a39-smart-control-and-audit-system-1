#include "rapport.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>

Rapport::Rapport()
{
id=0;
nom="";
rapport="";
iduni="";
idemployee="";
}
Rapport::Rapport(int id, QString nom, QString rapport,QDate datee, QString idemployee, QString iduni)
{
this->id=id;
    this->nom=nom;
this->rapport=rapport;
this ->iduni=iduni;
   this ->datee=datee;
    this ->idemployee=idemployee;
}
bool Rapport::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("insert into rapport (id,nom,rapport,datee,IDEMPLOYEE,iduni)""values(:id,:nom,:rapport,:datee,:IDEMPLOYEE,:iduni)");
    query.bindValue(":id", res);
            query.bindValue(":nom", nom);
    query.bindValue(":rapport", rapport);
    query.bindValue(":datee", datee);
    query.bindValue(":IDEMPLOYEE", "idemployee");
   query.bindValue(":iduni", iduni);
return query.exec();
}


bool Rapport::supprimer(QString id)
{
QSqlQuery query;

query.prepare("Delete from rapport where ID=:id");
query.bindValue(":id",id);
return query.exec();
}
bool Rapport::modifier()
{

    QSqlQuery query;
    QString res=QString::number(id);

          query.prepare("UPDATE rapport "" SET id=:id,nom=:nom,  rapport=:rapport, datee=:datee, iduni=:iduni , IDEMPLOYEE=IDEMPLOYEE  where ID='"+res+"' ");


          query.bindValue(":id", res);
          query.bindValue(":nom", nom);
          query.bindValue(":rapport", rapport);
          query.bindValue(":datee", datee);
            query.bindValue(":IDEMPLOYEE", idemployee);
            query.bindValue(":iduni", iduni);
        return    query.exec();
}

void Rapport::afficher(Ui::MainWindow *ui)
{

    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();

    qry->prepare("select * from rapport");
    qry->exec();
    modal->setQuery(*qry);
    modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    modal->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    modal->setHeaderData(2,Qt::Horizontal,QObject::tr("rapport"));
     modal->setHeaderData(3,Qt::Horizontal,QObject::tr("datee"));
       modal->setHeaderData(4,Qt::Horizontal,QObject::tr("idemployee"));
      modal->setHeaderData(5,Qt::Horizontal,QObject::tr("iduni"));
    ui->tableView->setModel(modal);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
