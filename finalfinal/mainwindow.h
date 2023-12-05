#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMainWindow>
#include "rapport.h"
#include "arduino.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts>
#include "popup.h"
#include "formateur.h"
#include "qrcodegen.h"
#include "employe.h"
#include "smtp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
void occ();
QChartView *chartView ;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_8_clicked();

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_pushButton_9_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_10_clicked();
    void on_pushButton_ajouter_clicked();
    void on_supprimer_clicked();
    void on_comboBox_modifier_currentIndexChanged(const QString &arg1);
    void on_comboBox_supprimer_currentIndexChanged(const QString &arg1);
    void on_modifier_clicked();
    void on_rechercher_bouton_clicked();
    void on_reset_clicked() ;
    void on_trier_clicked();
    void on_PDF_clicked();
    void on_consulter_clicked();
    void on_pushButton_N_clicked();
void rfid();
void   sendMail();
void on_pushButton_conn_clicked();
void on_pushButton_ajoutemp_2_clicked();

void on_pushButton_suppemp_2_clicked();

void on_pushButton_modemp_2_clicked();

void on_tableView_3_clicked(const QModelIndex &index);
void on_lineEdit_rechidemp_2_textChanged(const QString &arg1);

void on_pushButton_impemp_2_clicked();

void on_comboBox_3_currentTextChanged(const QString &arg1);

void statistiques();


void on_mdp_clicked();

void on_back_clicked();
private:
    QString ref;
    QByteArray data; // variable contenant les données reçues
    PopUp *popUp;
       formation Etmp , f;
           Arduino A;
        Ui::MainWindow *ui;
        employe empmp;

int x;
};
#endif // MAINWINDOW_H
