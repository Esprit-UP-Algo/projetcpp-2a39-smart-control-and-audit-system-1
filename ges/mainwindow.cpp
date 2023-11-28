#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "universite.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <iostream>
#include<QQuickItem>
#include "smtp.h"
#include <QtNetwork>
#include <QDesktopServices>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>
#include <QTextDocument>
#include <QDateTime>
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



#include<QtWidgets>
#include<QPrinter>
#include<QPrintDialog>
#include<QPainter>
#include<QAbstractItemModel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tab_universite->setModel(u.afficher());


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


          int ret=A.connect_arduino(); // lancer la connexion à arduino
          switch(ret){
          case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
              break;
          case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
             break;
          case(-1):qDebug() << "arduino is not available";
          }
           QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
           //le slot update_label suite à la reception du signal readyRead (reception des données).




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

    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"), QObject::tr("Ajout non effectué."), QMessageBox::Cancel);
    }
    // Historique
    QFile file("C:/Users/M S I/Documents/Audit-2A39-Gestion_des_universites/Historique.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;
    QTextStream cout(&file);
    QString d_info = QDateTime::currentDateTime().toString();
    QString message2 = d_info + " - Un client a été ajouté avec l'ID " + QString::number(id) + " par  salim\n";
    cout << message2;
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

            // Historique
            QFile file("C:/Users/M S I/Documents/Audit-2A39-Gestion_des_universites/Historique.txt");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;
            QTextStream cout(&file);
            QString d_info = QDateTime::currentDateTime().toString();
            QString message2 = d_info + " - Un client a été modifié avec la id " + QString::number(id) + " par  salim\n";
            cout << message2;
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
    //Historique
    QFile file("C:/Users/M S I/Documents/Audit-2A39-Gestion_des_universites/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;
            QTextStream cout(&file);
            QString d_info = QDateTime::currentDateTime().toString();
           QString message2 = d_info + " - Un client a été supprimé avec la id " + QString::number(id) + " par  salim\n";
            cout << message2;
}

void MainWindow::on_pb_annuler_supp_clicked()
{
ui->le_id_supp->clear();
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



    void MainWindow::on_pushButton_clicked()
    {
        QSqlQueryModel* model = u1.afficherH();
        QPrinter printer; // Create a QPrinter object for printing.
        QPrintDialog printDialog(&printer); // Create a print dialog, associating it with the printer.

        // Check if the user accepted the print dialog.
        if (printDialog.exec() == QDialog::Accepted) {
            QPainter painter(&printer); // Create a QPainter object associated with the printer.

            // Loop through the rows and columns of the table model for printing.
            for (int row = 0; row < model->rowCount(); ++row)
 {
                for (int col = 0; col < model->columnCount(); ++col) {
                    QModelIndex index = model->index(row, col);
                    QString data =model->data(index).toString();

                    // Draw the data from the table at specific coordinates.
                    painter.drawText(100 * col, 100 * row, data);
                }
            }
        }
    }



void MainWindow::on_pushButton_refresh_clicked()
{
    ui->tab_universite->setModel(u.afficher());

}


void MainWindow::on_sendMail_2_clicked()
{QString mail=ui->from_2->text();
QString password=ui->paswd_2->text();
QString recpt=ui->to_2->text();
QString objet=ui->subject_2->text();
QString description=ui->msg_2->toPlainText();
Smtp *smtp = new Smtp(mail,password,"smtp.gmail.com");
smtp->sendMail(mail,recpt ,objet,description);}


void MainWindow::mailsent_2(QString status)
{if(status == "Message sent")
QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
ui->to_2->clear();
ui->subject_2->clear();
ui->msg_2->clear();
ui->paswd_2->clear();
ui->from_2->clear();}

void MainWindow::readfile(){
    QString filename="C:/Users/M S I/Documents/Audit-2A39-Gestion_des_universites/Historique.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" ...";
    }
    QString line;
    ui->Histo->clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            ui->Histo->setText(ui->Histo->toPlainText()+line+"\n");
            qDebug() << "linea: "<<line;
        }
    }
    file.close();
}

void MainWindow::on_tabWidget_currentChanged()
{
    readfile();

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





void MainWindow::on_rec_clicked()
{
    A.write_to_arduino("1");

    // Read data from Arduino

   /* data = A.read_from_arduino();

    bool ok;
    int intValue = data.toInt(&ok);
    if(ok)
    {
        qDebug()<<"converted"<<intValue;
    }
      //  Certificat c;
        bool exists = c.verifierExistence(intValue);


        if (exists) {
            qDebug() << "ID exists in the database.";

            Certificat c;
            bool test= c.ajouteretatcoffreclosed(  data, intValue );
            if(test)
            {
                QMessageBox::information(nullptr, QObject::tr("valeur ajouter"),
                                      QObject::tr("ETAT DE PORT AJOUTER"), QMessageBox::Ok);
            }

    }*/
}

void MainWindow::on_pushButton_2_clicked()
{
    // Affichage de "porte ouverte" sur l'afficheur LCD
    A.write_to_arduino("2");
}

void MainWindow::on_pushButton_3_clicked()
{
      A.write_to_arduino("3");
}
