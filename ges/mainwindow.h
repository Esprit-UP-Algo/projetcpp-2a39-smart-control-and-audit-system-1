#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "universite.h"
#include <QPainter>
#include<QtGui>
#include <QVariant>
#include <QMainWindow>

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




private:
    Ui::MainWindow *ui;

    //crud
    universite u;
    universite u1;
    universite u2;
};
#endif // MAINWINDOW_H
