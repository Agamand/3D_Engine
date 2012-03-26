/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon 26. Mar 22:36:38 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNouvelle_sc_ne;
    QAction *actionSauvegarder;
    QAction *actionCharger;
    QAction *actionQuitter;
    QAction *actionFil_de_fer;
    QAction *actionFil_de_fer_2;
    QAction *actionPoints;
    QWidget *centralwidget;
    GlWidget *gl;
    QSlider *Time;
    QSpinBox *maxTime;
    QSpinBox *actualTime;
    QLabel *maxTimeLabel;
    QLabel *actualTimeLabel;
    QLabel *maxTimeLabel_2;
    QLabel *maxTimeLabel_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *tab_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QComboBox *comboBox;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuPr_f_rence;
    QMenu *menuMode_d_affichage;
    QMenu *menuOptions;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 607);
        actionNouvelle_sc_ne = new QAction(MainWindow);
        actionNouvelle_sc_ne->setObjectName(QString::fromUtf8("actionNouvelle_sc_ne"));
        actionSauvegarder = new QAction(MainWindow);
        actionSauvegarder->setObjectName(QString::fromUtf8("actionSauvegarder"));
        actionCharger = new QAction(MainWindow);
        actionCharger->setObjectName(QString::fromUtf8("actionCharger"));
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionFil_de_fer = new QAction(MainWindow);
        actionFil_de_fer->setObjectName(QString::fromUtf8("actionFil_de_fer"));
        actionFil_de_fer_2 = new QAction(MainWindow);
        actionFil_de_fer_2->setObjectName(QString::fromUtf8("actionFil_de_fer_2"));
        actionPoints = new QAction(MainWindow);
        actionPoints->setObjectName(QString::fromUtf8("actionPoints"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setLayoutDirection(Qt::LeftToRight);
        centralwidget->setAutoFillBackground(true);
        gl = new GlWidget(centralwidget);
        gl->setObjectName(QString::fromUtf8("gl"));
        gl->setGeometry(QRect(10, 20, 621, 491));
        Time = new QSlider(centralwidget);
        Time->setObjectName(QString::fromUtf8("Time"));
        Time->setGeometry(QRect(10, 520, 621, 20));
        Time->setMaximum(10000);
        Time->setSingleStep(10);
        Time->setPageStep(100);
        Time->setValue(0);
        Time->setOrientation(Qt::Horizontal);
        maxTime = new QSpinBox(centralwidget);
        maxTime->setObjectName(QString::fromUtf8("maxTime"));
        maxTime->setGeometry(QRect(700, 500, 91, 22));
        maxTime->setMaximum(10000000);
        maxTime->setSingleStep(100);
        maxTime->setValue(10000);
        actualTime = new QSpinBox(centralwidget);
        actualTime->setObjectName(QString::fromUtf8("actualTime"));
        actualTime->setGeometry(QRect(700, 530, 91, 22));
        actualTime->setMaximum(10000);
        actualTime->setSingleStep(100);
        maxTimeLabel = new QLabel(centralwidget);
        maxTimeLabel->setObjectName(QString::fromUtf8("maxTimeLabel"));
        maxTimeLabel->setGeometry(QRect(640, 500, 71, 21));
        actualTimeLabel = new QLabel(centralwidget);
        actualTimeLabel->setObjectName(QString::fromUtf8("actualTimeLabel"));
        actualTimeLabel->setGeometry(QRect(640, 530, 71, 21));
        maxTimeLabel_2 = new QLabel(centralwidget);
        maxTimeLabel_2->setObjectName(QString::fromUtf8("maxTimeLabel_2"));
        maxTimeLabel_2->setGeometry(QRect(760, 500, 16, 21));
        maxTimeLabel_3 = new QLabel(centralwidget);
        maxTimeLabel_3->setObjectName(QString::fromUtf8("maxTimeLabel_3"));
        maxTimeLabel_3->setGeometry(QRect(760, 530, 16, 21));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(640, 20, 151, 471));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 151, 451));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 149, 449));
        scrollArea->setWidget(scrollAreaWidgetContents);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        scrollArea_2 = new QScrollArea(tab_2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(0, 0, 151, 451));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 149, 449));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        tabWidget->addTab(tab_2, QString());
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 540, 51, 23));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(90, 540, 51, 23));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 540, 51, 23));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(370, 540, 69, 22));
        comboBox->setMaxVisibleItems(10);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menuPr_f_rence = new QMenu(menubar);
        menuPr_f_rence->setObjectName(QString::fromUtf8("menuPr_f_rence"));
        menuMode_d_affichage = new QMenu(menuPr_f_rence);
        menuMode_d_affichage->setObjectName(QString::fromUtf8("menuMode_d_affichage"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuPr_f_rence->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menu->menuAction());
        menuFichier->addSeparator();
        menuFichier->addAction(actionNouvelle_sc_ne);
        menuFichier->addAction(actionSauvegarder);
        menuFichier->addAction(actionCharger);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuitter);
        menuFichier->addSeparator();
        menuPr_f_rence->addSeparator();
        menuPr_f_rence->addAction(menuMode_d_affichage->menuAction());
        menuMode_d_affichage->addSeparator();
        menuMode_d_affichage->addAction(actionFil_de_fer);
        menuMode_d_affichage->addAction(actionFil_de_fer_2);
        menuMode_d_affichage->addAction(actionPoints);
        menuMode_d_affichage->addSeparator();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNouvelle_sc_ne->setText(QApplication::translate("MainWindow", "Nouvelle sc\303\250ne", 0, QApplication::UnicodeUTF8));
        actionSauvegarder->setText(QApplication::translate("MainWindow", "Sauvegarder", 0, QApplication::UnicodeUTF8));
        actionCharger->setText(QApplication::translate("MainWindow", "Charger", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
        actionFil_de_fer->setText(QApplication::translate("MainWindow", "Plein", 0, QApplication::UnicodeUTF8));
        actionFil_de_fer_2->setText(QApplication::translate("MainWindow", "Fil de fer", 0, QApplication::UnicodeUTF8));
        actionPoints->setText(QApplication::translate("MainWindow", "Points", 0, QApplication::UnicodeUTF8));
        maxTimeLabel->setText(QApplication::translate("MainWindow", "Max time", 0, QApplication::UnicodeUTF8));
        actualTimeLabel->setText(QApplication::translate("MainWindow", "Actual time", 0, QApplication::UnicodeUTF8));
        maxTimeLabel_2->setText(QApplication::translate("MainWindow", "ms", 0, QApplication::UnicodeUTF8));
        maxTimeLabel_3->setText(QApplication::translate("MainWindow", "ms", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "Lecture", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Aucun", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Rotation X", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Rotation Y", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Rotation Z", 0, QApplication::UnicodeUTF8)
        );
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
        menuPr_f_rence->setTitle(QApplication::translate("MainWindow", "Pr\303\251f\303\251rence", 0, QApplication::UnicodeUTF8));
        menuMode_d_affichage->setTitle(QApplication::translate("MainWindow", "Mode d'affichage", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
