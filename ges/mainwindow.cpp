#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "universite.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <iostream>
#include<QQuickItem>

using namespace std;

//Include Stats
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
QT_CHARTS_USE_NAMESPACE
//Fin Include Stats

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_universite->setModel(u.afficher());
        ui->tab_historique->setModel(u.afficherH());
    ui->le_id->setValidator(new QIntValidator(0,99999999,this));
      ui->le_id_modif->setValidator(new QIntValidator(0,99999999,this));
        ui->le_id_supp->setValidator(new QIntValidator(0,99999999,this));
     ui->le_budget->setValidator(new QIntValidator(0,99999999,this));
      ui->le_budget_modif->setValidator(new QIntValidator(0,99999999,this));
       ui->le_budget_modif->setValidator(new QIntValidator(0,99999999,this));
        ui->le_etudiant->setValidator(new QIntValidator(0,99999999,this));
        ui->le_etudiant_modif->setValidator(new QIntValidator(0,99999999,this));
       ui->tab_universite->setModel(u.afficher());
       QRegExp regex("[^0-9]*");
       QRegExpValidator* validator = new QRegExpValidator(regex, this);
       ui->le_nom->setValidator(validator);
       ui->le_adresse->setValidator(validator);
        ui->le_nom_modif->setValidator(validator);
          ui->le_adresse_modif->setValidator(validator);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id = ui->le_id->text().toInt();
    QString nom = ui->le_nom->text();
    QString adresse = ui->le_adresse->text();
    int nb_etudiants = ui->le_etudiant->text().toInt();
    QDate date_visite = ui->date_ajout->date();
    float budget_annuel = ui->le_budget->text().toFloat();

    universite u(id, nom, adresse, nb_etudiants, date_visite, budget_annuel);

    // Ajoutez les données dans "universite" et "historique"
    bool test = u.ajouter_universite(); // Ajout dans "universite" et "historique"

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("ok"), QObject::tr("Ajout effectué\n" "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_universite->setModel(u.afficher()); // Affichage dans "tab_universite"

        // Mettez à jour "tab_historique" avec les données actuelles de "historique"
        ui->tab_historique->setModel(u.afficherH());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"), QObject::tr("Ajout non effectué."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pb_annuler_ajout_clicked()
{
    ui->le_id->clear();
    ui->le_nom->clear();
    ui->le_adresse->clear();
    ui->le_etudiant->clear();
    ui->date_ajout->clear();
    ui->le_budget->clear();
}

void MainWindow::on_pb_modif_clicked()
{
    int id = ui->le_id_modif->text().toInt();
    QString nom = ui->le_nom_modif->text();
    QString adresse = ui->le_adresse_modif->text();
    int nb_etudiants = ui->le_etudiant_modif->text().toInt();
    QDate date_visite = ui->date_modif->date();
    float budget_annuel = ui->le_budget_modif->text().toFloat();

    // Vérifie si l'identifiant existe en utilisant la fonction afficher
    QSqlQueryModel* model = u2.afficher();
    bool idExists = false;

    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex index = model->index(row, 0); // Colonne de l'identifiant
        if (index.data().toInt() == id) {
            idExists = true;
            break;
        }
    }

    if (idExists) {
        // L'identifiant existe, essayez de le modifier
        bool test = u2.modifier_universite(id, nom, adresse, nb_etudiants, date_visite, budget_annuel);

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Modification effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
            ui->tab_universite->setModel(u2.afficher());
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Modification non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    } else {
        // L'identifiant n'existe pas
        QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Identifiant introuvable.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_annuler_modif_clicked()
{
    ui->le_id_modif->clear();
    ui->le_nom_modif->clear();
    ui->le_adresse_modif->clear();
    ui->le_etudiant_modif->clear();
    ui->date_modif->clear();
    ui->le_budget_modif->clear();

}

void MainWindow::on_pb_supprimer_clicked()
{
    int id = ui->le_id_supp->text().toInt();

    // Vérifie si l'identifiant existe en utilisant la fonction afficher
    QSqlQueryModel* model = u1.afficher();
    bool idExists = false;

    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex index = model->index(row, 0); // Colonne de l'identifiant
        if (index.data().toInt() == id) {
            idExists = true;
            break;
        }
    }

    if (idExists) {
        // L'identifiant existe, essayez de le supprimer
        bool test = u1.supprimer_universite(id);

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
            ui->tab_universite->setModel(u1.afficher());
        }
    } else {
        // L'identifiant n'existe pas
        QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Identifiant introuvable suppression non effectuée .\nClique Cancel pour sortir."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_annuler_supp_clicked()
{
ui->le_id_supp->clear();
}



void MainWindow::on_le_recherche_textChanged(const QString &arg1)
{
    if(ui->le_recherche->text()!="")
         {
        QString nom=ui->le_recherche->text();
        ui->tab_universite->setModel(u.rechercher(nom));
    }
     else
        ui->tab_universite->setModel(u.afficher());
    }


void MainWindow::on_cb_tri_currentIndexChanged(int index)
{
    if(index==1)
              ui->tab_universite->setModel(u.tri_id());
    else if(index==2)
              ui->tab_universite->setModel(u.tri_adresse());
    else if(index==3)
              ui->tab_universite->setModel(u.tri_date_visite());
}

void MainWindow::stats(QString table,QString critere,int valeur1,int valeur2,QString unite)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        QString valeur1QString = QString::number(valeur1);
        QString valeur2QString = QString::number(valeur2);

        QString queryTemplate = "select * from %1 where %2 %3 %4";
        QString queryTemplateBetween = "select * from %1 where %2 between %3 and %4";

        model->setQuery(queryTemplate.arg(table, critere, "<", valeur1QString));
        float countFirst = model->rowCount();
        model->setQuery(queryTemplateBetween.arg(table, critere, valeur1QString, valeur2QString));
        float countSecond = model->rowCount();
        model->setQuery(queryTemplate.arg(table, critere, ">", valeur2QString));
        float countThird = model->rowCount();
        float total = countFirst + countSecond + countThird;

        QString a = QString("moins de %1 %2 %3%").arg(valeur1QString, unite, QString::number((countFirst * 100) / total, 'f', 2));
        QString b = QString("entre %1 et %2 %3 %4%").arg(valeur1QString, valeur2QString, unite, QString::number((countSecond * 100) / total, 'f', 2));
        QString c = QString("Plus que %1 %2 %3%").arg(valeur2QString, unite, QString::number((countThird * 100) / total, 'f', 2));

        QPieSeries *series = new QPieSeries();
        series->append(a, countFirst);
        series->append(b, countSecond);
        series->append(c, countThird);

        for (QPieSlice *slice : series->slices()) {
            slice->setLabelVisible();
            slice->setPen(QPen());
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Pourcentage Par " + critere + ": Nombre Des " + table + ":" + QString::number(total));
        chart->legend()->hide();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(1000, 500);
        chartView->show();
    }

    void MainWindow::on_statsnbr_etudiants_clicked() {
        stats("universite", "NB_ETUDIANTS", 100, 200, "ETUDIANTS");
    }

    void MainWindow::on_stats_budget_clicked() {
        stats("universite", "BUDGET_ANNUEL", 50, 100, "Mille Dinars");
    }


