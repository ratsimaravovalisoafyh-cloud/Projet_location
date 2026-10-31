/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
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
    QPushButton *btnDashboard;
    QPushButton *btnClients;
    QPushButton *btnVoitures;
    QPushButton *btnLocations;
    QPushButton *btnLogOut;
    QPushButton *btnParams;
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
    QWidget *appHeader;
    QLabel *logoLabel;
    QPushButton *btnNotif;
    QPushButton *btnUser;
    QLabel *label;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1435, 724);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        sidebar = new QWidget(centralwidget);
        sidebar->setObjectName("sidebar");
        sidebar->setGeometry(QRect(0, 50, 201, 621));
        sidebar->setStyleSheet(QString::fromUtf8(""));
        btnDashboard = new QPushButton(sidebar);
        btnDashboard->setObjectName("btnDashboard");
        btnDashboard->setGeometry(QRect(20, 40, 151, 41));
        btnDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/assets/icons/icons-analytics-80.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnDashboard->setIcon(icon);
        btnClients = new QPushButton(sidebar);
        btnClients->setObjectName("btnClients");
        btnClients->setGeometry(QRect(40, 100, 111, 41));
        btnClients->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/assets/icons/icons-client-80.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnClients->setIcon(icon1);
        btnVoitures = new QPushButton(sidebar);
        btnVoitures->setObjectName("btnVoitures");
        btnVoitures->setGeometry(QRect(40, 160, 111, 41));
        btnVoitures->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/assets/icons/icons-car-80.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnVoitures->setIcon(icon2);
        btnLocations = new QPushButton(sidebar);
        btnLocations->setObjectName("btnLocations");
        btnLocations->setGeometry(QRect(40, 220, 111, 41));
        btnLocations->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/assets/icons/icons-schedule-80.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnLocations->setIcon(icon3);
        btnLogOut = new QPushButton(sidebar);
        btnLogOut->setObjectName("btnLogOut");
        btnLogOut->setGeometry(QRect(40, 560, 121, 51));
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::SystemLogOut));
        btnLogOut->setIcon(icon4);
        btnParams = new QPushButton(sidebar);
        btnParams->setObjectName("btnParams");
        btnParams->setGeometry(QRect(40, 280, 111, 41));
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::DocumentProperties));
        btnParams->setIcon(icon5);
        pageContent = new QWidget(centralwidget);
        pageContent->setObjectName("pageContent");
        pageContent->setGeometry(QRect(200, 50, 1221, 621));
        headerWidget = new QWidget(pageContent);
        headerWidget->setObjectName("headerWidget");
        headerWidget->setGeometry(QRect(0, 0, 1221, 61));
        titre = new QLabel(headerWidget);
        titre->setObjectName("titre");
        titre->setGeometry(QRect(20, 20, 371, 31));
        btnNouvelleLocation = new QPushButton(headerWidget);
        btnNouvelleLocation->setObjectName("btnNouvelleLocation");
        btnNouvelleLocation->setGeometry(QRect(980, 20, 191, 41));
        btnNouvelleLocation->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd));
        btnNouvelleLocation->setIcon(icon6);
        historique = new QLabel(pageContent);
        historique->setObjectName("historique");
        historique->setGeometry(QRect(10, 80, 261, 21));
        filtreWidget = new QWidget(pageContent);
        filtreWidget->setObjectName("filtreWidget");
        filtreWidget->setGeometry(QRect(0, 110, 1221, 51));
        barreSearch = new QLineEdit(filtreWidget);
        barreSearch->setObjectName("barreSearch");
        barreSearch->setGeometry(QRect(40, 10, 351, 28));
        barreSearch->setReadOnly(false);
        status = new QComboBox(filtreWidget);
        status->addItem(QString());
        status->addItem(QString());
        status->addItem(QString());
        status->setObjectName("status");
        status->setGeometry(QRect(470, 10, 131, 28));
        status->setEditable(true);
        checkBox = new QCheckBox(filtreWidget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(680, 10, 92, 25));
        Dulabel = new QLabel(filtreWidget);
        Dulabel->setObjectName("Dulabel");
        Dulabel->setGeometry(QRect(810, 10, 31, 20));
        dateDebut = new QDateEdit(filtreWidget);
        dateDebut->setObjectName("dateDebut");
        dateDebut->setGeometry(QRect(880, 10, 110, 29));
        dateDebut->setCalendarPopup(true);
        dateDebut->setDate(QDate(2026, 1, 1));
        AuLabel = new QLabel(filtreWidget);
        AuLabel->setObjectName("AuLabel");
        AuLabel->setGeometry(QRect(1020, 10, 31, 20));
        dateFin = new QDateEdit(filtreWidget);
        dateFin->setObjectName("dateFin");
        dateFin->setGeometry(QRect(1070, 10, 110, 29));
        dateFin->setCalendarPopup(true);
        dateFin->setDate(QDate(2026, 1, 1));
        tableView = new QTableView(pageContent);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(60, 170, 951, 431));
        appHeader = new QWidget(centralwidget);
        appHeader->setObjectName("appHeader");
        appHeader->setGeometry(QRect(-1, 0, 1421, 51));
        logoLabel = new QLabel(appHeader);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(10, 10, 61, 31));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/assets/logo-remove-background.png")));
        btnNotif = new QPushButton(appHeader);
        btnNotif->setObjectName("btnNotif");
        btnNotif->setGeometry(QRect(1310, 10, 31, 29));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/assets/icons/icons-notification-80.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnNotif->setIcon(icon7);
        btnUser = new QPushButton(appHeader);
        btnUser->setObjectName("btnUser");
        btnUser->setGeometry(QRect(1370, 10, 31, 29));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/assets/icons/icons-user-80.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnUser->setIcon(icon8);
        label = new QLabel(appHeader);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 10, 111, 31));
        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1435, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnDashboard->setText(QCoreApplication::translate("MainWindow", "Tableau de Bord", nullptr));
#if QT_CONFIG(shortcut)
        btnDashboard->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        btnClients->setText(QCoreApplication::translate("MainWindow", "Clients", nullptr));
#if QT_CONFIG(shortcut)
        btnClients->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        btnVoitures->setText(QCoreApplication::translate("MainWindow", "Voitures", nullptr));
#if QT_CONFIG(shortcut)
        btnVoitures->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        btnLocations->setText(QCoreApplication::translate("MainWindow", "Locations", nullptr));
#if QT_CONFIG(shortcut)
        btnLocations->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        btnLogOut->setText(QCoreApplication::translate("MainWindow", "D\303\251connexion", nullptr));
#if QT_CONFIG(shortcut)
        btnLogOut->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        btnParams->setText(QCoreApplication::translate("MainWindow", "Param\303\250tres", nullptr));
        titre->setText(QCoreApplication::translate("MainWindow", "Gestion des locations", nullptr));
        btnNouvelleLocation->setText(QCoreApplication::translate("MainWindow", " Nouvelle Location", nullptr));
#if QT_CONFIG(shortcut)
        btnNouvelleLocation->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        historique->setText(QCoreApplication::translate("MainWindow", "Historique des locations", nullptr));
        barreSearch->setText(QString());
        barreSearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher un client ou voiture", nullptr));
        status->setItemText(0, QCoreApplication::translate("MainWindow", "En cours", nullptr));
        status->setItemText(1, QCoreApplication::translate("MainWindow", "Annul\303\251e", nullptr));
        status->setItemText(2, QCoreApplication::translate("MainWindow", "Termin\303\251e", nullptr));

        status->setCurrentText(QCoreApplication::translate("MainWindow", "En cours", nullptr));
        status->setPlaceholderText(QString());
        checkBox->setText(QCoreApplication::translate("MainWindow", "P\303\251riode", nullptr));
        Dulabel->setText(QCoreApplication::translate("MainWindow", "Du", nullptr));
        AuLabel->setText(QCoreApplication::translate("MainWindow", "Au", nullptr));
        btnNotif->setText(QString());
#if QT_CONFIG(shortcut)
        btnNotif->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        btnUser->setText(QString());
#if QT_CONFIG(shortcut)
        btnUser->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        label->setText(QCoreApplication::translate("MainWindow", "Rent a car", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
