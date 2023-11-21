#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include<QDebug>
#include "connection.h"
#include<QMessageBox>
#include <iostream>

#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include<QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QTextDocument>

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>


#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QTextOption>
#include <QFont>
#include <QString>
#include <QSqlQuery>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include "qrcodegen.h"
#include<formateur.h>
#include "popup.h"

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

private slots :
    void on_pushButton_ajouter_clicked();
    void on_supprimer_clicked();
    void on_comboBox_modifier_currentIndexChanged(const QString &arg1);
    void on_comboBox_supprimer_currentIndexChanged(const QString &arg1);
    void on_modifier_clicked();
    void on_pushButton_ajouter_4_clicked();
    void on_rechercher_bouton_clicked();
    void on_reset_clicked() ;
    void on_trier_clicked();
    void on_PDF_clicked();
    void on_consulter_clicked();
    void on_pushButton_N_clicked();


private:
    Ui::MainWindow *ui;
 PopUp *popUp;
    formation Etmp , f;
};



#endif // MAINWINDOW_H
