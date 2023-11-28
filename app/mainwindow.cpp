#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"arduino.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    {
        ui->setupUi(this);
            ui->C->hide();
         popUp = new PopUp();


        ///////////////////////////////////////////////////
        ui->id_ajouter->setValidator(new QIntValidator(0,9999999,this)) ;
        ui->id_modifier->setValidator(new QIntValidator(0,9999999,this)) ;
        ui->id_supprimer->setValidator(new QIntValidator(0,9999999,this)) ;

      ui->comboBox_supprimer->setModel(f.tester());

        //////////////////////////////////////////////////

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_N_clicked()
{
    popUp->setPopupText(ui->textEdit->toPlainText());

    popUp->show();
}
void MainWindow::on_pushButton_ajouter_clicked()
{


    QString ID_F, TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR;
    QMessageBox messageBox;

    ID_F=ui->id_ajouter->text();//.toint
    TYPE_FORMATION=ui->type_ajouter->text();
    NOM_FORMATION=ui->nomf_ajouter->text();
    NOM_FORMATEUR=ui->nomff_ajouter->text();

    QRegularExpression ID_FRegex("^[a-zA-Z0-9]{8}$");
     QRegularExpression referenceRegex("^[a-zA-Z]{1,10}$");
    formation f(ID_F, TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR);

    bool test=f.ajouter();
    if (test)
    {
        messageBox.information(nullptr, messageBox.tr("Succès"), messageBox.tr("Ajout effectué"));
        A.write_to_arduino("ajout de l'id "+ID_F);
                   QSqlQuery query;
                   query.prepare("INSERT INTO LCD (message, datemess) " "VALUES (:message, :datemess)");
                   query.bindValue(":message", "ajout de id:"+ID_F);
                   query.bindValue(":datemess", QDateTime::currentDateTime());
                   query.exec();
                   popUp->setPopupText("Ajout effectué");

                   popUp->show();
    }
     else
        messageBox.critical(nullptr, messageBox.tr("Echec"), messageBox.tr("Ajout non effectué"));

    ui->id_ajouter->clear();
    ui->type_ajouter->clear();
    ui->nomf_ajouter->clear();
    ui->nomff_ajouter->clear();

    ui->tableView_ajouter->setModel(Etmp.afficher());
    ui->tableView_supprimer->setModel(Etmp.afficher());


}


void MainWindow::on_modifier_clicked()
{


    QString ID_F, TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR;
    QMessageBox messageBox;

    ID_F=ui->id_modifier->text();
    TYPE_FORMATION=ui->type_modifier->text();
    NOM_FORMATION=ui->nomf_modifier->text();
    NOM_FORMATEUR=ui->nomff_modifier->text();

    formation f(ID_F, TYPE_FORMATION, NOM_FORMATION, NOM_FORMATEUR);

    bool test1=f.modifier();
    if (test1)
    {
        messageBox.information(nullptr, messageBox.tr("Succès"), messageBox.tr("modification effectuée"));
        A.write_to_arduino("Modif de l'id"+ID_F);
               QSqlQuery query;
               query.prepare("INSERT INTO LCD (message) " "VALUES (:message)");
               query.bindValue(":message", " "+ID_F);

               query.exec();
               popUp->setPopupText("modifier effectué");

               popUp->show();
    }
     else
        messageBox.critical(nullptr, messageBox.tr("Echec"), messageBox.tr("Ajout non effectué"));

    ui->id_modifier->clear();
    ui->type_modifier->clear();
    ui->nomf_modifier->clear();
    ui->nomff_modifier->clear();

    ui->tableView_ajouter->setModel(Etmp.afficher());
    ui->tableView_modifier->setModel(Etmp.afficher());
    ui->tableView_supprimer->setModel(Etmp.afficher());

}


void MainWindow::on_comboBox_modifier_currentIndexChanged(const QString &arg1)
{
    QString test=ui->comboBox_modifier->currentText();
    QSqlQuery qry;
    qry.prepare("select * from FORMATION where ID_F ='"+test+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
         ui->id_modifier->setText(qry.value(0).toString() );
         ui->type_modifier->setText(qry.value(1).toString());
         ui->nomf_modifier->setText(qry.value(2).toString());

         //génération QR Code
         std::string infoQRCode ="identifiant = "+ qry.value(0).toString().toStdString()
                     + "\nNom = "+ qry.value(2).toString().toStdString()
                     + "\nPrenom = "+ qry.value(1).toString().toStdString()
                     + "\nAge = "+ qry.value(3).toString().toStdString();

          //Afficher QR Code
          qrcodegen::showQRCode(ui->qr_graphicsView, infoQRCode);


        }
    }

}

void MainWindow::on_supprimer_clicked()
{
    QString ID_F;
    QMessageBox messageBox;

    ID_F =ui->id_supprimer->text();
    bool test=Etmp.supprimer(ID_F);

    if (test)
    {
        messageBox.information(nullptr, messageBox.tr("Succès"), messageBox.tr("Suppression effectuée"));
        A.write_to_arduino("supp de l'id "+ID_F);
               QSqlQuery query;
               query.prepare("INSERT INTO LCD (message) " "VALUES (:message)");
               query.bindValue(":message", "supprission de "+ID_F);

               query.exec();
               popUp->setPopupText("suppression effectué");

               popUp->show();
    }
     else
        messageBox.critical(nullptr, messageBox.tr("Echec"), messageBox.tr("Suppression non effectuée"));

    ui->id_supprimer->clear();

    ui->tableView_ajouter->setModel(Etmp.afficher());
    ui->tableView_supprimer->setModel(Etmp.afficher());

}
void MainWindow::on_reset_clicked()
{
    formation E1;

            bool test=E1.supprimerTout();

            QMessageBox msgBox;

            if(test)
               { msgBox.setText("reset  avec succes.");
                ui->tableView_consulter->setModel(E1.afficher());
                ui->tableView_ajouter->setModel(E1.afficher());
                ui->tableView_modifier->setModel(E1.afficher());
                ui->tableView_supprimer->setModel(E1.afficher());
                A.write_to_arduino("reset done :=) ");
                       QSqlQuery query;
                       query.prepare("INSERT INTO LCD (message) " "VALUES (:message)");
                       query.bindValue(":message", "supprission de ");

                       query.exec();
               }
            else
                msgBox.setText("Echec du reset.!!!");


            msgBox.exec();


            ui->comboBox_supprimer->setModel(f.tester());

}

 void MainWindow::on_comboBox_supprimer_currentIndexChanged(const QString &arg1)
{
    QString test=ui->comboBox_supprimer->currentText();
    QSqlQuery qry;
    qry.prepare("select * from FORMATION where ID_F ='"+test+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
         ui->id_supprimer->setText(qry.value(0).toString() );
        }
    }

}

void MainWindow::on_pushButton_ajouter_4_clicked()
{
    bool verif=false;
        QString log=ui->logo_2->text();
        QString pass=ui->pass_2->text();
        QSqlQuery qry;
        QMessageBox msgbox;
        if(qry.exec("select login, pass from FORMATION where login =  '"+log+"' and pass = '" +pass+ "' " ))
        {
            while(qry.next())
            {ui->stackedWidget->hide();
             ui->C->show() ; // c : tabwidget

                        verif=true;
            }

            if(verif==false)
            {

               msgbox.setText("id/mot de passe incorrect");
                       msgbox.exec();
            }
        }
        else
        {
            msgbox.setText("erreur req sql");
            A.write_to_arduino("Welcome ");
                   QSqlQuery query;
                   query.prepare("INSERT INTO LCD (message) " "VALUES (:message)");
                   query.bindValue(":message", "supprission de ");

                   query.exec();
                    msgbox.exec();
                    ui->C->show();
                    ui->stackedWidget->hide();
        }

}

void MainWindow::on_rechercher_bouton_clicked()
{
    QString type_recherche = ui->comboBox_type_rechercher->currentText();
    QString recherche=ui->rechercher->text();

    if (type_recherche =="identifiant")
    ui->tableView_consulter->setModel(f.rechercheridentifiant(recherche) ) ;
    else if (type_recherche =="typeformation")
    ui->tableView_consulter->setModel(f.recherchernom(recherche) ) ;
    else if (type_recherche =="nomformation")
    ui->tableView_consulter->setModel(f.recherchernomf(recherche) ) ;
    else if (type_recherche =="nomformateur")
    ui->tableView_consulter->setModel(f.recherchernomff(recherche) ) ;



}

void MainWindow::on_trier_clicked()
{
    QString type_tri = "identidaiant";
    QString test_ordre ="croissant" ;

    type_tri = ui->comboBox_type_trier->currentText();
    test_ordre = ui->comboBox_ordre->currentText() ;

        if ((type_tri == "identifiant") && (test_ordre == "croissant") )

        ui->tableView_consulter->setModel(f.tricroissant_ID_F());

        else if ((type_tri == "typeformation" ) && (test_ordre == "croissant") )
        ui->tableView_consulter->setModel(f.tricroissant_nom());

        else if ((type_tri == "nomformation" ) && (test_ordre == "croissant") )
        ui->tableView_consulter->setModel(f.tricroissant_prenom());

        else if ((type_tri == "nomformateur" ) && (test_ordre == "croissant") )
        ui->tableView_consulter->setModel(f.tricroissant_age());

////////////////////////////////////////////////////////////////////////////////////////////

        if ((type_tri == "identifiant") && (test_ordre == "decroissant") )
        ui->tableView_consulter->setModel(f.tridecroissant_identifiant());

        else if ((type_tri == "typeformation" ) && (test_ordre == "decroissant") )
        ui->tableView_consulter->setModel(f.tridecroissant_nom());

        else if ((type_tri == "nomformation" ) && (test_ordre == "decroissant") )
        ui->tableView_consulter->setModel(f.tridecroissant_prenom());

        else if ((type_tri == "nomformateur" ) && (test_ordre == "decroissant") )
        ui->tableView_consulter->setModel(f.tridecroissant_age());

}

void MainWindow::on_PDF_clicked()
{
    QString strStream;
                  QTextStream out(&strStream);
                  const int rowCount = ui->tableView_consulter->model()->rowCount();
                  const int columnCount =ui->tableView_consulter->model()->columnCount();


                  out <<  "<html>\n"
                          "<head>\n"
                          "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          <<  QString("<title>%1</title>\n").arg("eleve")
                          <<  "</head>\n"
                          "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                              "<h1>Liste des Employes :</h1>"

                              "<table border=1 cellspacing=0 cellpadding=2>\n";

                  // headers
                      out << "<thead><tr bgcolor=#f0f0f0>";
                      for (int column = 0; column < columnCount; column++)
                          if (!ui->tableView_consulter->isColumnHidden(column))
                              out << QString("<th>%1</th>").arg(ui->tableView_consulter->model()->headerData(column, Qt::Horizontal).toString());
                      out << "</tr></thead>\n";
                      // data table
                         for (int row = 0; row < rowCount; row++) {
                             out << "<tr>";
                             for (int column = 0; column < columnCount; column++) {
                                 if (!ui->tableView_consulter->isColumnHidden(column)) {
                                     QString data = ui->tableView_consulter->model()->data(ui->tableView_consulter->model()->index(row, column)).toString().simplified();
                                     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                 }
                             }
                             out << "</tr>\n";
                         }
                         out <<  "</table>\n"
                             "</body>\n"
                             "</html>\n";



          QTextDocument *document = new QTextDocument();
          document->setHtml(strStream);


          //QTextDocument document;
          //document.setHtml(html);
          QPrinter printer(QPrinter::PrinterResolution);
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setOutputFileName("C:/TAHA/PDFF.pdf");
          document->print(&printer);

          cout<<"Done !\n"<<endl;
}

void MainWindow::on_consulter_clicked()
{
    QString identifiant= ui->id_consulter->text() ;

    QSqlQuery qry;
    qry.prepare("select * from FORMATION where ID_F = :ID_F") ;
    qry.bindValue(":ID_F", identifiant);

    if (!qry.exec())
        cout << "erreur";
        qry.next();
         ui->identifiant_consulter->setText(qry.value(0).toString() );
         ui->nom_consulter->setText(qry.value(1).toString());
         ui->prenom_consulter->setText(qry.value(2).toString());
         ui->age_consulter->setText(qry.value(3).toString());

        //générer QR Code
        std::string infoQRCode ="identifiant = "+ qry.value(0).toString().toStdString()
                    + "\nNom = "+ qry.value(1).toString().toStdString()
                    + "\nPrenom = "+ qry.value(2).toString().toStdString()
                    + "\nAge = "+ qry.value(3).toString().toStdString();

         //afficher QR Code
         qrcodegen::showQRCode(ui->qr_graphicsView_consulter, infoQRCode);


}
