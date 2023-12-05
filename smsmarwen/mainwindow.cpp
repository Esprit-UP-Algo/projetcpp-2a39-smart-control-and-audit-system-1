#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <cstdlib>
#include <ctime>
#include <QDebug>
#include <QTextStream>
#include <QTextDocument>
#include <QDesktopWidget>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
using namespace std;
#include <vector>
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
QString test11="";
QString test12="";
int index1=0,conn1=0;
#include <QtCharts>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setChecked(false);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_3->setChecked(false);
  ui->lineEdit->setValidator(new QIntValidator (0,99999999,ui->lineEdit));
  ui->lineEdit_2->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));
  ui->lineEdit_3->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));
  ui->lineEdit_4->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));
  ui->lineEdit_5->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));
  ui->lineEdit_6->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));

    ui->pushButton_4->setChecked(false);
    ui->pushButton_5->setChecked(false);
ui->frame->hide();
ui->frame_2->hide();
Rapport Rap;
Rap.afficher(ui);

 ui->frame_3->hide();

srand(static_cast<unsigned int>(time(0)));
   x = rand() % 10 + 1;
QString imagePath = ":/new/prefix1/res/"+QString::number(x)+".jpg";
QPixmap pixmap(imagePath);
ui->label_8->setPixmap(pixmap);
ui->label_9->setText(QString::number(x));
int ret=A.connect_arduino(); // lancer la connexion à arduino
            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }
             QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(rfid()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{occ();

    Rapport Rap;
    Rap.afficher(ui);
    ui->pushButton->setChecked(true);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_3->setChecked(false);

    ui->pushButton_4->setChecked(false);
    ui->pushButton_5->setChecked(false);
    ui->frame->show();
    ui->frame_2->show();
    ui->frame_3->show();


}

void MainWindow::on_pushButton_2_clicked()
{
    Rapport Rap;
    Rap.afficher(ui);
    ui->pushButton->setChecked(false);
    ui->pushButton_2->setChecked(true);
    ui->pushButton_3->setChecked(false);
    ui->frame->hide();
    ui->frame_2->hide();
    ui->pushButton_4->setChecked(false);
    ui->pushButton_5->setChecked(false);

    ui->frame_3->hide();
    A.write_to_arduino("you are now in menu 2");

}

void MainWindow::on_pushButton_3_clicked()
{
    Rapport Rap;
    Rap.afficher(ui);
    ui->pushButton->setChecked(false);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_3->setChecked(true);
    ui->frame->hide();
    ui->frame_2->hide();
     ui->frame_3->hide();
    ui->pushButton_4->setChecked(false);
    ui->pushButton_5->setChecked(false);
}

void MainWindow::on_pushButton_4_clicked()
{
    Rapport Rap;
    Rap.afficher(ui);
    ui->pushButton->setChecked(false);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_3->setChecked(false);
    ui->frame->hide();
    ui->frame_2->hide();
     ui->frame_3->hide();
    ui->pushButton_4->setChecked(true);
    ui->pushButton_5->setChecked(false);
}

void MainWindow::on_pushButton_5_clicked()
{
    Rapport Rap;
    Rap.afficher(ui);
    ui->pushButton->setChecked(false);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_3->setChecked(false);
    ui->frame->hide();
    ui->frame_2->hide();
     ui->frame_3->hide();
    ui->pushButton_4->setChecked(false);
    ui->pushButton_5->setChecked(true);
}

void MainWindow::on_pushButton_7_clicked()
{
    int id=ui->lineEdit->text().toInt();
   QDate datee=ui->dateTimeEdit->date();
    QString nom=ui->lineEdit_2->text();
    QString rapport=ui->lineEdit_3->text();
    QString idemployee=ui->lineEdit_4->text();
     QString iduni=ui->lineEdit_6->text();
     QString recap=ui->lineEdit_7->text();

    Rapport Rap(id,nom,rapport,datee,idemployee,iduni);
    qDebug() << "x: " << x << ", recap: " << recap;
if (id==NULL || nom=="" || rapport=="" || idemployee=="" || iduni==""){
    ui->label_10->setText("il ya un champ vide");}
else{
    ui->label_10->setText("");
    if ((recap == "1234" && x == 1) || (recap == "12345" && x == 2) || (recap == "123456" && x == 3) || (recap == "1234567" && x == 4) || (recap == "12345678" && x == 5) || (recap == "123456789" && x == 6) || (recap == "1234567891" && x == 7) || (recap == "12345678912" && x == 8) || (recap == "123456789123" && x == 9) || (recap == "1234567891234" && x == 10)) {
        // Your code here

    bool test=Rap.ajouter();
    if (test)
    {
        Rap.afficher(ui);

    }
    recap="";
    }
else{

}}
occ();
}

void MainWindow::on_pushButton_6_clicked()
{
    int id=ui->lineEdit->text().toInt();
   QDate datee=ui->dateTimeEdit->date();
    QString nom=ui->lineEdit_2->text();
    QString rapport=ui->lineEdit_3->text();
    QString idemployee=ui->lineEdit_4->text();
     QString iduni=ui->lineEdit_6->text();
    Rapport Rap(id,nom,rapport,datee,idemployee,iduni);
    bool test=Rap.modifier();
if(test){
Rap.afficher(ui);

}
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int i;
i=index.row();
QModelIndex in=index.sibling(i,0);
QString val=ui->tableView->model()->data(in).toString();


    QSqlQuery qry;
    qry.prepare("select id,nom,rapport,datee,IDEMPLOYEE,iduni from rapport where id='"+val+"' " );


    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit->setText(qry.value(0).toString());
            ui->lineEdit_4->setText(qry.value(4).toString());
            ui->lineEdit_6->setText(qry.value(5).toString());

            ui->lineEdit_2->setText(qry.value(1).toString());
            ui->lineEdit_3->setText(qry.value(2).toString());
            ui->dateTimeEdit->setDate(qry.value(3).toDate());


        }
}
    occ();
}

void MainWindow::on_pushButton_8_clicked()
{
    QModelIndex index=ui->tableView->currentIndex();
        int i=index.row();
        QModelIndex in=index.sibling(i,0);
        QString val=ui->tableView->model()->data(in).toString();
        Rapport Rap;
        bool test=Rap.supprimer(val);
        if (test)
        {

            Rap.afficher(ui);

        }
        occ();
}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString text=ui->lineEdit_5->text();

    if(text.isEmpty())
    {
         Rapport Rap;
        Rap.afficher(ui);

    }
    else
    {
        qry->prepare("select * from rapport where ( id LIKE'%"+text+"%' OR nom LIKE'%"+text+"%' OR rapport LIKE'%"+text+"%') ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("col1")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

        document->print(&printer);


    delete document;
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString type=ui->comboBox->currentText();
    if (type=="Par defaut"){
        qry->prepare("select id,nom,rapport,datee,IDEMPLOYEE,iduni from rapport");
        qry->exec();
        modal->setQuery(*qry);
        modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        modal->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        modal->setHeaderData(2,Qt::Horizontal,QObject::tr("rapport"));
         modal->setHeaderData(3,Qt::Horizontal,QObject::tr("datee"));
           modal->setHeaderData(4,Qt::Horizontal,QObject::tr("idemployee"));
          modal->setHeaderData(5,Qt::Horizontal,QObject::tr("iduni"));
        ui->tableView->setModel(modal);}
        else if (type=="id"){
            qry->prepare("select id,nom,rapport,datee,IDEMPLOYEE,iduni from rapport order by id");
            qry->exec();
            modal->setQuery(*qry);
            modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            modal->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            modal->setHeaderData(2,Qt::Horizontal,QObject::tr("rapport"));
             modal->setHeaderData(3,Qt::Horizontal,QObject::tr("datee"));
               modal->setHeaderData(4,Qt::Horizontal,QObject::tr("idemployee"));
              modal->setHeaderData(5,Qt::Horizontal,QObject::tr("iduni"));

            ui->tableView->setModel(modal);


        }
        else if (type=="nom"){
            qry->prepare("select id,nom,rapport,datee,IDEMPLOYEE,iduni from rapport order by nom");
            qry->exec();
            modal->setQuery(*qry);
            modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            modal->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            modal->setHeaderData(2,Qt::Horizontal,QObject::tr("rapport"));
             modal->setHeaderData(3,Qt::Horizontal,QObject::tr("datee"));
               modal->setHeaderData(4,Qt::Horizontal,QObject::tr("idemployee"));
              modal->setHeaderData(5,Qt::Horizontal,QObject::tr("iduni"));

            ui->tableView->setModel(modal);


        }

}

void MainWindow::on_pushButton_10_clicked()
{
    QString text,space="";
    QString msg=ui->input->text();
    ui->output->appendPlainText(space);
    ui->output->appendPlainText(msg);
    QSqlQuery qry,query;
     if     (msg[0]!="$")   {
    qry.prepare("select * from chatbot where word='"+msg+"' " );
     if(qry.exec())
     {
         if(qry.next()==false){
             ui->output->appendPlainText( "do you wanna add new word? write my answer with $ in first");
ui->label_16->setText(msg);}
         else

           ui->output->appendPlainText( "\n"+qry.value(1).toString());




     }}
    else if (msg[0]=="$"){
         QString msg1=msg.mid(1,msg.length()-1);
         query.prepare("insert into chatbot (WORD,REP)""values(:WORD,:REP)");
         query.bindValue(":WORD", ui->label_16->text());
         query.bindValue(":REP", msg1);
         query.exec();
         ui->output->appendPlainText( "\n New word for me");

     }
}
void MainWindow::occ(){

    vector<statt> v1,v11,v2,v3,v4;
    QSqlQuery qry,qry1,qry2,qry3;
statt s0,s1,s2,s3;

    qry.prepare("select id,nom from rapport" );


    qry.exec();

        while(qry.next())
        {
            s0.id=qry.value(0).toString();
            s0.nom=qry.value(1).toString();
            v1.push_back(s0);
        }
        int occ0=0,occ01=0,occ02=0,occ03=0,occ1=0,occ2=0,occ3=0,occ4=0;
        QString nomocc="",nomocc1="",nomocc2="",nomocc3="",id="",id1="",id2="",id3="";
for( int i=0;i<v1.size();i++){
    occ0=0;
    for( int j=0;j<v1.size();j++){
        if (v1[i].nom==v1[j].nom)
            occ0++;
    }
    if(occ0>occ1){
        occ1=occ0;
    nomocc=v1[i].nom;
    id=v1[i].id;}
}
qry1.prepare("select id,nom from rapport where nom!='"+nomocc+"'" );


qry1.exec();

    while(qry1.next())
    {
        s1.id=qry1.value(0).toInt();
        s1.nom=qry1.value(1).toString();
        v2.push_back(s1);
    }
    for( int i=0;i<v2.size();i++){
        occ01=0;

        for( int j=0;j<v2.size();j++){
            if (v2[i].nom==v2[j].nom)
                occ01++;
        }
        if(occ01>occ2){
            occ2=occ01;
        nomocc1=v2[i].nom;
        id1=v2[i].id;}
    }
    qry2.prepare("select id,nom from rapport where nom!='"+nomocc+"' and nom!='"+nomocc1+"' " );


    qry2.exec();

        while(qry2.next())
        {
            s2.id=qry2.value(0).toInt();
            s2.nom=qry2.value(1).toString();

            v3.push_back(s2);
        }
        for(unsigned int i=0;i<v3.size();i++){
            occ02=0;

            for(unsigned int j=0;j<v3.size();j++){
                if (v3[i].nom==v3[j].nom)
                    occ02++;
            }
            if(occ02>occ3){
                occ3=occ02;
            nomocc2=v3[i].nom;
            id2=v3[i].id;}
        }
        qry3.prepare("select id,nom from rapport where nom!='"+nomocc+"' and nom!='"+nomocc1+"' and nom!='"+nomocc2+"'" );


        qry3.exec();

            while(qry3.next())
            {
                s3.id=qry3.value(0).toInt();
                s3.nom=qry3.value(1).toString();

                v4.push_back(s3);
            }
            for(unsigned int i=0;i<v4.size();i++){
                occ03=0;

                for(unsigned int j=0;j<v4.size();j++){
                    if (v4[i].nom==v4[j].nom)
                        occ03++;
                }
                if(occ03>occ4){
                    occ4=occ03;
                nomocc3=v4[i].nom;
                id3=v4[i].id;}
            }

            QBarSet *set0 = new QBarSet("Jan");
            *set0 << occ1<< occ2<< occ3<< occ4;
          QBarSeries *series = new QBarSeries();
            series->append(set0);
           QChart *chart = new QChart();
            chart->addSeries(series);
    chart->setTitle("Les titres les plus populaires");
    QStringList cataloge;
    cataloge<<nomocc<<nomocc1<<nomocc2<<nomocc3;
    chart->setAnimationOptions(QChart::AllAnimations);
     QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,10);
    chart->setAxisY(axisY,series);
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(cataloge);
    chart->createDefaultAxes();
    chart->legend()->hide();

    chart->setAxisX(axisX,series);
            QPalette pal = qApp->palette();
            pal.setColor(QPalette::Window, QRgb(0xffffff));
           pal.setColor(QPalette::WindowText, QRgb(0x404044));
           qApp->setPalette(pal);
    chartView = new QChartView(chart,ui->chartview);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(561,331);

    chartView->show();

}
void MainWindow::rfid(){
    data=A.read_from_arduino();

   test11=data;
   test12=test11.left(test11.length()-2);
   qDebug()<<test12;
   if(test12[0]=="m"){
       qDebug()<<"menu vrai"<<endl;
   if(test12[1]=="1") {
       if(ui->pushButton->isChecked()==false)
       on_pushButton_clicked();
       qDebug()<<"page vrai"<<endl;
       if (test12[2]=="1")
           index1=1;
        if (test12[2]=="2")
           index1=2;
        if (test12[2]=="3")
            index1=3;
         if (test12[2]=="4")
            index1=4;
         if (test12[2]=="5")
             index1=5;
          if (test12[2]=="6")
             index1=6;
          if (test12[2]=="7")
             index1=7;
          if (test12[2]=="8")
             index1=8;
          if (test12[2]=="9")
             index1=9;
          if(index1==9 ){
              ui->rechh->setText(test12.right(test12.length()-3));
              index1=0;
              A.write_to_arduino("valeur id effectuée");


          }
          if(index1==8 ){
              qDebug()<<"col vrai"<<endl;

            ui->input->setText(test12.right(test12.length()-3));
            index1=0;
            A.write_to_arduino("valeur chat bot effectuée");



          }
           if(index1==1 ){
               qDebug()<<"col vrai"<<endl;

             ui->lineEdit->setText(test12.right(test12.length()-3));
             index1=0;
             A.write_to_arduino("valeur id effectuée");
           }
                 if (index1==2){
                              ui->lineEdit_2->setText(test12.right(test12.length()-3));
                               A.write_to_arduino("valeur nom effectuée");
                 index1=0;}
                 if(index1==3 ){
                   ui->lineEdit_3->setText(test12.right(test12.length()-3));
                   index1=0;
                   A.write_to_arduino("valeur rapport effectuée");
                 }
                 if(index1==4 ){

                    ui->dateTimeEdit->setDateTime(QDateTime::fromString(test12.right(test12.length()-1)));
                    A.write_to_arduino("valeur date effectuée");

                   index1=0;
                 }
                 if(index1==5 ){
                   ui->lineEdit_4->setText(test12.right(test12.length()-3));
                   index1=0;
                   A.write_to_arduino("valeur id employee effectuée");

                 }
                 if(index1==6 ){
                   ui->lineEdit_6->setText(test12.right(test12.length()-3));
                   index1=0;
                   A.write_to_arduino("valeur id uni effectuée");

                 }
                 if(index1==7 ){
                   ui->lineEdit_7->setText(test12.right(test12.length()-3));
                   index1=0;
                   A.write_to_arduino("valeur recapacha effectuée");

                 }
                  if (test12[2]=="r"&&conn1==0){
                 qDebug()<<"col vrai"<<endl;
                 QSqlQuery*qry=new QSqlQuery();
                 QString text=test12.right(test12.length()-3);





                     qry->prepare("select * from rapport where ( id LIKE'%"+text+"%' OR nom LIKE'%"+text+"%' OR rapport LIKE'%"+text+"%') ");
                     qry->exec();
                     while(qry->next()){
                         A.write_to_arduino("id="+qry->value(0).toString()+"nom="+qry->value(1).toString()+"rapport="+qry->value(2).toString()+"date="+qry->value(3).toString()+"id emply="+qry->value(4).toString()+"id uni="+qry->value(5).toString());
                         QThread::msleep(2000);

                     }
                     ui->rechh->clear();
                                          conn1=1;}

                 if (test12[2]=="b"&&conn1==0){

                     QString text,space="";
                     QString msg=ui->input->text();

                     if(msg!=""){
                         ui->output->appendPlainText(space);
                         ui->output->appendPlainText(msg);
                         QSqlQuery qry,query;
                      if     (msg[0]!="$")   {
                     qry.prepare("select * from chatbot where word='"+msg+"' " );
                      if(qry.exec())
                      {
                          if(qry.next()==false){
 QThread::msleep(2000);
 A.write_to_arduino("do you wanna add new word? write my answer with $ in first");

                              ui->output->appendPlainText( "do you wanna add new word? write my answer with $ in first");

                 ui->label_16->setText(msg);}
                          else{
                               QThread::msleep(2000);
A.write_to_arduino(qry.value(1).toString());
                            ui->output->appendPlainText( "\n"+qry.value(1).toString());
                  }



                      }}
                     else if (msg[0]=="$"){
                          QString msg1=msg.mid(1,msg.length()-1);
                          query.prepare("insert into chatbot (WORD,REP)""values(:WORD,:REP)");
                          query.bindValue(":WORD", ui->label_16->text());
                          query.bindValue(":REP", msg1);
                          query.exec();
                          QThread::msleep(2000);

                          ui->output->appendPlainText( "\n New word for me");
                          A.write_to_arduino("\n New word for me");

                      }}

ui->input->clear();
                     conn1=1;}
                 if (test12[2]=="a"&&conn1==0){

                     int id=ui->lineEdit->text().toInt();
                    QDate datee=ui->dateTimeEdit->date();
                     QString nom=ui->lineEdit_2->text();
                     QString rapport=ui->lineEdit_3->text();
                     QString idemployee=ui->lineEdit_4->text();
                      QString iduni=ui->lineEdit_6->text();
                      QString recap=ui->lineEdit_7->text();

                     Rapport Rap(id,nom,rapport,datee,idemployee,iduni);
                     qDebug() << "x: " << x << ", recap: " << recap;
                 if (id==NULL || nom=="" || rapport=="" || idemployee=="" || iduni==""){
                     ui->label_10->setText("il ya un champ vide");}
                 else{
                     ui->label_10->setText("");
                         // Your code here

                     bool test=Rap.ajouter();
                     if (test)
                     {
                         Rap.afficher(ui);
                         A.write_to_arduino("ajout  effectuée : id "+QString::number(id));

                     }
                     recap="";
                     }

                 occ();
                  ui->lineEdit->clear();
                ui->dateTimeEdit->clear();
                  ui->lineEdit_2->clear();
                  ui->lineEdit_3->clear();
                  ui->lineEdit_4->clear();
                  ui->lineEdit_6->clear();
                ui->lineEdit_7->clear();


                     conn1=1;}
                 if (test12[2]=="m"&&conn1==0){

                     int id=ui->lineEdit->text().toInt();
                    QDate datee=ui->dateTimeEdit->date();
                     QString nom=ui->lineEdit_2->text();
                     QString rapport=ui->lineEdit_3->text();
                     QString idemployee=ui->lineEdit_4->text();
                      QString iduni=ui->lineEdit_6->text();
                     Rapport Rap(id,nom,rapport,datee,idemployee,iduni);
                     bool test=Rap.modifier();
                 if(test){
                 Rap.afficher(ui);
                 A.write_to_arduino("modification  effectuée : id "+QString::number(id));

                 }
                 else
                       A.write_to_arduino("modification non effectuée : id "+QString::number(id));
                     conn1=1;
                     ui->lineEdit->clear();
                   ui->dateTimeEdit->clear();
                     ui->lineEdit_2->clear();
                     ui->lineEdit_3->clear();
                     ui->lineEdit_4->clear();
                     ui->lineEdit_6->clear();
                   ui->lineEdit_7->clear();
                 }
                 //new
                 if (test12[2]=="s"&&conn1==0){

if( ui->lineEdit->text()!=""){
    Rapport rap;
    bool test=rap.supprimer(ui->lineEdit->text());
    if (test)
    {
        occ();
        A.write_to_arduino("supprission  effectuée : id "+ui->lineEdit->text());

        rap.afficher(ui);

    }
    else {
        A.write_to_arduino("supprission non effectuée : id "+ui->lineEdit->text());

    }
}
ui->lineEdit->clear();
ui->dateTimeEdit->clear();
ui->lineEdit_2->clear();
ui->lineEdit_3->clear();
ui->lineEdit_4->clear();
ui->lineEdit_6->clear();
ui->lineEdit_7->clear();

    conn1=1;}

                 //new



   }
   if(test12[1]=="2") {
       if(ui->pushButton_2->isChecked()==false)
       on_pushButton_2_clicked();
       A.write_to_arduino("you are now in menu 2");


                     conn1=1;}

   }

       if(test12[1]=="3"){
           if(ui->pushButton_3->isChecked()==false)
           on_pushButton_3_clicked();
           A.write_to_arduino("you are now in menu 3");


                    conn1=1;}


   if(test12[1]=="4"){
       if(ui->pushButton_4->isChecked()==false)
       on_pushButton_4_clicked();
       A.write_to_arduino("you are now in menu 4");

                conn1=1;

   }
   if(test12[1]=="5") {
       if(ui->pushButton_5->isChecked()==false)
       on_pushButton_5_clicked();
       A.write_to_arduino("you are now in menu 5");


                conn1=1;




   }
   if(test12[0]=="p") {
       if(ui->pushButton->isChecked()==true )
       A.write_to_arduino("you are now in menu 1");
       else if (ui->pushButton_2->isChecked()==true )
           A.write_to_arduino("you are now in menu 2");
       else if (ui->pushButton_3->isChecked()==true )
           A.write_to_arduino("you are now in menu 3");
       else if (ui->pushButton_4->isChecked()==true )
           A.write_to_arduino("you are now in menu 4");
       else if (ui->pushButton_5->isChecked()==true )
           A.write_to_arduino("you are now in menu 5");


                conn1=1;




   }
   conn1=0;}
