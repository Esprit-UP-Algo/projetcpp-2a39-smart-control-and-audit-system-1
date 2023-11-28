#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "connection.h"
#include <QCoreApplication>
#include <QSslSocket>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Initialisation du support SSL
    QSslSocket::supportsSsl();

    MainWindow w;
    Connection c;
    bool test = c.ouvrirConnexion();
    if (test) {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\n"
                                             "Click Cancel."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}
