#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figura.cpp"

//#include "CImg.h"
#include <QFileDialog>
#include <QtGui>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include <iostream>

using namespace std;

QString fileName = "";
QString fileName1 = "";
QString ruta1 = "";
QString ruta_1 = "";
QString ruta_2 = "";
QString fileName2 = "";
QString ruta2 = "";
QString fileName1_aux = "";
QString fileName2_aux = "";
QVector<int> x_1;
QVector<int> y_1;
QVector<int> x_2;
QVector<int> y_2;
QString s1;
QString s2;
Figura *fig1;
Figura *fig2;


MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->actionEixir, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->b_carrega1, SIGNAL(clicked()), this, SLOT(Carrega1()));
    connect(ui->b_carrega2, SIGNAL(clicked()), this, SLOT(Carrega2()));
    connect(ui->juxta, SIGNAL(clicked()), this, SLOT(Reconeix()));
  
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::Carrega1() {

    QObject *parent;
    ruta1 = QFileDialog::getOpenFileName(0, QString(), QString(),
            tr("Images (*.png *.xpm *.jpg *.jpeg)"));

    QFileInfo fitx(ruta1);
    ruta_1=fitx.fileName();
    QString fileName1 = fitx.fileName();
    QImage image;
    QString program = "./recformas/RecFormas";
    QStringList arguments;
    arguments << "-o" << ruta1;
    QProcess *myProcess = new QProcess(parent);
    myProcess->start(program, arguments);



    myProcess->waitForFinished();
    QByteArray result = myProcess->readAllStandardOutput();
    
    s1 = result.data();
    int n_ver;

    QFile myFile("registros.dat");
    QDataStream in(&myFile);
    in >> n_ver;

    if (!myFile.open(QIODevice::ReadOnly)) // Open the file
    {
        // handle error
    }
    
    n_ver += 3;
    for (int aux = 1; aux < n_ver; aux++) {
        int x_aux, y_aux;
        in >> x_aux;
        in >> y_aux;
        x_1.push_back(x_aux);
        y_1.push_back(y_aux);
    }
    ui->des1->setText(s1);
    ruta1 = fitx.path();
    QObject *parent2;
    QString program2;
    program2 = "./codi/dibuixa";



    QStringList arguments2;
    arguments2 << ruta1 << fileName1 << "1";
    QProcess *myProcess2 = new QProcess(parent2);
    myProcess2->start(program2, arguments2);
    myProcess2->waitForFinished();
    QByteArray result2 = myProcess2->readAllStandardOutput();
    QImage image2;
    fileName1_aux = ruta1 + "/fin_" + fileName1;
    image2.load(fileName1_aux);
    ui->imageLabel->setPixmap(QPixmap::fromImage(image2));
    // ui->scrollArea = new QScrollArea;
    ui->imageLabel->setScaledContents(true);

}

void MainWindow::Carrega2() {

 
  
    QObject *parent;
    ruta2 = QFileDialog::getOpenFileName(0, QString(), QString(),
            tr("Images (*.png *.xpm *.jpg *.jpeg)"));
    QFileInfo fitx(ruta2);
    ruta_2=fitx.fileName();
    QString fileName2 = fitx.fileName();
    QImage image;
    QString program = "./recformas/RecFormas";
    QStringList arguments;


     arguments << "-o" << ruta2;
    //  arguments << "-C" << "cuadrat.jpg";
  
    QProcess *myProcess = new QProcess(parent);
    myProcess->start(program, arguments);
    sleep(2);

    myProcess->waitForFinished();
    QByteArray result = myProcess->readAllStandardOutput();
    s2 = result.data();
    int n_ver;

    QFile myFile("registros.dat");
    QDataStream in(&myFile);
    in >> n_ver;

    if (!myFile.open(QIODevice::ReadOnly)) // Open the file
    {
        // handle error
    }
    ui->des2->setText(s2);
    ruta2 = fitx.path();
    QObject *parent2;
    QString program2;
    program2 = "./codi/dibuixa";
    QStringList arguments2;
    arguments2 << ruta2 << fileName2 << "2";
    QProcess *myProcess2 = new QProcess(parent2);
    myProcess2->start(program2, arguments2);
    myProcess2->waitForFinished();
    QByteArray result2 = myProcess2->readAllStandardOutput();
    QImage image2;
    fileName2_aux = ruta2 + "/fin_" + fileName2;
    image2.load(fileName2_aux);
    ui->imageLabel_2->setPixmap(QPixmap::fromImage(image2));
    ui->imageLabel_2->setScaledContents(true);
}

void MainWindow::Reconeix() {

    



    QObject *parent3;
   
    QString program3 = "./recformas/RecFormas2";
    QStringList arguments3;


    // arguments << "-o" << ruta2;
    arguments3 << "-C" << ruta_1;
  
    QProcess *myProcess3 = new QProcess(parent3);
    myProcess3->start(program3, arguments3);
    sleep(1);
    system("killall -9 RecFormas2");
    myProcess3->waitForFinished();
    QByteArray result3 = myProcess3->readAllStandardOutput();
    s2 = result3.data();
    std::string descrip1 = s2.toUtf8().constData();


   
 
    
       QObject *parent4;
   
    QString program4 = "./recformas/RecFormas2";
    QStringList arguments4;


    // arguments << "-o" << ruta2;
    arguments4 << "-C" << ruta_2;
  
    QProcess *myProcess4 = new QProcess(parent4);
    myProcess4->start(program4, arguments4);
    sleep(1);
    system("killall -9 RecFormas2");
    myProcess4->waitForFinished();
    QByteArray result4 = myProcess4->readAllStandardOutput();
    s1 = result4.data();
    std::string descrip2 = s1.toUtf8().constData();

    fig1=LeerFigura2(descrip1);
    fig1->PonerEnElEjeParaRestar();
    
  
    //char *Nombre_figura2 = "quad.jpg";
    fig2=LeerFigura2(descrip2);
    //fig2->mostrar();
    fig2->PonerEnElEjeParaRestar();
    






    Figura *fig3;
    fig3 = Restar(fig1,fig2);
    
    string res="";
    res=fig3->visualizar();
    QString result((char *)res.c_str());
    ui->des3->setText(result);
    fig3->escribe();
    
    QObject *parent;
    QObject *parent2;
    QString program = "./codi/dibuixa_resul";
    QStringList arguments;
    QStringList arguments2;
    QProcess *myProcess = new QProcess(parent);
    myProcess->start(program, arguments);
    myProcess->waitForFinished();
    QImage image;
    QString fm = "resultat.png";
    image.load(fm);
    ui->imageLabel_4->setPixmap(QPixmap::fromImage(image));
    ui->imageLabel_4->setScaledContents(true);
}

void MainWindow::changeEvent(QEvent *e) {
    QMainWindow::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange :
                    ui->retranslateUi(this);
            break;
        default:
            break;
    }
}
