#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void Carrega1();
    void Carrega2();

    void Reconeix();

protected:
    void changeEvent(QEvent *e);


private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
