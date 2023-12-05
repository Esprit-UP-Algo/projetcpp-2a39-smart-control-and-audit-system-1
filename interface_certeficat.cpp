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

    ui->tableView_main_interface->setModel(Etmp.afficher());
    ui->tableView_main_interface2->setModel(Etmp.afficher());
    ui->tableViewcoofre->setModel(Etmp.affichercoffre());
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
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Exporter le tableau au format PDF", "", "Fichiers PDF (*.pdf)");//permet de sélectionner des fichiers ou des répertoires
//filepath:stock le chemain de fichier
    //getSaveFileName:choisir un emplacement et un nom ll fichier
          if (filePath.isEmpty())
          {
              return;
          }

          QPrinter printer(QPrinter::PrinterResolution); //QPrinter besh l qt yaaref eli enty une imprimente virtuelle
          printer.setOutputFormat(QPrinter::PdfFormat); //besh yaaref eli l format fl sortie type taa3ou PDF
          printer.setOutputFileName(filePath);//besh yaaref chemain
          printer.setPageSize(QPrinter::Tabloid);//thaded taille taa l page


          QPainter painter(&printer);//ay haj amarssouma besh natb3ouha bl machine virtuelle
          painter.setRenderHint(QPainter::Antialiasing);//tech graphidue besh l bord ywaliw plus lisse
          painter.setRenderHint(QPainter::TextAntialiasing);//les contours de caractere plus lisses
          painter.setRenderHint(QPainter::HighQualityAntialiasing);//ll qualite
          painter.setRenderHint(QPainter::SmoothPixmapTransform);//améliore la qualité du rendu des images ki ne9elbouha wela ay faaza



            QFont titleFont;
          titleFont.setBold(true);
          titleFont.setPixelSize(20);
          painter.setFont(titleFont);

          QRect titleRect(50, 50, printer.width() - 100, 30);
          painter.drawText(titleRect, Qt::AlignCenter, "Titre du tableau");

          // Ajouter la date d'exportation
          QFont dateFont;
          dateFont.setPixelSize(12);
          painter.setFont(dateFont);

          QDateTime currentDate = QDateTime::currentDateTime();
          QString exportDate = "Date d'exportation: " + currentDate.toString("dd.MM.yyyy hh:mm:ss");

          QRect dateRect(50, 80, printer.width() - 100, 20);
          painter.drawText(dateRect, Qt::AlignCenter, exportDate);

          QAbstractItemModel* originalModel = ui->tableView_main_interface->model();//recuperer un pointeur vers la table ppour acceder au donnes actuelle de la table
          QString originalStylesheet = ui->tableView_main_interface->styleSheet();//recuperer une feuille sur qt
          QSize originalSize = ui->tableView_main_interface->size();//TAILLE DE LA TABLE X,Y taille bidemonsionnelle

          QStandardItemModel model;

          model.setHorizontalHeaderLabels({"NUMERO", "REFERENTIEL", "DOMAINE", "VALIDITE", "DATE_VALIDITE_DEBUT","SIGNIATAIRE" ,"DATE_VALIDITE_FIN"});

          int rowCount = originalModel->rowCount();//pour obtenir le nombre de ligne
          int columnCount = originalModel->columnCount();//nombre de colonnes
          for (int row = 0; row < rowCount; ++row)
          {
              QList<QStandardItem*> rowData;//l kol ligne nakhel9ou rowdata nesstokio fih les donnes taa ligne
              for (int col = 0; col < columnCount-1; ++col)
              {
                  QStandardItem* item = new QStandardItem(originalModel->data(originalModel->index(row, col)).toString());//nesstokiw led donner eli fi col row yaani mither (2.3) w nrodouhom des chaines de caractere
                  rowData.append(item);
              }
              model.appendRow(rowData);
          }

          ui->tableView_main_interface->setModel(&model);//laffichage de noubelle model

          ui->tableView_main_interface->resize(printer.width(), printer.height());//besh nhafedh aal led dimensions

          ui->tableView_main_interface->render(&painter);//besh nhawlou mn tabel l pdf

          ui->tableView_main_interface->setModel(originalModel);// baaed l imrimentatioon nraj3ou l table
          ui->tableView_main_interface->setStyleSheet(originalStylesheet);// revenir à l'apparence visuelle initiale de la table.
          ui->tableView_main_interface->resize(originalSize);//dimensions d'origine après le processus d'impression.

          painter.end();
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


void interface_certeficat::on_calendarWidget_clicked(const QDate &date)
{
    {
        // Demander à l'utilisateur d'ajouter une note
        bool ok;
        QString note = QInputDialog::getText(this, "Ajouter une note", "Entrez une note :", QLineEdit::Normal, "", &ok);

        // Si l'utilisateur clique sur "OK", afficher un message avec la note
        if (ok && !note.isEmpty())
        {
            QString message = QString("Note ajoutée le %1 : %2").arg(date.toString("dd/MM/yyyy")).arg(note);
            QMessageBox::information(this, "Note ajoutée", message);

            // Stocker la note dans la liste des notes
            NoteEntry entry;
            entry.date = date;
            entry.note = note;
            notes.append(entry);

            // Rafraîchir les info-bulles pour prendre en compte la nouvelle note
            on_calendarWidget_selectionChanged();
        }
    }
}

void interface_certeficat::on_calendarWidget_selectionChanged()
{        // Reuse the existing model or create a new one if needed
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView_note->model());
    if (!model) {
        model = new QStandardItemModel(this);
        model->setHorizontalHeaderLabels(QStringList() << "Date" << "Note");
    } else {
        // Clear the existing table if the model is being reused
    }

    // La date sélectionnée dans le calendrier
    QDate selectedDate = ui->calendarWidget->selectedDate();

    // Liste pour stocker toutes les notes associées à la date sélectionnée
    QList<NoteEntry> selectedNotes;

    // Remplir la liste des notes associées à la date sélectionnée
    foreach (const NoteEntry &entry, notes) {
        if (selectedDate == entry.date) {
            selectedNotes.append(entry);
        }
    }

    // Ajouter les notes à la table
    foreach (const NoteEntry &entry, selectedNotes) {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(entry.date.toString("dd/MM/yyyy")));
        rowItems.append(new QStandardItem(entry.note));
        model->appendRow(rowItems);
    }

    // Définir le modèle pour le tableau
    ui->tableView_note->setModel(model);

    // Effacer l'info-bulle
    ui->calendarWidget->setToolTip("");


}


void interface_certeficat::on_pushButton_enregistrer_clicked()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView_note->model());

       // Check if the model exists
       if (!model) {
           qDebug() << "No model available for export.";
           return;
       }

       // Ask the user to choose a file path
       QString filePath = QFileDialog::getSaveFileName(this, tr("Export Table to TXT"), "", tr("Text Files (*.txt);;All Files (*)"));
       if (filePath.isEmpty()) {
           qDebug() << "Export canceled or no file selected.";
           return;
       }

       // Open the file for writing
       QFile file(filePath);
       if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
           QTextStream out(&file);

           // Write headers to the file
           QStringList headers;
           headers << "#" << "Date" << "***"<<"Note";  // Added a column for row numbers
           out << headers.join('\t') << '\n';

           // Write data to the file
           for (int row = 0; row < model->rowCount(); ++row) {
               QStringList rowData;

               // Add row number
               rowData << QString::number(row + 1);

               for (int column = 0; column < model->columnCount(); ++column) {
                   // Get the data for each cell
                   QString data = model->item(row, column)->text();
                   rowData << data;
               }
               out << rowData.join('\t') << '\n';
           }

           // Close the file
           file.close();
           qDebug() << "Export successful. File saved at:" << filePath;
       } else {
           qDebug() << "Failed to open the file for export:" << file.errorString();
       }
}

void interface_certeficat::on_pushButton_exp_stat_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Exporter le tableau au format PDF", "", "Fichiers PDF (*.pdf)");//permet de sélectionner des fichiers ou des répertoires
//filepath:stock le chemain de fichier
    //getSaveFileName:choisir un emplacement et un nom ll fichier
          if (filePath.isEmpty())
          {
              return;
          }

          QPrinter printer(QPrinter::PrinterResolution); //QPrinter besh l qt yaaref eli enty une imprimente virtuelle
          printer.setOutputFormat(QPrinter::PdfFormat); //besh yaaref eli l format fl sortie type taa3ou PDF
          printer.setOutputFileName(filePath);//besh yaaref chemain
          printer.setPageSize(QPrinter::Tabloid);//thaded taille taa l page


          QPainter painter(&printer);//ay haj amarssouma besh natb3ouha bl machine virtuelle
          painter.setRenderHint(QPainter::Antialiasing);//tech graphidue besh l bord ywaliw plus lisse
          painter.setRenderHint(QPainter::TextAntialiasing);//les contours de caractere plus lisses
          painter.setRenderHint(QPainter::HighQualityAntialiasing);//ll qualite
          painter.setRenderHint(QPainter::SmoothPixmapTransform);//améliore la qualité du rendu des images ki ne9elbouha wela ay faaza


          QAbstractItemModel* originalModel = ui->tableView_Resultat->model();//recuperer un pointeur vers la table ppour acceder au donnes actuelle de la table
          QString originalStylesheet = ui->tableView_Resultat->styleSheet();//recuperer une feuille sur qt
          QSize originalSize = ui->tableView_Resultat->size();//TAILLE DE LA TABLE X,Y taille bidemonsionnelle

          QStandardItemModel model;

          model.setHorizontalHeaderLabels({"MOIS", "NOMBRE CERTEFICAT/MOIS", "POURCENTAGE"});

          int rowCount = originalModel->rowCount();//pour obtenir le nombre de ligne
          int columnCount = originalModel->columnCount();//nombre de colonnes
          for (int row = 0; row < rowCount; ++row)
          {
              QList<QStandardItem*> rowData;//l kol ligne nakhel9ou rowdata nesstokio fih les donnes taa ligne
              for (int col = 0; col < columnCount; ++col)
              {
                  QStandardItem* item = new QStandardItem(originalModel->data(originalModel->index(row, col)).toString());//nesstokiw led donner eli fi col row yaani mither (2.3) w nrodouhom des chaines de caractere
                  rowData.append(item);
              }
              model.appendRow(rowData);
          }

          ui->tableView_Resultat->setModel(&model);//laffichage de noubelle model

          ui->tableView_Resultat->resize(printer.width(), printer.height());//besh nhafedh aal led dimensions

          ui->tableView_Resultat->render(&painter);//besh nhawlou mn tabel l pdf

          ui->tableView_Resultat->setModel(originalModel);// baaed l imrimentatioon nraj3ou l table
          ui->tableView_Resultat->setStyleSheet(originalStylesheet);// revenir à l'apparence visuelle initiale de la table.
          ui->tableView_Resultat->resize(originalSize);//dimensions d'origine après le processus d'impression.


          painter.end();
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

       // Affichage de "Enter password" sur l'afficheur LCD
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
