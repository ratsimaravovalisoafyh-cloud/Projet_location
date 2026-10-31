#include "factureform.h"
#include "ui_factureform.h"
#include "qrcodegenerator.h"

#include <QDate>
#include <QLocale>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFileInfo>
#include <QLabel>
#include <QPrinter>
#include <QTextDocument>
#include <QPageSize>
#include <QPageLayout>
#include <QMarginsF>
#include <QPixmap>
#include <QUrl>

factureForm::factureForm(QWidget *parent, int idLocation)
    : QDialog(parent)
    , ui(new Ui::factureForm)
    , m_idLocation(idLocation)

{
    ui->setupUi(this);

    chargerFacture();

    connect(ui->btnFermer, &QPushButton::clicked,
            this, &QDialog::accept);

    connect(ui->btnTelechargerPdf, &QPushButton::clicked,
            this, &factureForm::telechargerPdf);
}

factureForm::~factureForm()
{
    delete ui;
}


void factureForm::chargerFacture()
{
    QSqlQuery query;

    query.prepare(
        "SELECT l.id_location, l.id_client, c.nom, "
        "CONCAT(v.marque, ' ', v.modele) AS voiture, "
        "l.date_debut, l.date_fin, "
        "l.montant_total, l.statut_location "
        "FROM locations l "
        "JOIN clients c ON c.id_client = l.id_client "
        "JOIN voitures v ON v.id_voiture = l.id_voiture "
        "WHERE l.id_location = :id");

    query.bindValue(":id", m_idLocation);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(
            this,
            "Erreur",
            "Impossible de charger les données de la facture :\n"
                + query.lastError().text());
        return;
    }

    const int idClient = query.value("id_client").toInt();
    const QString nomClient = query.value("nom").toString();
    const QString nomVoiture = query.value("voiture").toString();
    const QDate dateDebut = query.value("date_debut").toDate();
    const QDate dateFin = query.value("date_fin").toDate();
    const double montant = query.value("montant_total").toDouble();
    const QString statut = query.value("statut_location").toString();

    ui->logo->setText("Rent a car");
    ui->titre->setText("FACTURE DE LOCATION");
    ui->soustitre->setText("Rent a car · Fianarantsoa");

    const QString numero =
        QString("FAC-%1-%2")
            .arg(dateDebut.year())
            .arg(m_idLocation, 6, 10, QChar('0'));

    ui->numeroFacture->setText(numero);
    ui->labelReferenceLocation->setText(QString::number(m_idLocation));
    ui->labelReferenceClient->setText(QString::number(idClient));
    ui->labelClient->setText(nomClient);
    ui->labelVoiture->setText(nomVoiture);
    ui->labelDateDebut->setText(dateDebut.toString("dd/MM/yyyy"));
    ui->labelDateFin->setText(dateFin.toString("dd/MM/yyyy"));
    ui->labelStatut->setText(statut);

    const QLocale francais(QLocale::French);
    ui->labelMontant->setText(
        francais.toString(montant, 'f', 0) + " Ar");

    // Le QR code contient la référence lisible de la facture.
    const QImage qr = creerImageQrFacture(numero);
    if (qr.isNull()) {
        ui->qrCodeLabel->setText("QR indisponible");
    } else {
        ui->qrCodeLabel->setText(QString());
        ui->qrCodeLabel->setPixmap(QPixmap::fromImage(qr));
    }
    ui->labelQRNote->setText(
        "Scannez pour lire la référence de cette facture.");
}

void factureForm::telechargerPdf()
{
    QString chemin = QFileDialog::getSaveFileName(
        this,
        "Enregistrer la facture",
        ui->numeroFacture->text() + ".pdf",
        "Fichiers PDF (*.pdf)");

    if (chemin.isEmpty())
        return;

    if (!chemin.endsWith(".pdf", Qt::CaseInsensitive))
        chemin += ".pdf";

    QPrinter imprimante(QPrinter::HighResolution);
    imprimante.setOutputFormat(QPrinter::PdfFormat);
    imprimante.setOutputFileName(chemin);
    imprimante.setPageSize(QPageSize(QPageSize::A4));
    imprimante.setPageMargins(QMarginsF(14, 14, 14, 14), QPageLayout::Millimeter);

    const QString numero = ui->numeroFacture->text().toHtmlEscaped();
    const QString client = ui->labelClient->text().toHtmlEscaped();
    const QString voiture = ui->labelVoiture->text().toHtmlEscaped();
    const QString debut = ui->labelDateDebut->text().toHtmlEscaped();
    const QString fin = ui->labelDateFin->text().toHtmlEscaped();
    const QString statut = ui->labelStatut->text().toHtmlEscaped();
    const QString montant = ui->labelMontant->text().toHtmlEscaped();

    const QString referenceClient =
        ui->labelReferenceClient->text().toHtmlEscaped();
    const QString referenceLocation =
        ui->labelReferenceLocation->text().toHtmlEscaped();
    const QImage qr = creerImageQrFacture(ui->numeroFacture->text());
    if (qr.isNull()) {
        QMessageBox::critical(this, "Erreur QR",
                              "Le QR code de cette référence n'a pas pu être généré.");
        return;
    }

    // Mise en page en tableaux simples : QTextDocument les imprime de façon
    const QString html = QStringLiteral(R"HTML(
<html><head><meta charset="utf-8"></head>
<body style="font-family:Arial; color:#193F63; font-size:10pt;">
<table width="100%" cellspacing="0" cellpadding="14" bgcolor="#183B5E">
 <tr>
  <td width="65%"><font color="#FFFFFF" size="5"><b>Rent a car</b></font><br>
   <font color="#D7E9FC" size="2">Fianarantsoa · Gestion de location</font></td>
  <td width="35%" align="right"><font color="#FFFFFF" size="4"><b>FACTURE DE LOCATION</b></font><br>
   <font color="#D7E9FC" size="2">%1</font></td>
 </tr>
</table>
<br>
<font color="#71869A" size="2"><b>INFORMATIONS DE LA LOCATION</b></font><br><br>
<table width="100%" cellspacing="0" cellpadding="12" border="1" bordercolor="#D3E1EF" bgcolor="#F5F9FE">
 <tr>
  <td width="50%"><font color="#71869A" size="2"><b>CLIENT</b></font><br><br>
   <font color="#193F63" size="4"><b>%2</b></font><br><br>
   <font color="#71869A" size="2">Référence client : </font><b>%4</b></td>
  <td width="50%"><font color="#71869A" size="2"><b>VÉHICULE</b></font><br><br>
   <font color="#193F63" size="4"><b>%3</b></font><br><br>
   <font color="#71869A" size="2">N° de location : </font><b>%5</b></td>
 </tr>
</table>
<br>
<table width="100%" cellspacing="0" cellpadding="12" border="1" bordercolor="#D3E1EF" bgcolor="#FFFFFF">
 <tr>
  <td width="50%"><font color="#71869A" size="2"><b>DÉBUT DE LOCATION</b></font><br><br>
   <font color="#193F63" size="4"><b>%6</b></font></td>
  <td width="50%"><font color="#71869A" size="2"><b>RETOUR PRÉVU</b></font><br><br>
   <font color="#193F63" size="4"><b>%7</b></font></td>
 </tr>
</table>
<br>
<table width="100%" cellspacing="0" cellpadding="12" bgcolor="#D7E9FB">
 <tr>
  <td width="50%"><font color="#71869A" size="2"><b>STATUT</b></font><br><br>
   <font color="#193F63" size="3"><b>%8</b></font></td>
  <td width="50%" align="right"><font color="#71869A" size="2"><b>MONTANT TOTAL</b></font><br><br>
   <font color="#193F63" size="5"><b>%9</b></font></td>
 </tr>
</table>
<br>
<table width="100%" cellspacing="0" cellpadding="8" border="1" bordercolor="#D3E1EF" bgcolor="#FFFFFF">
 <tr><td align="center">
  <font color="#193F63" size="3"><b>QR code de la facture</b></font><br><br>
  <img src="invoice-qr" width="145" height="145"><br>
  <font color="#71869A" size="2">Scannez pour lire la référence de cette facture : %1</font>
 </td></tr>
</table>
<br><font color="#71869A" size="2">Document généré par Rent a car · Fianarantsoa</font>
</body></html>
)HTML").arg(numero, client, voiture, referenceClient, referenceLocation,
              debut, fin, statut, montant);
    QTextDocument document;
    document.addResource(QTextDocument::ImageResource, QUrl("invoice-qr"), qr);
    document.setHtml(html);
    document.print(&imprimante);

    if (QFileInfo::exists(chemin) && QFileInfo(chemin).size() > 0) {
        QMessageBox::information(
            this,
            "Facture enregistrée",
            "Le PDF a été enregistré ici :\n" + chemin);
    } else {
        QMessageBox::critical(
            this,
            "Erreur",
            "Le fichier PDF n’a pas pu être créé.");
    }
}
