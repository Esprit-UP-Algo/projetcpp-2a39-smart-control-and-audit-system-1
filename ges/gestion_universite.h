#ifndef GESTION_UNIVERSITE_H
#define GESTION_UNIVERSITE_H
#include <QDialog>
#include "universite.h"
#include <QPainter>
#include <QtGui>


namespace Ui {
class gestion_universite;
}

class gestion_universite : public QDialog
{
    Q_OBJECT

public:
    explicit gestion_universite(QWidget *parent = nullptr);
    ~gestion_universite();

private slots:
    //crud
    void on_pb_ajouter_clicked();
    void on_pb_annuler_ajout_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_annuler_supp_clicked();
    void on_pb_modif_clicked();
    void on_pb_annuler_modif_clicked();





private:
    Ui::gestion_universite *ui;
    //crud
    universite u;
    universite u1;
    universite u2;


};










#endif // GESTION_UNIVERSITE_H
