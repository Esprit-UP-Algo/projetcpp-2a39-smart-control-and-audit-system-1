#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QString>
#include <QSqlQuery>
#include <QDate>


class Historique {
public:
    Historique();

    // Méthodes pour gérer la table "historique"
    bool ajouter_historique();
    // Vous pouvez ajouter d'autres méthodes selon vos besoins.

private:
    int id;
    QString nom;
    QString adresse;
    int nb_etudiants;
    QDate date_visite;
    double budget_annuel;
};

#endif // HISTORIQUE_H
