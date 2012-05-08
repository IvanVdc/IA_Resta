#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "CImg.h"
#include <QFileDialog>
#include <QtGui>
#include <sstream>
#include <fstream>

#include <iostream>




QString fileName = "";
QString fileName1 = "";
QString ruta1 = "";
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

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow) {
    ui->setupUi(this);



    connect(ui->actionEixir, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->b_carrega1, SIGNAL(clicked()), this, SLOT(Carrega1()));
    connect(ui->b_carrega2, SIGNAL(clicked()), this, SLOT(Carrega2()));
    connect(ui->juxta, SIGNAL(clicked()), this, SLOT(Reconeix()));
    // this->connect(ui->actionEixir, SIGNAL(clicked()), this, SLOT(close()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::Carrega1() {

    QObject *parent;


    /* QString path( QFileDialog::getOpenFileName(0, QString(), QString(),
                                     tr("Images (*.png *.xpm *.jpg *.jpeg)")));
     if (!path.isNull()) {
         QFileInfo pathInfo( path );
         QString fileName1(pathInfo.fileName());

     }*/

    ruta1 = QFileDialog::getOpenFileName(0, QString(), QString(),
            tr("Images (*.png *.xpm *.jpg *.jpeg)"));




    /*if (!fileName.isNull()) {
       QFileInfo pathInfo( fileName );
       QString fileName1(pathInfo.fileName());

   }*/

    QFileInfo fitx(ruta1);

    QString fileName1 = fitx.fileName();



    /* fileName1 = QFileDialog::getOpenFileName(0, QString(), QString(),
                                         tr("Images (*.png *.xpm *.jpg *.jpeg)"));*/
    QImage image;
    /*   if (!image.load(fileName1)) {
           ui->imageLabel->setText(tr("Carrega una nova \n imatge ..."));
           return;
       }

     */

    // ui->des1->setText(tr("[with-holes,with-curves,[[0,0,0],[right-angle,convex,smaller],[right-angle,convex,bigger],[right-angle,convex,smaller],[right-angle,convex,bigger]]"));

    //std::string toStdString ()
    //  RecSenyals a(fileName.toStdString());
    //a.RecSenyals1(fileName.toStdString());





    QString program = "./recformas/RecFormas";



    QStringList arguments;
    // std::string s= fileName.toStdString();
    arguments << "-o" << ruta1;


    //double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 37.56, -10000, 10000, 2, &ok);



    QProcess *myProcess = new QProcess(parent);
    myProcess->start(program, arguments);



    myProcess->waitForFinished();
    QByteArray result = myProcess->readAllStandardOutput();
    //result = result.simplified();
    s1 = result.data();
    //QStringList list;
    //list = str2.split("\n", QString::KeepEmptyParts);
    /*bool ok;
    int aux=1;
    std::string  aux_nv = list[0].toStdString();
    int n_ver= atoi(aux_nv.c_str());
    //int n_ver=list[0].toInt( &ok, 10 );
    //int n_ver= atoi(list[0].c_str());
     QString auxiliar="";
    auxiliar+="hol ";
    n_ver+=3;
    QString stra; stra.setNum(n_ver);
    auxiliar+=stra;*/
    int n_ver;

    QFile myFile("registros.dat");
    QDataStream in(&myFile);
    in >> n_ver;

    if (!myFile.open(QIODevice::ReadOnly)) // Open the file
    {
        // handle error
    }
    /* bool ok;
     QTextStream stream( &myFile ); // Set the stream to read from myFile
     line = stream.readLine();
     int n_ver=line.toInt(&ok, 10);
     */
    n_ver += 3;
    for (int aux = 1; aux < n_ver; aux++) {
        int x_aux, y_aux;
        in >> x_aux;
        in >> y_aux;
        x_1.push_back(x_aux);
        y_1.push_back(y_aux);



    }

    /*
    for (aux=1;aux<n_ver;aux++){
        QStringList list2;
        //atoi(strConvert.c_str()
        list2 = list[aux].split(",", QString::SkipEmptyParts);
        int x_aux=list2[0].toInt(&ok, 10);
        x_1.push_back(x_aux);
        auxiliar+=x_aux;
        auxiliar+=" ";
       int y_aux=list2[1].toInt(&ok, 10);
        y_1.push_back(y_aux);
        auxiliar+=y_aux;
        auxiliar+=" ";
    }*/
    //auxiliar+="lll";

    //aux++;

    //s1=list[aux];
    ui->des1->setText(s1);


    ruta1 = fitx.path();

    QObject *parent2;

    QString program2;
    program2 = "./codi/dibuixa";



    QStringList arguments2;

    // arguments3 << "/home/sergi/Escriptori/juxtaposicio/codi/triangle.png" << "3" << "1.2"<< "1.2"<< "2.2" <<"2.2"<< "3.3"<< "3.3";

    // std::string s= fileName.toStdString();
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


    /* QString path( QFileDialog::getOpenFileName(0, QString(), QString(),
                                     tr("Images (*.png *.xpm *.jpg *.jpeg)")));
     if (!path.isNull()) {
         QFileInfo pathInfo( path );
         QString fileName1(pathInfo.fileName());

     }*/

    ruta2 = QFileDialog::getOpenFileName(0, QString(), QString(),
            tr("Images (*.png *.xpm *.jpg *.jpeg)"));



    /*if (!fileName.isNull()) {
       QFileInfo pathInfo( fileName );
       QString fileName1(pathInfo.fileName());

   }*/

    QFileInfo fitx(ruta2);

    QString fileName2 = fitx.fileName();



    /* fileName1 = QFileDialog::getOpenFileName(0, QString(), QString(),
                                         tr("Images (*.png *.xpm *.jpg *.jpeg)"));*/
    QImage image;
    /*   if (!image.load(fileName1)) {
           ui->imageLabel->setText(tr("Carrega una nova \n imatge ..."));
           return;
       }

     */

    // ui->des1->setText(tr("[with-holes,with-curves,[[0,0,0],[right-angle,convex,smaller],[right-angle,convex,bigger],[right-angle,convex,smaller],[right-angle,convex,bigger]]"));

    //std::string toStdString ()
    //  RecSenyals a(fileName.toStdString());
    //a.RecSenyals1(fileName.toStdString());





    QString program = "./recformas/RecFormas";



    QStringList arguments;
    // std::string s= fileName.toStdString();
    arguments << "-o" << ruta2;


    //double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 37.56, -10000, 10000, 2, &ok);



    QProcess *myProcess = new QProcess(parent);
    myProcess->start(program, arguments);



    myProcess->waitForFinished();
    QByteArray result = myProcess->readAllStandardOutput();
    //result = result.simplified();
    s2 = result.data();
    //QStringList list;
    //list = str2.split("\n", QString::KeepEmptyParts);
    /*bool ok;
    int aux=1;
    std::string  aux_nv = list[0].toStdString();
    int n_ver= atoi(aux_nv.c_str());
    //int n_ver=list[0].toInt( &ok, 10 );
    //int n_ver= atoi(list[0].c_str());
     QString auxiliar="";
    auxiliar+="hol ";
    n_ver+=3;
    QString stra; stra.setNum(n_ver);
    auxiliar+=stra;*/
    int n_ver;

    QFile myFile("registros.dat");
    QDataStream in(&myFile);
    in >> n_ver;

    if (!myFile.open(QIODevice::ReadOnly)) // Open the file
    {
        // handle error
    }
    /* bool ok;
     QTextStream stream( &myFile ); // Set the stream to read from myFile
     line = stream.readLine();
     int n_ver=line.toInt(&ok, 10);
     */

    /*
    for (aux=1;aux<n_ver;aux++){
        QStringList list2;
        //atoi(strConvert.c_str()
        list2 = list[aux].split(",", QString::SkipEmptyParts);
        int x_aux=list2[0].toInt(&ok, 10);
        x_1.push_back(x_aux);
        auxiliar+=x_aux;
        auxiliar+=" ";
       int y_aux=list2[1].toInt(&ok, 10);
        y_1.push_back(y_aux);
        auxiliar+=y_aux;
        auxiliar+=" ";
    }*/
    //auxiliar+="lll";

    //aux++;

    //s1=list[aux];
    ui->des2->setText(s2);


    ruta2 = fitx.path();

    QObject *parent2;

    QString program2;
    program2 = "./codi/dibuixa";



    QStringList arguments2;

    // arguments3 << "/home/sergi/Escriptori/juxtaposicio/codi/triangle.png" << "3" << "1.2"<< "1.2"<< "2.2" <<"2.2"<< "3.3"<< "3.3";

    // std::string s= fileName.toStdString();
    arguments2 << ruta2 << fileName2 << "2";





    QProcess *myProcess2 = new QProcess(parent2);
    myProcess2->start(program2, arguments2);


    myProcess2->waitForFinished();
    QByteArray result2 = myProcess2->readAllStandardOutput();







    QImage image2;
    fileName2_aux = ruta2 + "/fin_" + fileName2;
    image2.load(fileName2_aux);
    ui->imageLabel_2->setPixmap(QPixmap::fromImage(image2));
    // ui->scrollArea = new QScrollArea;
    ui->imageLabel_2->setScaledContents(true);


















}

void MainWindow::Reconeix() {
    //ui->label_3->setText(tr("KKd"));


    QObject *parent;
    QObject *parent2;


    QString program = "./codi/dibuixa_resul";
    QStringList arguments;
    QStringList arguments2;
    //std::string s1= fileName1_aux.toStdString();
    // std::string s2= fileName2_aux.toStdString();

    QString num1 = ui->r1v1->text();
    int r1v1 = num1.toInt();
    QString num2 = ui->r1v2->text();
    int r1v2 = num2.toInt();
    QString num3 = ui->r2v1->text();
    int r2v1 = num3.toInt();
    QString num4 = ui->r2v2->text();
    int r2v2 = num4.toInt();

    if (r1v1 > 0 and r1v2 > 0 and r2v1 > 0 and r2v2 > 0) {

        // const char *s1_aux = s1.toAscii().data();
        // const char *s2_aux = s2.toAscii().data();



        //double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 37.56, -10000, 10000, 2, &ok);

        arguments << num1 << num2 << num3 << num4;

        QProcess *myProcess = new QProcess(parent);
        myProcess->start(program, arguments);


        myProcess->waitForFinished();


        QImage image;

        QString fm = "resultat.png";
        image.load(fm);
        ui->imageLabel_4->setPixmap(QPixmap::fromImage(image));
        // ui->scrollArea = new QScrollArea;
        ui->imageLabel_4->setScaledContents(true);


        QString program2 = "./codi/executa";
        //QStringList arguments;
        //std::string s1= fileName1_aux.toStdString();
        // std::string s2= fileName2_aux.toStdString();






        //double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 37.56, -10000, 10000, 2, &ok);

        arguments2 << s1 << s2 << num1 << num2 << num3 << num4;

        QProcess *myProcess2 = new QProcess(parent2);
        myProcess2->start(program2, arguments2);
        myProcess2->waitForFinished();
        QByteArray result = myProcess2->readAllStandardOutput();
        //result=myProcess->readAllStandardError();
        //result = result.simplified();
        QString str2(result.data());
        ui->des3->setText(str2);



    } else {
        //errorMessageDialog->showMessage(tr("T."));
        bool ok;
        int respuesta = 0;

        respuesta = QMessageBox::warning(this, "", trUtf8("El nombre de vertexs introduits no son correctes"));
        //double d = QInputDialog::error(this, tr("Error: els vertexs no son correctes."));
        //     QPushButton *errorButton = new QPushButton(tr("QErrorMessage::show&M&essage()"));


    }


    /*
             arguments << "-f" << fileName1;

             QProcess *myProcess = new QProcess(parent);
             myProcess->start(program, arguments);
             QVector<QString> vector_str;
             QString str;


            while (myProcess->state() != QProcess::Running ){

             ui->progressBar->setValue(int(proc));
             proc+=2;
             }
                myProcess->waitForFinished();
                    QByteArray result=myProcess->readAllStandardOutput();
                    //result = result.simplified();
                    QString str2(result.data());
                    foreach (str, str2.split('\n')) {
                         vector_str.push_back(str);
                       }

           foreach (QByteArray line, file.readAll().split('\n')) {
                if (line.startsWith("Function: ")) {
                    initFromConfig();
                    if (line.mid(10) == "Generic Network")
                        setValue("active", true);
                    else
                        setValue("active", false);
                }
            }

                    //result = scn.readAllStandardError ();
                    //scan_output->append(result.data());

                  image.load(vector_str.back());
                  QSize size(10, 10);
                  image.scaled(size);


                  // ui->label_3->setText(result.data());


                  QString aux_str;
                  vector_str.pop_back();
                  aux_str="La senyal ha segut reconeguda amb un:\n";
                  aux_str+= vector_str.back();
                  aux_str+=" de similitut.";
                  aux_str+= '\n';
                  aux_str+= '\n';
                  aux_str+="I te el significat de:\n";
                  vector_str.pop_back();
                  aux_str+= vector_str.back();
                  aux_str+=".";
                  //ui->label_5->setText(aux_str);



     */


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
