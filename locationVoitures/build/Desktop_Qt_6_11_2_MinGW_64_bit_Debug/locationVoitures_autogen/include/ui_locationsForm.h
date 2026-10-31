/********************************************************************************
** Form generated from reading UI file 'locationsForm.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCATIONSFORM_H
#define UI_LOCATIONSFORM_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_locationsForm
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

    void setupUi(QDialog *locationsForm)
    {
        if (locationsForm->objectName().isEmpty())
            locationsForm->setObjectName("locationsForm");
        locationsForm->resize(386, 426);
        locationsForm->setStyleSheet(QString::fromUtf8("background-color: rgb(36, 84, 126);"));
        comboClient = new QComboBox(locationsForm);
        comboClient->setObjectName("comboClient");
        comboClient->setGeometry(QRect(20, 80, 341, 28));
        comboClient->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        comboClient->setEditable(true);
        comboVoiture = new QComboBox(locationsForm);
        comboVoiture->setObjectName("comboVoiture");
        comboVoiture->setGeometry(QRect(20, 160, 341, 28));
        comboVoiture->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        comboVoiture->setEditable(true);
        dateDebut = new QDateEdit(locationsForm);
        dateDebut->setObjectName("dateDebut");
        dateDebut->setGeometry(QRect(20, 240, 161, 29));
        dateDebut->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateDebut->setCalendarPopup(true);
        dateDebut->setDate(QDate(2026, 1, 1));
        dateFin = new QDateEdit(locationsForm);
        dateFin->setObjectName("dateFin");
        dateFin->setGeometry(QRect(200, 240, 161, 29));
        dateFin->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateFin->setCalendarPopup(true);
        dateFin->setDate(QDate(2026, 1, 1));
        labelMontant = new QLabel(locationsForm);
        labelMontant->setObjectName("labelMontant");
        labelMontant->setGeometry(QRect(20, 300, 351, 31));
        btnSave = new QPushButton(locationsForm);
        btnSave->setObjectName("btnSave");
        btnSave->setGeometry(QRect(20, 360, 151, 41));
        btnSave->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        btnAnnuler = new QPushButton(locationsForm);
        btnAnnuler->setObjectName("btnAnnuler");
        btnAnnuler->setGeometry(QRect(210, 360, 151, 41));
        btnAnnuler->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        labelClient = new QLabel(locationsForm);
        labelClient->setObjectName("labelClient");
        labelClient->setGeometry(QRect(20, 40, 63, 20));
        labelVoiture = new QLabel(locationsForm);
        labelVoiture->setObjectName("labelVoiture");
        labelVoiture->setGeometry(QRect(20, 120, 63, 20));
        labelDateDebut = new QLabel(locationsForm);
        labelDateDebut->setObjectName("labelDateDebut");
        labelDateDebut->setGeometry(QRect(20, 210, 151, 20));
        labelDateFin = new QLabel(locationsForm);
        labelDateFin->setObjectName("labelDateFin");
        labelDateFin->setGeometry(QRect(200, 210, 171, 20));

        retranslateUi(locationsForm);

        QMetaObject::connectSlotsByName(locationsForm);
    } // setupUi

    void retranslateUi(QDialog *locationsForm)
    {
        locationsForm->setWindowTitle(QCoreApplication::translate("locationsForm", "Nouvelle location", nullptr));
        comboClient->setCurrentText(QString());
        comboClient->setPlaceholderText(QCoreApplication::translate("locationsForm", "S\303\251lectionner un client", nullptr));
        comboVoiture->setCurrentText(QString());
        comboVoiture->setPlaceholderText(QCoreApplication::translate("locationsForm", "S\303\251lectionner une voiture", nullptr));
        labelMontant->setText(QCoreApplication::translate("locationsForm", "<html><head/><body><p><span style=\" font-size:11pt; color:#0b223b;\">Montant total estim\303\251:</span></p></body></html>", nullptr));
        btnSave->setText(QCoreApplication::translate("locationsForm", "Enregistrer", nullptr));
        btnAnnuler->setText(QCoreApplication::translate("locationsForm", "Annuler", nullptr));
        labelClient->setText(QCoreApplication::translate("locationsForm", "<html><head/><body><p><span style=\" font-size:10pt; color:#f4fffa;\">Client</span></p></body></html>", nullptr));
        labelVoiture->setText(QCoreApplication::translate("locationsForm", "<html><head/><body><p><span style=\" font-size:10pt; color:#ffffff;\">Voiture</span></p></body></html>", nullptr));
        labelDateDebut->setText(QCoreApplication::translate("locationsForm", "<html><head/><body><p><span style=\" font-size:10pt; color:#ffffff;\">Date du d\303\251but</span></p></body></html>", nullptr));
        labelDateFin->setText(QCoreApplication::translate("locationsForm", "<html><head/><body><p><span style=\" font-size:10pt; color:#ffffff;\">Date de retour pr\303\251vue</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class locationsForm: public Ui_locationsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCATIONSFORM_H
