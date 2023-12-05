#ifndef INTERFACE_CERTEFICAT_H
#define INTERFACE_CERTEFICAT_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "certeficat.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QAbstractTableModel>
#include <QColor>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextEdit>
#include <QPainter>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include "arduino.h"



QT_BEGIN_NAMESPACE
namespace Ui { class interface_certeficat; }
QT_END_NAMESPACE

class interface_certeficat : public QMainWindow
{
    Q_OBJECT

public:
    interface_certeficat(QWidget *parent = nullptr);
    ~interface_certeficat();
    void on_rechercher_clicked();


private slots:
    void on_pushButton_ajouter_clicked();


    void on_pushButton_supp_clicked();

    void on_pushButton_Update_clicked();

    void on_pushButton_rechercher_clicked();

    void on_pushButton_retourner_clicked();

    void on_pushButton_trier_clicked();

    void on_tableView_main_interface_activated(const QModelIndex &index);

    void on_pushButton_scanne_clicked();

    void on_pushButton_exporter_clicked();
    void on_pushButton_imprimer_clicked();

private:
    void start_Camera();
    void stop_Camera();
private:

    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire



private:
    Ui::interface_certeficat *ui;
    Certificat Etmp;
    QTextEdit *texte;
    QScopedPointer<QCamera> M_Camera;
     QScopedPointer<QCameraImageCapture> M_Camera_Image;
     int counter=0;
     QImage ImageFromCamera;
private:

     struct NoteEntry
         {
             QDate date;
             QString note;
         };

         QVector<NoteEntry> notes; // Liste des notes


private slots:
    void  print(QPrinter *printer);
    void on_pushButton_mail_clicked();
    void on_pushButton_ajouter_2_clicked();

    void on_tableView_main_interface2_activated(const QModelIndex &index);
    void on_pushButton_calendrier_clicked();

    void on_pushButton_clicked();
    void on_pushButton_start_cam_clicked();
    void on_pushButton_stop_cam_clicked();
    void imageCaptured(int reqid, const QImage &img);
    void on_pushButton_cap_clicked();
    void on_pushButton_Update_2_clicked();
    void on_pushButton_camera_clicked();

void on_pushButton_statistique_clicked();
int calculerNombreCertificatsJanvier(int mois);
int on_pushButton_statistique_2_clicked();
void on_calendarWidget_clicked(const QDate &date);
void on_calendarWidget_selectionChanged();
void on_pushButton_enregistrer_clicked();
void on_pushButton_exp_stat_clicked();
void on_pushButton_retournouvelle_clicked();
void on_pushButton_retourcal2_clicked();
void on_pushButton_stat3_clicked();
void on_pushButton_retourcam4_clicked();
void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
void zidlas();

void on_pushButton_2_clicked();
void on_pushButton_3_clicked();
void on_pushButton_4_clicked();
QString  checkDataForCurrentDate();
void on_bagra_clicked();
void on_tabWidget_tabBarClicked(int index);
void on_tabWidget_currentChanged(int index);
void on_push_clicked();
void on_pushButton_imprimers_clicked();
void on_pushButton_COFFRE_clicked();
void on_pushButton_QR_clicked();
};


#endif // INTERFACE_CERTEFICAT_H
