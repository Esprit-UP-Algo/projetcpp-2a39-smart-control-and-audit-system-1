#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "universite.h"
#include <QPainter>
#include<QtGui>
#include <QVariant>
#include <QMainWindow>

#include "smtp.h"
#include"arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_pb_ajouter_clicked();

    void on_pb_annuler_ajout_clicked();

    void on_pb_modif_clicked();

    void on_pb_annuler_modif_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_annuler_supp_clicked();

    void on_le_recherche_textChanged(const QString &arg1);


    void on_cb_tri_currentIndexChanged(int index);

    void stats(QString,QString ,int,int,QString);

    void on_statsnbr_etudiants_clicked();

    void on_stats_budget_clicked();


    void on_sendMail_2_clicked();

  void mailsent_2(QString);


    void on_pushButton_clicked();

 void readfile();

    void on_pushButton_refresh_clicked();


  void on_tabWidget_currentChanged();


private:
    Ui::MainWindow *ui;

    //crud
    universite u;
    universite u1;
    universite u2;

    //Arduino
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire

};
#endif // MAINWINDOW_H
