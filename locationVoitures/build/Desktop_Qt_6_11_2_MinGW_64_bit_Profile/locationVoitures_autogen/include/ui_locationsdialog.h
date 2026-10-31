/********************************************************************************
** Form generated from reading UI file 'locationsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCATIONSDIALOG_H
#define UI_LOCATIONSDIALOG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_locationsDialog
{
public:
    QComboBox *comboClient;
    QComboBox *comboVoiture;
    QDateEdit *dateDebut;
    QDateEdit *dateFin;
    QLabel *labelMontant;
    QPushButton *btnSave;
    QPushButton *btnAnnuler;
    QLabel *labelClient;
    QLabel *labelVoiture;
    QLabel *labelDateDebut;
    QLabel *labelDateFin;

    void setupUi(QDialog *locationsDialog)
    {
        if (locationsDialog->objectName().isEmpty())
            locationsDialog->setObjectName("locationsDialog");
        comboClient = new QComboBox(locationsDialog);
        comboClient->setObjectName("comboClient");
        comboClient->setGeometry(QRect(20, 90, 181, 28));
        comboClient->setEditable(true);
        comboVoiture = new QComboBox(locationsDialog);
        comboVoiture->setObjectName("comboVoiture");
        comboVoiture->setGeometry(QRect(20, 160, 211, 28));
        comboVoiture->setEditable(true);
        dateDebut = new QDateEdit(locationsDialog);
        dateDebut->setObjectName("dateDebut");
        dateDebut->setGeometry(QRect(10, 250, 110, 29));
        dateDebut->setCalendarPopup(true);
        dateFin = new QDateEdit(locationsDialog);
        dateFin->setObjectName("dateFin");
        dateFin->setGeometry(QRect(240, 250, 110, 29));
        dateFin->setCalendarPopup(true);
        dateFin->setDate(QDate(2000, 1, 1));
        labelMontant = new QLabel(locationsDialog);
        labelMontant->setObjectName("labelMontant");
        labelMontant->setGeometry(QRect(20, 300, 161, 20));
        btnSave = new QPushButton(locationsDialog);
        btnSave->setObjectName("btnSave");
        btnSave->setGeometry(QRect(10, 360, 90, 29));
        btnAnnuler = new QPushButton(locationsDialog);
        btnAnnuler->setObjectName("btnAnnuler");
        btnAnnuler->setGeometry(QRect(180, 360, 90, 29));
        labelClient = new QLabel(locationsDialog);
        labelClient->setObjectName("labelClient");
        labelClient->setGeometry(QRect(20, 60, 63, 20));
        labelVoiture = new QLabel(locationsDialog);
        labelVoiture->setObjectName("labelVoiture");
        labelVoiture->setGeometry(QRect(20, 130, 63, 20));
        labelDateDebut = new QLabel(locationsDialog);
        labelDateDebut->setObjectName("labelDateDebut");
        labelDateDebut->setGeometry(QRect(20, 220, 101, 20));
        labelDateFin = new QLabel(locationsDialog);
        labelDateFin->setObjectName("labelDateFin");
        labelDateFin->setGeometry(QRect(250, 220, 151, 20));

        retranslateUi(locationsDialog);

        QMetaObject::connectSlotsByName(locationsDialog);
    } // setupUi

    void retranslateUi(QDialog *locationsDialog)
    {
        locationsDialog->setWindowTitle(QCoreApplication::translate("locationsDialog", "Nouvelle location", nullptr));
        comboClient->setCurrentText(QCoreApplication::translate("locationsDialog", "S\303\251lectionner un client", nullptr));
        comboVoiture->setCurrentText(QCoreApplication::translate("locationsDialog", "S\303\251lectionner une voiture", nullptr));
        labelMontant->setText(QCoreApplication::translate("locationsDialog", " Montant total \303\251stim\303\251", nullptr));
        btnSave->setText(QCoreApplication::translate("locationsDialog", "Enregistrer", nullptr));
        btnAnnuler->setText(QCoreApplication::translate("locationsDialog", "Annuler", nullptr));
        labelClient->setText(QCoreApplication::translate("locationsDialog", "Client", nullptr));
        labelVoiture->setText(QCoreApplication::translate("locationsDialog", "Voiture", nullptr));
        labelDateDebut->setText(QCoreApplication::translate("locationsDialog", "Date du d\303\251but", nullptr));
        labelDateFin->setText(QCoreApplication::translate("locationsDialog", "Date de retour pr\303\251vue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class locationsDialog: public Ui_locationsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCATIONSDIALOG_H
