#include "interface_certeficat.h"
#include "ui_interface_certeficat.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QtSql>  // Pour QSqlQuery, QSqlDatabase, QSqlTableModel, etc.
#include <QSqlError>  // Pour gérer les erreurs de base de données
#include <QSqlDriver>  // Pour les pilotes de base de données spécifiques
#include <QSqlRecord>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include <QPixmap>
#include <QLabel>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextEdit>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QTextDocument>
#include <QTextCursor>
#include <QCalendarWidget>
#include <QMap>
#include <QStringList>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLegendMarker>
#include <QtCharts>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QDate>
#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <QLabel>
#include "arduino.h"
#include "qrcode.h"
#include <fstream>
#include <QtSvg/QSvgRenderer>
#include "qrcodegen.h"

interface_certeficat::interface_certeficat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::interface_certeficat)
{
    ui->setupUi(this);
    for(const QCameraInfo &infor :QCameraInfo::availableCameras())
    {
    qDebug() <<infor.description();
    }
    M_Camera.reset(new QCamera(QCameraInfo::defaultCamera()));
    M_Camera->setViewfinder(ui->widget_camera_view) ;
    M_Camera_Image.reset(new QCameraImageCapture(M_Camera.data()));
    M_Camera_Image->setCaptureDestination((QCameraImageCapture::CaptureToFile));
    connect(M_Camera_Image.data(), &QCameraImageCapture::imageCaptured, this, &interface_certeficat::imageCaptured );
    ui->tableView_note->setModel(Etmp.afficherDATE());
    ui->tableView_main_interface->setModel(Etmp.afficher());
    ui->tableView_main_interface2->setModel(Etmp.afficher());
    ui->tableViewcoofre->setModel(Etmp.affichercoffre());
    ui->tableView_note->setModel(Etmp.afficherDATE());
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

interface_certeficat::~interface_certeficat()
{
    delete ui;

}





void interface_certeficat::on_pushButton_ajouter_clicked()
{
    int numero = ui->lineEdit_numero->text().toInt();
    int  referentiel = ui->lineEdit_referentiel->text().toInt();
    QDate dateValidite_debut = ui->dateEdit_debut->date();
    QDate dateValidite_fin = ui->dateEdit_fin->date();
    QString titulaire = ui->lineEdit_titulaire->text();
    QString domaine = ui->lineEdit_domaine->text();
    QString validite = ui->lineEdit_validite->text();
    QString signiataire = ui->lineEdit_signataire->text();




    if(numero == 0) {
        QMessageBox msgBox(QMessageBox::Warning, "Invalid ", "Numero doit etre rempli par des numero ", QMessageBox::Ok);
        msgBox.exec();
        ui->lineEdit_numero->setFocus();
    }


     if(titulaire.length() == 0) {
        QMessageBox msgBox(QMessageBox::Warning, "Invalid", "titulaire doit etre rempli par une chaine de caractere.",QMessageBox::Ok, this);
        msgBox.exec();
        ui->lineEdit_titulaire->setFocus();
    }
     if(domaine.length()==0){
        QMessageBox msgBox(QMessageBox::Warning, "Invalid ", " domaine doit etre rempli par une chaine de caractere ",QMessageBox::Ok, this);
        msgBox.exec();
        ui->lineEdit_domaine->setFocus();
    }

     if(validite.length()==0) {
        QMessageBox msgBox(QMessageBox::Warning, "Invalid ", "validite doit etre rempli par une chaine de caractere",QMessageBox::Ok, this);
        msgBox.exec();
        ui->lineEdit_validite->setFocus();
    }
     if(signiataire.length()==0) {
        QMessageBox msgBox(QMessageBox::Warning, "Invalid ", "signataire doit etre rempli par une chaine de caractere",QMessageBox::Ok, this);
        msgBox.exec();
        ui->lineEdit_validite->setFocus();
    }




    // Now, create the Certificat and add it to the database
    Certificat c(titulaire, numero, referentiel, dateValidite_debut ,dateValidite_fin,validite, signiataire, domaine);
    bool test = c.ajouter();

    if (test) {
        ui->tableView_main_interface->setModel(Etmp.afficher());
        ui->tableView_main_interface2->setModel(Etmp.afficher());
        interface_certeficat::on_pushButton_statistique_clicked();



        QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Ajout effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
            QObject::tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}



void interface_certeficat::on_pushButton_supp_clicked()
{
  QModelIndex index = ui->tableView_main_interface->currentIndex(); // Récupérer l'index de la ligne sélectionnée dans le TableView
  const int COLONNE_ID = 0;
  if (index.isValid()) {
      int row = index.row();

      int idToDelete = ui->tableView_main_interface->model()->data(ui->tableView_main_interface->model()->index(row, COLONNE_ID)).toInt(); // Assurez-vous que COLONNE_ID est correctement défini

      Certificat C2;
      C2.setNumero(idToDelete);

      if (C2.supprimer(C2.getNumero())) {
          ui->tableView_main_interface->setModel(Etmp.afficher());
          ui->tableView_main_interface2->setModel(Etmp.afficher());


          QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Certificat supprimé.\nCliquez sur OK pour continuer"), QMessageBox::Ok);

          // Rafraîchir la QTableView en supprimant la ligne supprimée
          ui->tableView_main_interface->model()->removeRow(row);

          ui->lineEdit_numero->clear();
          ui->lineEdit_domaine->clear();
          ui->lineEdit_validite->clear();
          ui->lineEdit_titulaire->clear();
          ui->lineEdit_signataire->clear();
          ui->dateEdit_debut->clear();
          ui->dateEdit_fin->clear();
          ui->lineEdit_referentiel->clear();
      } else {
          QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                                QObject::tr("Échec de la suppression.\nCliquez sur OK pour continuer"), QMessageBox::Ok);
      }
  } else {

      qDebug() << "Aucune ligne sélectionnée dans le TableView.";
      QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                            QObject::tr("Aucune ligne sélectionnée dans le TableView.\nCliquez sur OK pour continuer"), QMessageBox::Ok);
  }
}






void interface_certeficat::on_pushButton_Update_clicked()
{
  QModelIndex index = ui->tableView_main_interface2->currentIndex(); // Récupérer l'index de la ligne sélectionnée dans le TableView

  if (index.isValid()) {
      int row = index.row();

      // Récupérer l'ID de la ligne sélectionnée dans le TableView (supposons que la colonne 0 contient l'ID)
      int idToUpdate = ui->tableView_main_interface2->model()->data(ui->tableView_main_interface2->model()->index(row, 0)).toInt();

      // Récupérer les valeurs des champs de saisie
      int referentiel = ui->lineEdit_referentiel->text().toInt();
      QDate dateValidite_debut = ui->dateEdit_debut->date();
      QDate dateValidite_fin = ui->dateEdit_fin->date();
      QString titulaire = ui->lineEdit_titulaire->text();
      QString domaine = ui->lineEdit_domaine->text();
      QString validite = ui->lineEdit_validite->text();
      QString signiataire = ui->lineEdit_signataire->text();




             QSqlQuery qry;


             if(titulaire.length() == 0) {
                 QMessageBox msgBox(QMessageBox::Warning, "Invalid", "titulaire doit etre rempli par une chaine de caractere.",QMessageBox::Ok, this);
                 msgBox.exec();
                 ui->lineEdit_titulaire->setFocus();
             }
             else if(domaine.length()==0){
                 QMessageBox msgBox(QMessageBox::Warning, "Invalid ", " domaine doit etre rempli par une chaine de caractere ",QMessageBox::Ok, this);
                 msgBox.exec();
                 ui->lineEdit_domaine->setFocus();
             }

             else if(validite.length()==0) {
                 QMessageBox msgBox(QMessageBox::Warning, "Invalid ", "validite doit etre rempli par une chaine de caractere",QMessageBox::Ok, this);
                 msgBox.exec();
                 ui->lineEdit_validite->setFocus();
             }
             else if(signiataire.length()==0) {
                 QMessageBox msgBox(QMessageBox::Warning, "Invalid ", "signataire doit etre rempli par une chaine de caractere",QMessageBox::Ok, this);
                 msgBox.exec();
                 ui->lineEdit_validite->setFocus();
             }
             qry.prepare("UPDATE CERTIFICAT SET REFERENTIEL = :referentiel, TITULAIRE = :titulaire, DOMAINE = :domaine, VALIDITE = :validite, DATE_VALIDITE_DEBUT = :date_validite_debut, DATE_VALIDITE_FIN = :date_validite_fin, SIGNIATAIRE = :signataire WHERE NUMERO = :id");

             qry.bindValue(":referentiel", referentiel);
             qry.bindValue(":titulaire", titulaire);
             qry.bindValue(":domaine", domaine);
             qry.bindValue(":validite", validite);
             qry.bindValue(":date_validite_debut", dateValidite_debut);
             qry.bindValue(":date_validite_fin", dateValidite_fin);
             qry.bindValue(":signataire", signiataire);
             qry.bindValue(":id", idToUpdate);

             if (qry.exec()) {
               ui->tableView_main_interface2->viewport()->update();
               ui->tableView_main_interface2->setModel(Etmp.afficher());
               // Rafraîchir le modèle pour refléter les modifications
               QMessageBox::information(nullptr, QObject::tr("OK"),
                                      QObject::tr("Certificat est modifiee.\nCliquez sur OK pour continuer"), QMessageBox::Ok);
                 ui->tableView_main_interface2->model()->removeRow(row);

                 ui->lineEdit_numero->clear();
                 ui->lineEdit_domaine->clear();
                 ui->lineEdit_validite->clear();
                 ui->lineEdit_titulaire->clear();
                 ui->lineEdit_signataire->clear();
                 ui->dateEdit_debut->clear();
                 ui->dateEdit_fin->clear();
                 ui->lineEdit_referentiel->clear();
             } else {
                 QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                                       QObject::tr("Échec .\nCliquez sur OK pour continuer"), QMessageBox::Ok);
             }

         }

  }







void interface_certeficat::on_pushButton_rechercher_clicked()
{
    int numeroRechercher = ui->lineEdit_rechercher_num->text().toInt();

    if (numeroRechercher <= 0) {
        // Check to ensure the search number is valid
        QMessageBox::warning(this, "Error", "Please enter a valid certificate number.");
        return;
    }

    QSqlQuery query;//taqra ml l base acceder ll base
    query.prepare("SELECT * FROM CERTIFICAT WHERE NUMERO = :numero");
    query.bindValue(":numero", numeroRechercher);

    if (query.exec() && query.next()) {
        // A certificate with the searched number has been found

        // Create a new model and set it to the QTableView
        QStandardItemModel *model = new QStandardItemModel(this);  //l faza eli besh tdhaharlek star wahdou
        ui->tableView_main_interface->setModel(model);

        QStringList headers; //les entete taa tablou horizontale
        headers << "Numéro" << "Référentiel" << "Titulaire" << "Domaine" << "Validité" << "Date Validité" << "Signataire";
        model->setHorizontalHeaderLabels(headers);

        do {
            // Get the data from the query result
            int numero = query.value("NUMERO").toInt();
            int referentiel = query.value("REFERENTIEL").toInt();
            QDate dateValidite_debut = query.value("DATE_VALIDITE_DEBUT").toDate();
            QString titulaire = query.value("TITULAIRE").toString();
            QString domaine = query.value("DOMAINE").toString();
            QString validite = query.value("VALIDITE").toString();
            QString signiataire = query.value("SIGNIATAIRE").toString();
             QDate dateValidite_fin = query.value("DATE_VALIDITE_FIN").toDate();

            // Add a new row to the model ,yaani nhot les valeur eli
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::number(numero))
                     << new QStandardItem(QString::number(referentiel))
                     << new QStandardItem(titulaire)
                     << new QStandardItem(domaine)
                     << new QStandardItem(validite)
                     << new QStandardItem((dateValidite_debut).toString())
                     << new QStandardItem((dateValidite_fin).toString())
                     << new QStandardItem(signiataire);


            model->appendRow(rowItems);//ajouter une nouvelle ligne dans un modele sur QT
        } while (query.next());
    } else {
        // No certificate with the searched number was found
        QMessageBox::information(this, "Information", "No certificate with the number " + QString::number(numeroRechercher) + " was found.");
    }
}




void interface_certeficat::on_pushButton_retourner_clicked()
{
    ui->tableView_main_interface->setModel(Etmp.afficher());

}



void interface_certeficat::on_pushButton_trier_clicked()
{

    QSqlQueryModel *model =new QSqlQueryModel;
    model->setQuery("SELECT * FROM CERTIFICAT ORDER BY NUMERO +0");//forcer avec 0 le tri

        if (model->lastError().isValid()) {
            qDebug() << "echec : " << model->lastError().text();
            delete model;
            return;
            // Refresh the view
        }
        ui->tableView_main_interface->setModel(model);
        ui->tableView_main_interface2->setModel(model);

}




void interface_certeficat::on_tableView_main_interface_activated(const QModelIndex &index)
{
    QString val=ui->tableView_main_interface->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from CERTIFICAT where NUMERO='"+val+"'");
       if(qry.exec())
       {
        while(qry.next())
        {ui->lineEdit_numero->setText(qry.value(0).toString());
            ui->lineEdit_referentiel->setText(qry.value(1).toString());
            ui->lineEdit_domaine->setText(qry.value(3).toString());
            ui->lineEdit_validite->setText(qry.value(4).toString());
            ui->lineEdit_titulaire->setText(qry.value(2).toString());
            ui->lineEdit_signataire->setText(qry.value(6).toString());
            ui->dateEdit_debut->setDate(QDate::fromString(qry.value(5).toString(), "yyyy-MM-dd"));
            ui->dateEdit_fin->setDate(QDate::fromString(qry.value(7).toString(), "yyyy-MM-dd"));



        }
       }

}





void interface_certeficat::on_pushButton_scanne_clicked()
{

}

void interface_certeficat::on_pushButton_exporter_clicked()
{
    QString strStream;
      QTextStream out(&strStream);

      const int rowCount = ui->tableView_main_interface->model()->rowCount();
      const int columnCount = ui->tableView_main_interface->model()->columnCount();

      // HTML header
      out << "<html>\n"
             "<head>\n"
             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
             "<style type=\"text/css\">\n"
             "table {\n"
             "    border-collapse: collapse;\n"
             "    width: 100%;\n"
             "}\n"
             "th, td {\n"
             "    border: 1px solid #dddddd;\n"
             "    text-align: left;\n"
             "    padding: 8px;\n"
             "}\n"
             "th {\n"
             "    background-color: #f2f2f2;\n"
             "}\n"
             "</style>\n"
             << QString("<title>%1</title>\n").arg("strTitle")
             << "</head>\n"
             "<body bgcolor=#ffffff link=#5000A0>\n"
             "<center> <H1>TABLE DES CERTIFICATS </H1></br></br>\n";

      QDateTime currentDateTime = QDateTime::currentDateTime();
      out << QString("<p>Date d'exportation : %1</p>\n").arg(currentDateTime.toString());

      out << "<table>\n";

      out << "<thead><tr>";
      out << "<th>Numero</th>";
      for (int column = 0; column < columnCount; column++)
      {
          if (!ui->tableView_main_interface->isColumnHidden(column))
          {
              out << QString("<th>%1</th>").arg(ui->tableView_main_interface->model()->headerData(column, Qt::Horizontal).toString());
          }
      }
      out << "</tr></thead>\n";

      for (int row = 0; row < rowCount; row++)
      {
          out << "<tr>";
          out << "<td>" << row + 1 << "</td>";
          for (int column = 0; column < columnCount; column++)
          {
              if (!ui->tableView_main_interface->isColumnHidden(column))
              {
                  QString data = ui->tableView_main_interface->model()->data(ui->tableView_main_interface->model()->index(row, column)).toString().simplified();
                  out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
              }
          }
          out << "</tr>\n";
      }

      out << "</table></center>\n"
             "</body>\n"
             "</html>\n";

      QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
      if (QFileInfo(fileName).suffix().isEmpty())
      {
          fileName.append(".pdf");
      }

      QPrinter printer(QPrinter::PrinterResolution);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      printer.setOutputFileName(fileName);

      QTextDocument doc;
      doc.setHtml(strStream);
      doc.setPageSize(printer.pageRect().size());
      doc.print(&printer);
}






void interface_certeficat::on_pushButton_imprimer_clicked()
{   QPrinter printer(QPrinter::PrinterResolution);
    printer.setPageSize(QPrinter::A4);//thaded taille taa l page
    // Utiliser le format natif de l'imprimante

    // Afficher la boîte de dialogue d'aperçu
    QPrintPreviewDialog previewDialog(&printer, this);

    // Connecter le signal paintRequested avant d'exécuter la boîte de dialogue
    connect(&previewDialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));

    // Afficher la boîte de dialogue d'aperçu
    previewDialog.showMaximized();

    // Exécuter la boîte de dialogue
    if (previewDialog.exec() == QDialog::Accepted) {
        // Si l'utilisateur clique sur OK dans la boîte de dialogue d'aperçu, l'impression sera effectuée dans la fonction print.
    }
}


void  interface_certeficat::print(QPrinter *printer)
{

    QPainter painter(printer);
       painter.setRenderHint(QPainter::Antialiasing);
       painter.setRenderHint(QPainter::TextAntialiasing);
       painter.setRenderHint(QPainter::HighQualityAntialiasing);
       painter.setRenderHint(QPainter::SmoothPixmapTransform);

       QAbstractItemModel* originalModel = ui->tableView_main_interface->model();
       QString originalStylesheet = ui->tableView_main_interface->styleSheet();
       QSize originalSize = ui->tableView_main_interface->size();

       QStandardItemModel model;

       model.setHorizontalHeaderLabels({"NUMERO", "REFERENTIEL", "DOMAINE", "VALIDITE", "DATE_VALIDITE_DEBUT","SIGNIATAIRE" ,"DATE_VALIDITE_FIN"});

       int rowCount = originalModel->rowCount();
       int columnCount = originalModel->columnCount();
       for (int row = 0; row < rowCount; ++row)
       {
           QList<QStandardItem*> rowData;
           for (int col = 0; col < columnCount-1; ++col)
           {
               QStandardItem* item = new QStandardItem(originalModel->data(originalModel->index(row, col)).toString());
               rowData.append(item);
           }
           model.appendRow(rowData);
       }

       ui->tableView_main_interface->setModel(&model);
       ui->tableView_main_interface->resize(printer->width(), printer->height());
       ui->tableView_main_interface->render(&painter);

       ui->tableView_main_interface->setModel(originalModel);
       ui->tableView_main_interface->setStyleSheet(originalStylesheet);
       ui->tableView_main_interface->resize(originalSize);
}





void interface_certeficat::on_pushButton_mail_clicked()
{


}

void interface_certeficat::on_pushButton_ajouter_2_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void interface_certeficat::on_tableView_main_interface2_activated(const QModelIndex &index)
{
    QString val=ui->tableView_main_interface2->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from CERTIFICAT where NUMERO='"+val+"'");
       if(qry.exec())
       {
        while(qry.next())
        {ui->lineEdit_numero->setText(qry.value(0).toString());
            ui->lineEdit_referentiel->setText(qry.value(1).toString());
            ui->lineEdit_domaine->setText(qry.value(3).toString());
            ui->lineEdit_validite->setText(qry.value(4).toString());
            ui->lineEdit_titulaire->setText(qry.value(2).toString());
            ui->lineEdit_signataire->setText(qry.value(6).toString());
            ui->dateEdit_debut->setDate(QDate::fromString(qry.value(5).toString(), "yyyy-MM-dd"));
            ui->dateEdit_fin->setDate(QDate::fromString(qry.value(7).toString(), "yyyy-MM-dd"));



        }
       }
}

void interface_certeficat::on_pushButton_calendrier_clicked()
{

on_rechercher_clicked();
ui->tabWidget->setCurrentIndex(2);


}


void interface_certeficat::start_Camera()
{
    M_Camera->start();
}

void interface_certeficat::stop_Camera()
{
     M_Camera->stop();
}

void interface_certeficat::on_pushButton_start_cam_clicked()
{
    start_Camera();
}

void interface_certeficat::on_pushButton_stop_cam_clicked()
{
    stop_Camera();
}

void interface_certeficat::imageCaptured(int reqid, const QImage &img)
{
Q_UNUSED(reqid);
    ImageFromCamera=img.scaled(ui->widget_camera_view->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    counter = counter +1;
    QString ImagePath = QCoreApplication::applicationDirPath() + "/Image"+QString::number(counter) + ".bmp";
    QPixmap::fromImage(ImageFromCamera).save(ImagePath);





}

void interface_certeficat::on_pushButton_cap_clicked()
{

    M_Camera_Image->capture();

}

void interface_certeficat::on_pushButton_Update_2_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void interface_certeficat::on_pushButton_camera_clicked()
{
     ui->tabWidget->setCurrentIndex(4);
}
int interface_certeficat::calculerNombreCertificatsJanvier(int mois)
{
    QSqlQuery query;

        if (mois < 1 || mois > 12) {
            qDebug() << "Mois invalide. Le mois doit être compris entre 1 et 12.";
            return -1;  // Valeur d'erreur
        }

        query.prepare("SELECT COUNT(*) AS count FROM CERTIFICAT WHERE EXTRACT(MONTH FROM DATE_VALIDITE_DEBUT) = :mois");
        query.bindValue(":mois", mois);

        if (query.exec() && query.next()) {
            int nombreCertificats = query.value("count").toInt();
            return nombreCertificats;
        } else {
            qDebug() << "Erreur lors du calcul du nombre de certificats pour le mois " << mois;
            return -1;  // Valeur d'erreur
        }
}
int interface_certeficat::on_pushButton_statistique_2_clicked()
{
    int a=1;
     ui->tabWidget->setCurrentIndex(3);
     interface_certeficat::on_pushButton_statistique_clicked();

     return a;
}


void interface_certeficat::on_pushButton_statistique_clicked()
{
    interface_certeficat p;
    // Créer le graphique à barres
    QBarSet *set0 = new QBarSet("");
    QBarSet *set1 = new QBarSet("Nombre de certificats");

    // Ajoutez le nombre de certificats en janvier aux QBarSet
    *set0 << 0;
    *set1 << p.calculerNombreCertificatsJanvier(1) << p.calculerNombreCertificatsJanvier(2) << p.calculerNombreCertificatsJanvier(3) << p.calculerNombreCertificatsJanvier(4)
         << p.calculerNombreCertificatsJanvier(5) << p.calculerNombreCertificatsJanvier(6) << p.calculerNombreCertificatsJanvier(7) << p.calculerNombreCertificatsJanvier(8)
         << p.calculerNombreCertificatsJanvier(9) << p.calculerNombreCertificatsJanvier(10) << p.calculerNombreCertificatsJanvier(11) << p.calculerNombreCertificatsJanvier(12);

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("LE NOMBRE DE CERTEFICAT SELON MOIS");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "JANVIER" << "FEVRIER" << "MARS" << "AVRIL" << "MAI" << "JUIN" << "JUILLET" << "AOUT" << "SEPTEMBRE" << "OCTOBRE" << "NOVEMBRE" << "DECEMBRE";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    // Créer une scène graphique
    QGraphicsScene *scene = new QGraphicsScene(this);

    QChartView *chartView = new QChartView(chart);
    chartView->setMinimumSize(600, 400);

    scene->addWidget(chartView);

    // Définir la scène de QGraphicsView
    ui->graphicsView->setScene(scene);
    // Afficher la fenêtre
    ui->graphicsView->show();
    int totalCertificats = 0;
    for (int mois = 1; mois <= 12; ++mois) {
        totalCertificats += p.calculerNombreCertificatsJanvier(mois);
    }

    // Créez un modèle de tableau standard
    QStandardItemModel *model = new QStandardItemModel();

    // Ajoutez des en-têtes de colonne
    model->setHorizontalHeaderLabels(QStringList() << "Mois" << "Nombre de certificats" << "Pourcentage");

    // Ajoutez les résultats pour chaque mois
    for (int mois = 1; mois <= 12; ++mois) {
        int resultat = p.calculerNombreCertificatsJanvier(mois);

        // Obtenez le nom du mois
        QString nomMois;
        switch (mois) {
        case 1: nomMois = "Janvier"; break;
        case 2: nomMois = "Février"; break;
        case 3: nomMois = "Mars"; break;
        case 4: nomMois = "Avril"; break;
        case 5: nomMois = "Mai"; break;
        case 6: nomMois = "Juin"; break;
        case 7: nomMois = "Juillet"; break;
        case 8: nomMois = "Août"; break;
        case 9: nomMois = "Septembre"; break;
        case 10: nomMois = "Octobre"; break;
        case 11: nomMois = "Novembre"; break;
        case 12: nomMois = "Décembre"; break;
        default: nomMois = "Inconnu"; break;
        }

        // Calculez le pourcentage par rapport au total
        double pourcentage = 0.0;
        if (totalCertificats > 0) {
            pourcentage = static_cast<double>(resultat) / totalCertificats * 100.0;
        }

        // Ajoutez une nouvelle ligne au modèle avec le mois, le résultat et le pourcentage
        QList<QStandardItem *> items;
        items << new QStandardItem(nomMois);
        items << new QStandardItem(QString::number(resultat));
        items << new QStandardItem(QString("%1%").arg(QString::number(pourcentage, 'f', 2)));
        model->appendRow(items);
    }

    ui->tableView_Resultat->setModel(model);
}




void interface_certeficat::on_rechercher_clicked()
{
    QString result = checkDataForCurrentDate();  // Assuming checkDataForCurrentDate is a member function

       // Display the result in a QMessageBox
       QMessageBox::information(this, "EVENEMENT RESULTAT", result);
}

void interface_certeficat::on_pushButton_enregistrer_clicked()
{
    interface_certeficat c;
    c.checkDataForCurrentDate();
}

void interface_certeficat::on_pushButton_exp_stat_clicked()
{
    QString strStream;
      QTextStream out(&strStream);

      const int rowCount = ui->tableView_Resultat->model()->rowCount();
      const int columnCount = ui->tableView_Resultat->model()->columnCount();

      // HTML header
      out << "<html>\n"
             "<head>\n"
             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
             "<style type=\"text/css\">\n"
             "table {\n"
             "    border-collapse: collapse;\n"
             "    width: 100%;\n"
             "}\n"
             "th, td {\n"
             "    border: 1px solid #dddddd;\n"
             "    text-align: left;\n"
             "    padding: 8px;\n"
             "}\n"
             "th {\n"
             "    background-color: #f2f2f2;\n"
             "}\n"
             "</style>\n"
             << QString("<title>%1</title>\n").arg("strTitle")
             << "</head>\n"
             "<body bgcolor=#ffffff link=#5000A0>\n"
             "<center> <H1>Statistique Table </H1></br></br>\n";

      QDateTime currentDateTime = QDateTime::currentDateTime();
      out << QString("<p>Date d'exportation : %1</p>\n").arg(currentDateTime.toString());

      out << "<table>\n";

      out << "<thead><tr>";
      out << "<th>Numero</th>";
      for (int column = 0; column < columnCount; column++)
      {
          if (!ui->tableView_Resultat->isColumnHidden(column))
          {
              out << QString("<th>%1</th>").arg(ui->tableView_Resultat->model()->headerData(column, Qt::Horizontal).toString());
          }
      }
      out << "</tr></thead>\n";

      for (int row = 0; row < rowCount; row++)
      {
          out << "<tr>";
          out << "<td>" << row + 1 << "</td>";
          for (int column = 0; column < columnCount; column++)
          {
              if (!ui->tableView_Resultat->isColumnHidden(column))
              {
                  QString data = ui->tableView_Resultat->model()->data(ui->tableView_Resultat->model()->index(row, column)).toString().simplified();
                  out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
              }
          }
          out << "</tr>\n";
      }

      out << "</table></center>\n"
             "</body>\n"
             "</html>\n";

      QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
      if (QFileInfo(fileName).suffix().isEmpty())
      {
          fileName.append(".pdf");
      }

      QPrinter printer(QPrinter::PrinterResolution);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      printer.setOutputFileName(fileName);

      QTextDocument doc;
      doc.setHtml(strStream);
      doc.setPageSize(printer.pageRect().size());
      doc.print(&printer);
}

void interface_certeficat::on_pushButton_retournouvelle_clicked()
{
     ui->tabWidget->setCurrentIndex(0);
}

void interface_certeficat::on_pushButton_retourcal2_clicked()
{
     ui->tabWidget->setCurrentIndex(0);
}

void interface_certeficat::on_pushButton_stat3_clicked()
{
     ui->tabWidget->setCurrentIndex(0);
}

void interface_certeficat::on_pushButton_retourcam4_clicked()
{
     ui->tabWidget->setCurrentIndex(0);
}
void interface_certeficat::update_label()
{
     int intValue;

    data=A.read_from_arduino();
    if(data=="2")
            {


                 ui->label_eta_moteur->setText("ON TO 90 DEGRE");
                 ui->label_eta_coffre->setText("OUVERT");
                 QMessageBox::information(nullptr, QObject::tr("INFORMATION"),
                                     QObject::tr("PORTE OUVERT"), QMessageBox::Ok);


    }
   if(data=="3")
            {


                 ui->label_eta_moteur->setText("ON TO 0 DEGRE");
                 ui->label_eta_coffre->setText("FEMER");
                 QMessageBox::information(nullptr, QObject::tr("INFORMATION"),
                                     QObject::tr("PORTE FERMER"), QMessageBox::Ok);

    }


   //qDebug() << "converted" << data.toHex();
   // Ou
   qDebug() << "converted" << QString(data);
   bool ok;
   intValue = data.toInt(&ok);
   qDebug()<<"la valeur enttier"<<intValue;
   Certificat b;
   bool exists = b.verifierExistence(intValue);


   if (exists) {

       qDebug() << "ID exists in the database.";
       QMessageBox::information(nullptr, QObject::tr("INFORMATION"),
                             QObject::tr("ID exists in the database"), QMessageBox::Ok);

}
   ui->label_12id->setText(QString::number(intValue));
   Certificat c;
   bool test= c.ajouteretatcoffreclosed( intValue );
   if(test)
   {
       ui->tableViewcoofre->setModel(Etmp.affichercoffre());

       QMessageBox::information(nullptr, QObject::tr("valeur ajouter"),
                           QObject::tr("ETAT DE PORT AJOUTER"), QMessageBox::Ok);
   }
   if(ok)
   {

       }

}

void interface_certeficat::on_pushButton_clicked()
{
    A.write_to_arduino("1");


}

void interface_certeficat::zidlas()
{
    A.write_to_arduino("4");

}





void interface_certeficat::on_pushButton_2_clicked()
{

       A.write_to_arduino("2");


}

void interface_certeficat::on_pushButton_3_clicked()
{
     A.write_to_arduino("3");


}

void interface_certeficat::on_pushButton_4_clicked()
{
    A.write_to_arduino("4");



}
void interface_certeficat::on_calendarWidget_clicked(const QDate &date)
{
    bool ok;
    QString note = QInputDialog::getText(this, "Ajouter une note", "Entrez une note :", QLineEdit::Normal, "", &ok);

    qDebug() << note;

    QSqlQuery query;
    query.prepare("INSERT INTO EVENT (DATEE, NOTE) VALUES (:date, :note)");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":note", note);

    if (query.exec())
    {
        qDebug() << "Note inserted into the database";
    }
    else
    {
        qDebug() << "Error inserting note into the database:" << query.lastError().text();
    }

    // Refresh the notes for the selected date
    on_calendarWidget_selectionChanged();
}

void interface_certeficat::on_calendarWidget_selectionChanged()
{
    // Reuse the existing model or create a new one if needed
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView_note->model());
    if (!model)
    {
        model = new QStandardItemModel(this);
        model->setHorizontalHeaderLabels(QStringList() << "Date" << "Note");
    }
    else
    {
        model->removeRows(0, model->rowCount());  // Clear the existing table if the model is being reused
    }

    // Get the selected date from the calendar
    QDate selectedDate = ui->calendarWidget->selectedDate();

    QSqlQuery query;
    query.prepare("SELECT * FROM EVENT WHERE DATEE = :date");
    query.bindValue(":date", selectedDate.toString("yyyy-MM-dd"));

    if (query.exec())
    {
        while (query.next())
        {
            QString note = query.value("NOTE").toString();  // Corrected column name

            QList<QStandardItem *> rowItems;
            rowItems.append(new QStandardItem(selectedDate.toString("dd/MM/yyyy")));
            rowItems.append(new QStandardItem(note));
            model->appendRow(rowItems);
        }
    }
    else
    {
        qDebug() << "Error retrieving notes from the database:" << query.lastError().text();
    }

    // Set the model for the table
    ui->tableView_note->setModel(model);

    // Clear the tooltip
    ui->calendarWidget->setToolTip("");
}

QString interface_certeficat::checkDataForCurrentDate()
{
       QDate currentDate = QDate::currentDate();

       QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM EVENT WHERE DATEE = :date");
       query.bindValue(":date", currentDate.toString("yyyy-MM-dd"));

       if (query.exec() && query.next()) {
           int rowCount = query.value(0).toInt();
           qDebug() << "Rows found for the current date:" << rowCount;

           QString result = "pour aujourd-hui le : " + currentDate.toString("yyyy-MM-dd") + ": le nombre des evenement est  " + QString::number(rowCount);
           return result;
       } else {
           qDebug() << "Error checking data in the database:" << query.lastError().text();
           return "Error checking data in the database: " + query.lastError().text();
       }
}





void interface_certeficat::on_bagra_clicked()
{
    interface_certeficat c;
    c.checkDataForCurrentDate();
}

void interface_certeficat::on_tabWidget_tabBarClicked(int index)
{
    //on_rechercher_clicked();
}

void interface_certeficat::on_tabWidget_currentChanged(int index)
{
    ui->tableView_main_interface->setModel(Etmp.afficher());
    ui->tableView_main_interface2->setModel(Etmp.afficher());
    ui->tableViewcoofre->setModel(Etmp.affichercoffre());
    ui->tableView_note->setModel(Etmp.afficherDATE());
    interface_certeficat::on_pushButton_statistique_clicked();

}

void interface_certeficat::on_push_clicked()
{
    QModelIndex index = ui->tableView_note->currentIndex(); // Récupérer l'index de la ligne sélectionnée dans le TableView
    const int COLONNE_ID = 0;
    if (index.isValid()) {
        int row = index.row();

        int idToDelete = ui->tableView_note->model()->data(ui->tableView_note->model()->index(row, COLONNE_ID)).toInt(); // Assurez-vous que COLONNE_ID est correctement défini

        Certificat C2;
        C2.setNumero(idToDelete);

        if (C2.supprimer(C2.getNumero())) {
            ui->tableView_note->setModel(Etmp.afficherDATE());


            QMessageBox::information(nullptr, QObject::tr("OK"),
                                   QObject::tr("evenemet supprimé.\nCliquez sur OK pour continuer"), QMessageBox::Ok);

            ui->tableView_note->model()->removeRow(row);

            ui->lineEdit_numero->clear();
            ui->lineEdit_domaine->clear();
            ui->lineEdit_validite->clear();
            ui->lineEdit_titulaire->clear();
            ui->lineEdit_signataire->clear();
            ui->dateEdit_debut->clear();
            ui->dateEdit_fin->clear();
            ui->lineEdit_referentiel->clear();
        } else {
            QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                                  QObject::tr("Échec de la suppression.\nCliquez sur OK pour continuer"), QMessageBox::Ok);
        }
    } else {

        qDebug() << "Aucune ligne sélectionnée dans le TableView.";
        QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                              QObject::tr("Aucune ligne sélectionnée dans le TableView.\nCliquez sur OK pour continuer"), QMessageBox::Ok);
    }
}

void interface_certeficat::on_pushButton_imprimers_clicked()
{
    QPrinter printer(QPrinter::PrinterResolution);
       printer.setPageSize(QPrinter::A4);//thaded taille taa l page
       // Utiliser le format natif de l'imprimante

       // Afficher la boîte de dialogue d'aperçu
       QPrintPreviewDialog previewDialog(&printer, this);

       // Connecter le signal paintRequested avant d'exécuter la boîte de dialogue
       connect(&previewDialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));

       // Afficher la boîte de dialogue d'aperçu
       previewDialog.showMaximized();

       // Exécuter la boîte de dialogue
       if (previewDialog.exec() == QDialog::Accepted) {
           // Si l'utilisateur clique sur OK dans la boîte de dialogue d'aperçu, l'impression sera effectuée dans la fonction print.
       }
}

void interface_certeficat::on_pushButton_COFFRE_clicked()
{
    ui->tabWidget->setCurrentIndex(5);

}

void interface_certeficat::on_pushButton_QR_clicked()
{if(ui->tableView_main_interface2->currentIndex().row() == -1)
    {
        QMessageBox::information(nullptr, QObject::tr("QrCode"),
                                 QObject::tr("Veuillez choisir une activité du tableau.\n"
                                             "Cliquez sur OK pour quitter."), QMessageBox::Ok);
    }
    else
    {
        int numero = ui->tableView_main_interface2->model()->data(ui->tableView_main_interface2->model()->index(ui->tableView_main_interface2->currentIndex().row(), 0)).toInt();
        int referentiel = ui->tableView_main_interface2->model()->data(ui->tableView_main_interface2->model()->index(ui->tableView_main_interface2->currentIndex().row(), 2)).toInt();
        QString titulaire = ui->tableView_main_interface2->model()->data(ui->tableView_main_interface2->model()->index(ui->tableView_main_interface2->currentIndex().row(), 1)).toString();
        QString domaine = ui->tableView_main_interface2->model()->data(ui->tableView_main_interface2->model()->index(ui->tableView_main_interface2->currentIndex().row(), 3)).toString();
        QString validite = ui->tableView_main_interface2->model()->data(ui->tableView_main_interface2->model()->index(ui->tableView_main_interface2->currentIndex().row(), 4)).toString();
        QString signataire = ui->tableView_main_interface2->model()->data(ui->tableView_main_interface2->model()->index(ui->tableView_main_interface2->currentIndex().row(), 5)).toString();
        QString qrContent = QString("La certificat %1 son referentiel est %2. Son titulaire est est %3, son domaine %4, et sa validite est %5. son signiataire est %7 ")
                                .arg(numero).arg(referentiel).arg(titulaire).arg(domaine).arg(validite).arg(signataire);  // You need to replace "genre_placeholder" with the correct variable or expression for genre.

        // Convert QString to std::string
        std::string infoQRCode = qrContent.toStdString();

        // Generate and display QR Code
        qrcodegen::showQRCode(ui->graphicsView_2, infoQRCode);
    }

}
