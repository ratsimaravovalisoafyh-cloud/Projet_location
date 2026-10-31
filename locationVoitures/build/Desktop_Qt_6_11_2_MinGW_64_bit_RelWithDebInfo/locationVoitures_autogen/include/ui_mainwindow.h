/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *sidebar;
    QLabel *brand;
    QPushButton *btnDashboard;
    QPushButton *btnClients;
    QPushButton *btnVoitures;
    QPushButton *btnLocations;
    QPushButton *btnLogOut;
    QWidget *pageContent;
    QWidget *headerWidget;
    QLabel *titre;
    QPushButton *btnNouvelleLocation;
    QLabel *historique;
    QWidget *filtreWidget;
    QLineEdit *barreSearch;
    QComboBox *status;
    QCheckBox *checkBox;
    QLabel *Dulabel;
    QDateEdit *dateDebut;
    QLabel *AuLabel;
    QDateEdit *dateFin;
    QTableView *tableView;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1226, 661);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        sidebar = new QWidget(centralwidget);
        sidebar->setObjectName("sidebar");
        sidebar->setGeometry(QRect(0, 0, 201, 631));
        sidebar->setStyleSheet(QString::fromUtf8(""));
        brand = new QLabel(sidebar);
        brand->setObjectName("brand");
        brand->setGeometry(QRect(20, 20, 151, 20));
        btnDashboard = new QPushButton(sidebar);
        btnDashboard->setObjectName("btnDashboard");
        btnDashboard->setGeometry(QRect(30, 120, 121, 29));
        btnClients = new QPushButton(sidebar);
        btnClients->setObjectName("btnClients");
        btnClients->setGeometry(QRect(40, 170, 90, 29));
        btnVoitures = new QPushButton(sidebar);
        btnVoitures->setObjectName("btnVoitures");
        btnVoitures->setGeometry(QRect(40, 220, 90, 29));
        btnLocations = new QPushButton(sidebar);
        btnLocations->setObjectName("btnLocations");
        btnLocations->setGeometry(QRect(40, 270, 90, 29));
        btnLogOut = new QPushButton(sidebar);
        btnLogOut->setObjectName("btnLogOut");
        btnLogOut->setGeometry(QRect(40, 560, 90, 29));
        pageContent = new QWidget(centralwidget);
        pageContent->setObjectName("pageContent");
        pageContent->setGeometry(QRect(200, 0, 1021, 631));
        headerWidget = new QWidget(pageContent);
        headerWidget->setObjectName("headerWidget");
        headerWidget->setGeometry(QRect(-1, 0, 1021, 61));
        titre = new QLabel(headerWidget);
        titre->setObjectName("titre");
        titre->setGeometry(QRect(20, 20, 151, 20));
        btnNouvelleLocation = new QPushButton(headerWidget);
        btnNouvelleLocation->setObjectName("btnNouvelleLocation");
        btnNouvelleLocation->setGeometry(QRect(809, 20, 151, 29));
        historique = new QLabel(pageContent);
        historique->setObjectName("historique");
        historique->setGeometry(QRect(10, 80, 171, 20));
        filtreWidget = new QWidget(pageContent);
        filtreWidget->setObjectName("filtreWidget");
        filtreWidget->setGeometry(QRect(0, 110, 1021, 51));
        barreSearch = new QLineEdit(filtreWidget);
        barreSearch->setObjectName("barreSearch");
        barreSearch->setGeometry(QRect(10, 10, 351, 28));
        barreSearch->setReadOnly(false);
        status = new QComboBox(filtreWidget);
        status->addItem(QString());
        status->addItem(QString());
        status->addItem(QString());
        status->setObjectName("status");
        status->setGeometry(QRect(400, 10, 131, 28));
        status->setEditable(true);
        checkBox = new QCheckBox(filtreWidget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(550, 10, 92, 25));
        Dulabel = new QLabel(filtreWidget);
        Dulabel->setObjectName("Dulabel");
        Dulabel->setGeometry(QRect(670, 10, 31, 20));
        dateDebut = new QDateEdit(filtreWidget);
        dateDebut->setObjectName("dateDebut");
        dateDebut->setGeometry(QRect(710, 10, 110, 29));
        dateDebut->setCalendarPopup(true);
        AuLabel = new QLabel(filtreWidget);
        AuLabel->setObjectName("AuLabel");
        AuLabel->setGeometry(QRect(830, 10, 31, 20));
        dateFin = new QDateEdit(filtreWidget);
        dateFin->setObjectName("dateFin");
        dateFin->setGeometry(QRect(880, 10, 110, 29));
        dateFin->setCalendarPopup(true);
        tableView = new QTableView(pageContent);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(10, 171, 1011, 451));
        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1226, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        brand->setText(QCoreApplication::translate("MainWindow", " LOCATION VOITURES", nullptr));
        btnDashboard->setText(QCoreApplication::translate("MainWindow", "Tableau de Bord", nullptr));
        btnClients->setText(QCoreApplication::translate("MainWindow", "Clients", nullptr));
        btnVoitures->setText(QCoreApplication::translate("MainWindow", "Voitures", nullptr));
        btnLocations->setText(QCoreApplication::translate("MainWindow", "Locations", nullptr));
        btnLogOut->setText(QCoreApplication::translate("MainWindow", "D\303\251connexion", nullptr));
        titre->setText(QCoreApplication::translate("MainWindow", "Gestion des locations", nullptr));
        btnNouvelleLocation->setText(QCoreApplication::translate("MainWindow", "+ Nouvelle Location", nullptr));
        historique->setText(QCoreApplication::translate("MainWindow", "Historique des locations", nullptr));
        barreSearch->setText(QString());
        barreSearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher un client ou voiture", nullptr));
        status->setItemText(0, QCoreApplication::translate("MainWindow", "En cours", nullptr));
        status->setItemText(1, QCoreApplication::translate("MainWindow", "Annul\303\251e", nullptr));
        status->setItemText(2, QCoreApplication::translate("MainWindow", "Termin\303\251e", nullptr));

        status->setCurrentText(QCoreApplication::translate("MainWindow", "Tous les status", nullptr));
        status->setPlaceholderText(QString());
        checkBox->setText(QCoreApplication::translate("MainWindow", "P\303\251riode", nullptr));
        Dulabel->setText(QCoreApplication::translate("MainWindow", "Du", nullptr));
        AuLabel->setText(QCoreApplication::translate("MainWindow", "Au", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
