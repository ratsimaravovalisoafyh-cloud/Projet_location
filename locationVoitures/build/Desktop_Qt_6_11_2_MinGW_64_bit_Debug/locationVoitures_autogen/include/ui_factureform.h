/********************************************************************************
** Form generated from reading UI file 'factureform.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACTUREFORM_H
#define UI_FACTUREFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_factureForm
{
public:
    QVBoxLayout *layoutFacture;
    QFrame *headerWidget;
    QHBoxLayout *layoutHeader;
    QLabel *logo;
    QWidget *titleContainer;
    QVBoxLayout *layoutTitre;
    QLabel *titre;
    QLabel *soustitre;
    QSpacerItem *spacerHeader;
    QLabel *numeroFacture;
    QFrame *infoWidget;
    QGridLayout *layoutInfos;
    QLabel *captionClient;
    QLabel *captionVoiture;
    QLabel *labelClient;
    QLabel *labelVoiture;
    QLabel *captionReferenceClient;
    QLabel *captionReferenceLocation;
    QLabel *labelReferenceClient;
    QLabel *labelReferenceLocation;
    QFrame *datesWidget;
    QGridLayout *layoutDates;
    QLabel *captionDateDebut;
    QLabel *captionDateFin;
    QLabel *labelDateDebut;
    QLabel *labelDateFin;
    QFrame *montantWidget;
    QHBoxLayout *layoutMontant;
    QWidget *statusContainer;
    QVBoxLayout *layoutStatut;
    QLabel *captionStatut;
    QLabel *labelStatut;
    QSpacerItem *spacerMontant;
    QWidget *montantContainer;
    QVBoxLayout *layoutTotal;
    QLabel *captionMontant;
    QLabel *labelMontant;
    QFrame *qrWidget;
    QVBoxLayout *layoutQR;
    QLabel *labelQRTitre;
    QLabel *qrCodeLabel;
    QLabel *labelQRNote;
    QHBoxLayout *layoutBoutons;
    QSpacerItem *spacerBoutons;
    QPushButton *btnFermer;
    QPushButton *btnTelechargerPdf;

    void setupUi(QDialog *factureForm)
    {
        if (factureForm->objectName().isEmpty())
            factureForm->setObjectName("factureForm");
        factureForm->resize(630, 730);
        factureForm->setMinimumSize(QSize(590, 680));
        layoutFacture = new QVBoxLayout(factureForm);
        layoutFacture->setSpacing(12);
        layoutFacture->setObjectName("layoutFacture");
        layoutFacture->setContentsMargins(22, 20, 22, 20);
        headerWidget = new QFrame(factureForm);
        headerWidget->setObjectName("headerWidget");
        headerWidget->setFrameShape(QFrame::Shape::StyledPanel);
        headerWidget->setFrameShadow(QFrame::Shadow::Plain);
        layoutHeader = new QHBoxLayout(headerWidget);
        layoutHeader->setSpacing(14);
        layoutHeader->setObjectName("layoutHeader");
        layoutHeader->setContentsMargins(16, 12, 16, 12);
        logo = new QLabel(headerWidget);
        logo->setObjectName("logo");
        logo->setMinimumSize(QSize(90, 0));

        layoutHeader->addWidget(logo);

        titleContainer = new QWidget(headerWidget);
        titleContainer->setObjectName("titleContainer");
        layoutTitre = new QVBoxLayout(titleContainer);
        layoutTitre->setSpacing(3);
        layoutTitre->setObjectName("layoutTitre");
        layoutTitre->setContentsMargins(0, 0, 0, 0);
        titre = new QLabel(titleContainer);
        titre->setObjectName("titre");

        layoutTitre->addWidget(titre);

        soustitre = new QLabel(titleContainer);
        soustitre->setObjectName("soustitre");

        layoutTitre->addWidget(soustitre);


        layoutHeader->addWidget(titleContainer);

        spacerHeader = new QSpacerItem(25, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutHeader->addItem(spacerHeader);

        numeroFacture = new QLabel(headerWidget);
        numeroFacture->setObjectName("numeroFacture");
        numeroFacture->setMinimumSize(QSize(145, 32));
        numeroFacture->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutHeader->addWidget(numeroFacture);


        layoutFacture->addWidget(headerWidget);

        infoWidget = new QFrame(factureForm);
        infoWidget->setObjectName("infoWidget");
        infoWidget->setFrameShape(QFrame::Shape::StyledPanel);
        infoWidget->setFrameShadow(QFrame::Shadow::Plain);
        layoutInfos = new QGridLayout(infoWidget);
        layoutInfos->setObjectName("layoutInfos");
        layoutInfos->setHorizontalSpacing(18);
        layoutInfos->setVerticalSpacing(8);
        layoutInfos->setContentsMargins(18, 14, 18, 14);
        captionClient = new QLabel(infoWidget);
        captionClient->setObjectName("captionClient");

        layoutInfos->addWidget(captionClient, 0, 0, 1, 1);

        captionVoiture = new QLabel(infoWidget);
        captionVoiture->setObjectName("captionVoiture");

        layoutInfos->addWidget(captionVoiture, 0, 2, 1, 1);

        labelClient = new QLabel(infoWidget);
        labelClient->setObjectName("labelClient");
        labelClient->setWordWrap(true);

        layoutInfos->addWidget(labelClient, 1, 0, 1, 2);

        labelVoiture = new QLabel(infoWidget);
        labelVoiture->setObjectName("labelVoiture");
        labelVoiture->setWordWrap(true);

        layoutInfos->addWidget(labelVoiture, 1, 2, 1, 2);

        captionReferenceClient = new QLabel(infoWidget);
        captionReferenceClient->setObjectName("captionReferenceClient");

        layoutInfos->addWidget(captionReferenceClient, 2, 0, 1, 1);

        captionReferenceLocation = new QLabel(infoWidget);
        captionReferenceLocation->setObjectName("captionReferenceLocation");

        layoutInfos->addWidget(captionReferenceLocation, 2, 2, 1, 1);

        labelReferenceClient = new QLabel(infoWidget);
        labelReferenceClient->setObjectName("labelReferenceClient");

        layoutInfos->addWidget(labelReferenceClient, 3, 0, 1, 2);

        labelReferenceLocation = new QLabel(infoWidget);
        labelReferenceLocation->setObjectName("labelReferenceLocation");

        layoutInfos->addWidget(labelReferenceLocation, 3, 2, 1, 2);


        layoutFacture->addWidget(infoWidget);

        datesWidget = new QFrame(factureForm);
        datesWidget->setObjectName("datesWidget");
        datesWidget->setFrameShape(QFrame::Shape::StyledPanel);
        datesWidget->setFrameShadow(QFrame::Shadow::Plain);
        layoutDates = new QGridLayout(datesWidget);
        layoutDates->setObjectName("layoutDates");
        layoutDates->setHorizontalSpacing(20);
        layoutDates->setVerticalSpacing(6);
        layoutDates->setContentsMargins(18, 12, 18, 12);
        captionDateDebut = new QLabel(datesWidget);
        captionDateDebut->setObjectName("captionDateDebut");

        layoutDates->addWidget(captionDateDebut, 0, 0, 1, 1);

        captionDateFin = new QLabel(datesWidget);
        captionDateFin->setObjectName("captionDateFin");

        layoutDates->addWidget(captionDateFin, 0, 1, 1, 1);

        labelDateDebut = new QLabel(datesWidget);
        labelDateDebut->setObjectName("labelDateDebut");

        layoutDates->addWidget(labelDateDebut, 1, 0, 1, 1);

        labelDateFin = new QLabel(datesWidget);
        labelDateFin->setObjectName("labelDateFin");

        layoutDates->addWidget(labelDateFin, 1, 1, 1, 1);


        layoutFacture->addWidget(datesWidget);

        montantWidget = new QFrame(factureForm);
        montantWidget->setObjectName("montantWidget");
        montantWidget->setFrameShape(QFrame::Shape::StyledPanel);
        montantWidget->setFrameShadow(QFrame::Shadow::Plain);
        layoutMontant = new QHBoxLayout(montantWidget);
        layoutMontant->setSpacing(12);
        layoutMontant->setObjectName("layoutMontant");
        layoutMontant->setContentsMargins(18, 12, 18, 12);
        statusContainer = new QWidget(montantWidget);
        statusContainer->setObjectName("statusContainer");
        layoutStatut = new QVBoxLayout(statusContainer);
        layoutStatut->setSpacing(5);
        layoutStatut->setObjectName("layoutStatut");
        layoutStatut->setContentsMargins(0, 0, 0, 0);
        captionStatut = new QLabel(statusContainer);
        captionStatut->setObjectName("captionStatut");

        layoutStatut->addWidget(captionStatut);

        labelStatut = new QLabel(statusContainer);
        labelStatut->setObjectName("labelStatut");

        layoutStatut->addWidget(labelStatut);


        layoutMontant->addWidget(statusContainer);

        spacerMontant = new QSpacerItem(30, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutMontant->addItem(spacerMontant);

        montantContainer = new QWidget(montantWidget);
        montantContainer->setObjectName("montantContainer");
        layoutTotal = new QVBoxLayout(montantContainer);
        layoutTotal->setSpacing(5);
        layoutTotal->setObjectName("layoutTotal");
        layoutTotal->setContentsMargins(0, 0, 0, 0);
        captionMontant = new QLabel(montantContainer);
        captionMontant->setObjectName("captionMontant");

        layoutTotal->addWidget(captionMontant);

        labelMontant = new QLabel(montantContainer);
        labelMontant->setObjectName("labelMontant");

        layoutTotal->addWidget(labelMontant);


        layoutMontant->addWidget(montantContainer);


        layoutFacture->addWidget(montantWidget);

        qrWidget = new QFrame(factureForm);
        qrWidget->setObjectName("qrWidget");
        qrWidget->setFrameShape(QFrame::Shape::StyledPanel);
        qrWidget->setFrameShadow(QFrame::Shadow::Plain);
        layoutQR = new QVBoxLayout(qrWidget);
        layoutQR->setSpacing(5);
        layoutQR->setObjectName("layoutQR");
        layoutQR->setContentsMargins(12, 10, 12, 10);
        labelQRTitre = new QLabel(qrWidget);
        labelQRTitre->setObjectName("labelQRTitre");
        labelQRTitre->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutQR->addWidget(labelQRTitre);

        qrCodeLabel = new QLabel(qrWidget);
        qrCodeLabel->setObjectName("qrCodeLabel");
        qrCodeLabel->setMinimumSize(QSize(150, 150));
        qrCodeLabel->setMaximumSize(QSize(150, 150));
        qrCodeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutQR->addWidget(qrCodeLabel);

        labelQRNote = new QLabel(qrWidget);
        labelQRNote->setObjectName("labelQRNote");
        labelQRNote->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelQRNote->setWordWrap(true);

        layoutQR->addWidget(labelQRNote);


        layoutFacture->addWidget(qrWidget);

        layoutBoutons = new QHBoxLayout();
        layoutBoutons->setObjectName("layoutBoutons");
        spacerBoutons = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutBoutons->addItem(spacerBoutons);

        btnFermer = new QPushButton(factureForm);
        btnFermer->setObjectName("btnFermer");
        btnFermer->setMinimumSize(QSize(115, 42));

        layoutBoutons->addWidget(btnFermer);

        btnTelechargerPdf = new QPushButton(factureForm);
        btnTelechargerPdf->setObjectName("btnTelechargerPdf");
        btnTelechargerPdf->setMinimumSize(QSize(210, 42));

        layoutBoutons->addWidget(btnTelechargerPdf);


        layoutFacture->addLayout(layoutBoutons);


        retranslateUi(factureForm);

        QMetaObject::connectSlotsByName(factureForm);
    } // setupUi

    void retranslateUi(QDialog *factureForm)
    {
        factureForm->setWindowTitle(QCoreApplication::translate("factureForm", "Facture de location", nullptr));
        logo->setText(QCoreApplication::translate("factureForm", "Rent a car", nullptr));
        titre->setText(QCoreApplication::translate("factureForm", "FACTURE DE LOCATION", nullptr));
        soustitre->setText(QCoreApplication::translate("factureForm", "Rent a car \302\267 Fianarantsoa", nullptr));
        numeroFacture->setText(QCoreApplication::translate("factureForm", "FAC-2026-000123", nullptr));
        captionClient->setText(QCoreApplication::translate("factureForm", "CLIENT", nullptr));
        captionVoiture->setText(QCoreApplication::translate("factureForm", "V\303\211HICULE", nullptr));
        labelClient->setText(QCoreApplication::translate("factureForm", "Rakoto Andry", nullptr));
        labelVoiture->setText(QCoreApplication::translate("factureForm", "Toyota Corolla", nullptr));
        captionReferenceClient->setText(QCoreApplication::translate("factureForm", "R\303\251f\303\251rence client", nullptr));
        captionReferenceLocation->setText(QCoreApplication::translate("factureForm", "N\302\260 de location", nullptr));
        labelReferenceClient->setText(QCoreApplication::translate("factureForm", "0042", nullptr));
        labelReferenceLocation->setText(QCoreApplication::translate("factureForm", "123", nullptr));
        captionDateDebut->setText(QCoreApplication::translate("factureForm", "D\303\211BUT DE LOCATION", nullptr));
        captionDateFin->setText(QCoreApplication::translate("factureForm", "RETOUR PR\303\211VU", nullptr));
        labelDateDebut->setText(QCoreApplication::translate("factureForm", "01 novembre 2026", nullptr));
        labelDateFin->setText(QCoreApplication::translate("factureForm", "03 novembre 2026", nullptr));
        captionStatut->setText(QCoreApplication::translate("factureForm", "STATUT", nullptr));
        labelStatut->setText(QCoreApplication::translate("factureForm", "En cours", nullptr));
        captionMontant->setText(QCoreApplication::translate("factureForm", "MONTANT TOTAL", nullptr));
        labelMontant->setText(QCoreApplication::translate("factureForm", "270 000 Ar", nullptr));
        labelQRTitre->setText(QCoreApplication::translate("factureForm", "QR code de la facture", nullptr));
        qrCodeLabel->setText(QCoreApplication::translate("factureForm", "QR CODE", nullptr));
        labelQRNote->setText(QCoreApplication::translate("factureForm", "Scannez pour retrouver la r\303\251f\303\251rence de location.", nullptr));
        btnFermer->setText(QCoreApplication::translate("factureForm", "Fermer", nullptr));
        btnTelechargerPdf->setText(QCoreApplication::translate("factureForm", "T\303\251l\303\251charger en PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class factureForm: public Ui_factureForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACTUREFORM_H
