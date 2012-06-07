/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu May 10 16:45:17 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCarrega_nova_imatge;
    QAction *actionEixir;
    QAction *actionAjuda;
    QAction *actionSobre_rec_senyals;
    QWidget *centralWidget;
    QFrame *frame;
    QLabel *label_2;
    QLabel *imageLabel;
    QLabel *imageLabel_2;
    QLabel *label_6;
    QPushButton *b_carrega1;
    QPushButton *b_carrega2;
    QTextBrowser *des1;
    QTextBrowser *des2;
    QFrame *frame_2;
    QPushButton *juxta;
    QLabel *imageLabel_4;
    QLabel *label_9;
    QTextBrowser *des3;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuAjuda;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(799, 624);
        actionCarrega_nova_imatge = new QAction(MainWindow);
        actionCarrega_nova_imatge->setObjectName(QString::fromUtf8("actionCarrega_nova_imatge"));
        actionEixir = new QAction(MainWindow);
        actionEixir->setObjectName(QString::fromUtf8("actionEixir"));
        actionAjuda = new QAction(MainWindow);
        actionAjuda->setObjectName(QString::fromUtf8("actionAjuda"));
        actionSobre_rec_senyals = new QAction(MainWindow);
        actionSobre_rec_senyals->setObjectName(QString::fromUtf8("actionSobre_rec_senyals"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 20, 771, 331));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(190, 0, 101, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        imageLabel = new QLabel(frame);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
        imageLabel->setGeometry(QRect(170, 30, 131, 121));
        imageLabel->setFrameShape(QFrame::WinPanel);
        imageLabel->setMargin(0);
        imageLabel_2 = new QLabel(frame);
        imageLabel_2->setObjectName(QString::fromUtf8("imageLabel_2"));
        imageLabel_2->setGeometry(QRect(170, 190, 131, 121));
        imageLabel_2->setFrameShape(QFrame::WinPanel);
        imageLabel_2->setMargin(0);
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(190, 160, 101, 31));
        label_6->setFont(font);
        b_carrega1 = new QPushButton(frame);
        b_carrega1->setObjectName(QString::fromUtf8("b_carrega1"));
        b_carrega1->setGeometry(QRect(10, 80, 121, 41));
        b_carrega2 = new QPushButton(frame);
        b_carrega2->setObjectName(QString::fromUtf8("b_carrega2"));
        b_carrega2->setGeometry(QRect(10, 240, 121, 41));
        des1 = new QTextBrowser(frame);
        des1->setObjectName(QString::fromUtf8("des1"));
        des1->setGeometry(QRect(360, 30, 381, 121));
        des2 = new QTextBrowser(frame);
        des2->setObjectName(QString::fromUtf8("des2"));
        des2->setGeometry(QRect(360, 190, 381, 121));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(20, 370, 771, 201));
        frame_2->setFrameShape(QFrame::WinPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_2->setLineWidth(7);
        juxta = new QPushButton(frame_2);
        juxta->setObjectName(QString::fromUtf8("juxta"));
        juxta->setGeometry(QRect(40, 80, 181, 41));
        imageLabel_4 = new QLabel(frame_2);
        imageLabel_4->setObjectName(QString::fromUtf8("imageLabel_4"));
        imageLabel_4->setGeometry(QRect(260, 20, 161, 151));
        imageLabel_4->setFrameShape(QFrame::WinPanel);
        imageLabel_4->setMargin(0);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(40, 10, 191, 31));
        label_9->setFont(font);
        des3 = new QTextBrowser(frame_2);
        des3->setObjectName(QString::fromUtf8("des3"));
        des3->setGeometry(QRect(440, 20, 311, 151));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 799, 25));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuAjuda = new QMenu(menuBar);
        menuAjuda->setObjectName(QString::fromUtf8("menuAjuda"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuBar->addAction(menuAjuda->menuAction());
        menuMenu->addAction(actionCarrega_nova_imatge);
        menuMenu->addSeparator();
        menuMenu->addAction(actionEixir);
        menuAjuda->addAction(actionAjuda);
        menuAjuda->addAction(actionSobre_rec_senyals);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionCarrega_nova_imatge->setText(QApplication::translate("MainWindow", "Carrega nova imatge", 0, QApplication::UnicodeUTF8));
        actionEixir->setText(QApplication::translate("MainWindow", "Eixir", 0, QApplication::UnicodeUTF8));
        actionAjuda->setText(QApplication::translate("MainWindow", "Ajuda", 0, QApplication::UnicodeUTF8));
        actionSobre_rec_senyals->setText(QApplication::translate("MainWindow", "Sobre rec_senyals", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Figura 1:", 0, QApplication::UnicodeUTF8));
        imageLabel->setText(QString());
        imageLabel_2->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Figura 2:", 0, QApplication::UnicodeUTF8));
        b_carrega1->setText(QApplication::translate("MainWindow", "Carrega figura 1", 0, QApplication::UnicodeUTF8));
        b_carrega2->setText(QApplication::translate("MainWindow", "Carrega figura 2", 0, QApplication::UnicodeUTF8));
        juxta->setText(QApplication::translate("MainWindow", "Aplicar difer\303\250ncia", 0, QApplication::UnicodeUTF8));
        imageLabel_4->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "Figura resultant:", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
        menuAjuda->setTitle(QApplication::translate("MainWindow", "Ajuda", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
