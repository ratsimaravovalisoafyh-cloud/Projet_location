#include "locationsForm.h"
#include "ui_locationsForm.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QVariant>//permet de manipuler plsr valeur de diff types
#include <QDate>
#include <QDateEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QDebug>


locationsForm::locationsForm(QWidget *parent, int idLocation)
    : QDialog(parent)
    , ui(new Ui::locationsForm)
    , m_idLocation(idLocation)
{
    ui->setupUi(this);

    //permet de charger les clients et voitures depuis mysql
    Clients();
    Voitures();

    ui->dateDebut->setDate(QDate::currentDate());
    ui->dateFin->setDate(QDate::currentDate().addDays(1));

    if (m_idLocation != -1) {
        chargementLocationPourModif();
    } else {
        ui->dateDebut->setDate(QDate::currentDate());
        ui->dateFin->setDate(QDate::currentDate().addDays(1));
    }


    connect(ui->comboVoiture,
            QOverload<int>::of(&QComboBox::currentIndexChanged), //transmet l'id de l'element selctionné (int)
            this,
            [this](int) {
                calculMontant();
            });

    connect(ui->dateDebut,
            &QDateEdit::dateChanged,
            this,
            [this](const QDate &) {
                calculMontant();
            });

    connect(ui->dateFin,
            &QDateEdit::dateChanged,
            this,
            [this](const QDate &) {
                calculMontant();
            });

    // Boutons
    connect(ui->btnSave,
            &QPushButton::clicked,
            this,
            [this]() {
                enregistrerLocation();
            });

    connect(ui->btnAnnuler,
            &QPushButton::clicked,
            this,
            &QDialog::reject);

        calculMontant();
}

locationsForm::~locationsForm()
{
    delete ui;
}

void locationsForm::Clients()
{
    QSqlQuery query;

    if(!query.exec(
            "SELECT id_client, nom "
            "FROM clients "
            "ORDER BY nom")) {

        QMessageBox::critical(
            this,
            "Erreur Sql",
            "Impossible de charger les clients:\n"
                + query.lastError().text()
        );
        return;
    }

    ui->comboClient->clear();

    ui->comboClient->addItem(
         "Sélectionner un client",
         QVariant()
    );

    while (query.next()){
        int id = query.value("id_client").toInt();

        QString nom = query.value("nom").toString();

        ui->comboClient->addItem(nom, id);

    }
}

void locationsForm::Voitures()
{
    QSqlQuery query;

    if (!query.exec(
            "SELECT id_voiture, marque, modele, prix_journalier "
            "FROM voitures "
            "ORDER BY marque, modele")) {
        QMessageBox::critical(
            this,
            "Erreur Sql",
            "Impossible de charger les voitures:\n"
                + query.lastError().text()
        );
        return;
    }
    ui->comboVoiture->clear();

    ui->comboVoiture->addItem(
        "Sélectionner une voiture",
        QVariant()
        );

    while (query.next()) {
        int id = query.value("id_voiture").toInt();
        QString marque = query.value("marque").toString();
        QString modele = query.value("modele").toString();
        QString nomVoiture = marque + " " + modele;

        ui->comboVoiture->addItem(
            nomVoiture,
            id);
    }

}


// Récupérer le tarif journalier
double locationsForm::tarifJournalier(int idVoiture)
{
    QSqlQuery query;

    query.prepare(
        "SELECT prix_journalier "
        "FROM voitures "
        "WHERE id_voiture = :id");

    query.bindValue(":id", idVoiture);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(
            this,
            "Erreur SQL",
            "Impossible de récupérer le tarif :\n"
                + query.lastError().text());
        return -1.0;
    }

    return query.value(0).toDouble();
}


void locationsForm::calculMontant()
{
    int idVoiture = ui->comboVoiture->currentData().toInt();

    if (ui->comboVoiture->currentIndex() <= 0) {
        ui->labelMontant->setText(
            "Montant total estimé : 0 Ar");
        return;
    }

    QDate debut = ui->dateDebut->date();
    QDate fin = ui->dateFin->date();

    if (fin < debut) {
        ui->labelMontant->setText(
            "Dates invalides");
        return;
    }

    double tarif = tarifJournalier(idVoiture);

    if (tarif < 0) {
        ui->labelMontant->setText(
            "Tarif indisponible");
        return;
    }

    int nombreJours = debut.daysTo(fin) + 1; //mznomboka 0 fona ny index d'où + 1

    double montant = nombreJours * tarif;

    ui->labelMontant->setText(
        "Montant total estimé : "
        + QString::number(montant, 'f', 2) //montant avec précision 2 chiffres après virgule
        + " Ar");
}

void locationsForm::chargementLocationPourModif()
{
    QSqlQuery query;
    query.prepare(
        "SELECT id_client, id_voiture, date_debut, date_fin "
        "FROM locations WHERE id_location = :id");
    query.bindValue(":id", m_idLocation);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(
            this, "Erreur",
            "Impossible de charger cette location :\n"
                + query.lastError().text());
        reject();
        return;
    }

    const int idClient = query.value("id_client").toInt();
    const int idVoiture = query.value("id_voiture").toInt();
    m_ancienneVoitureId = idVoiture;

    ui->comboClient->setCurrentIndex(
        ui->comboClient->findData(idClient));

    //par précaution
    // La voiture associée peut ne plus être marquée disponible.
    // On l’ajoute au formulaire si elle n’est pas déjà dans la liste.
    int indexVoiture = ui->comboVoiture->findData(idVoiture);
    if (indexVoiture < 0) {
        QSqlQuery voiture;
        voiture.prepare(
            "SELECT marque, modele FROM voitures "
            "WHERE id_voiture = :id");
        voiture.bindValue(":id", idVoiture);

        if (voiture.exec() && voiture.next()) { //execution
            const QString nom =
                voiture.value("marque").toString() + " "
                + voiture.value("modele").toString();

            ui->comboVoiture->addItem(nom, idVoiture);
            indexVoiture = ui->comboVoiture->count() - 1;
        }
    }
    ui->comboVoiture->setCurrentIndex(indexVoiture);

    ui->dateDebut->setDate(query.value("date_debut").toDate());
    ui->dateFin->setDate(query.value("date_fin").toDate());
}

void locationsForm::enregistrerLocation()
{
    // Vérification an'le client
    if (ui->comboClient->currentIndex() <= 0) {
        QMessageBox::warning(
            this,
            "Information manquante",
            "Veuillez sélectionner un client.");
        return;
    }

    // Vérification  voiture
    if (ui->comboVoiture->currentIndex() <= 0) {
        QMessageBox::warning(
            this,
            "Information manquante",
            "Veuillez sélectionner une voiture.");
        return;
    }

    int idClient = ui->comboClient->currentData().toInt();
    int idVoiture = ui->comboVoiture->currentData().toInt();

    QDate debut = ui->dateDebut->date();
    QDate fin = ui->dateFin->date();

    // Vérification des dates
    if (fin < debut) {
        QMessageBox::warning(
            this,
            "Dates invalides",
            "La date de retour doit être égale ou postérieure "
            "à la date de début.");
        return;
    }

    QSqlQuery conflit;
    QString sql =
        "SELECT COUNT(*) "
        "FROM locations "
        "WHERE id_voiture = :id "
        "AND statut_location NOT IN ('Annulée', 'Terminée') "
        "AND date_debut <= :fin "
        "AND date_fin >= :debut";

    if (m_idLocation != -1) {
        sql += " AND id_location <> :idLocation";
    }

    conflit.prepare(sql);
    conflit.bindValue(":id", idVoiture);
    conflit.bindValue(":debut", debut.toString("yyyy-MM-dd"));
    conflit.bindValue(":fin", fin.toString("yyyy-MM-dd"));

    if (m_idLocation != -1) {
        conflit.bindValue(":idLocation", m_idLocation);
    }

    if (!conflit.exec() || !conflit.next()) {
        QMessageBox::critical(
            this,
            "Erreur SQL",
            "Impossible de vérifier la disponibilité :\n"
                + conflit.lastError().text());
        return;
    }

    if (conflit.value(0).toInt() > 0) {
        QMessageBox::warning(
            this,
            "Voiture indisponible",
            "Cette voiture possède déjà une location "
            "sur la période choisie.");
        return;
    }


    double tarif = tarifJournalier(idVoiture);

    if (tarif < 0) {
        return;
    }

    int nombreJours = debut.daysTo(fin) + 1;
    double montant = nombreJours * tarif;

    // Insérer ou modifier la location dans MySQL
    QSqlQuery enregistrement;

    if (m_idLocation == -1) {
        enregistrement.prepare(
            "INSERT INTO locations "
            "(id_client, id_voiture, date_debut, date_fin, "
            "montant_total, statut_location) "
            "VALUES (:client, :voiture, :debut, :fin, "
            ":montant, 'En cours')");
    } else { //pour modification
        enregistrement.prepare(
            "UPDATE locations SET "
            "id_client = :client, "
            "id_voiture = :voiture, "
            "date_debut = :debut, "
            "date_fin = :fin, "
            "montant_total = :montant "
            "WHERE id_location = :id");
        enregistrement.bindValue(":id", m_idLocation);
    }

    enregistrement.bindValue(":client", idClient);
    enregistrement.bindValue(":voiture", idVoiture);
    enregistrement.bindValue(":debut", debut.toString("yyyy-MM-dd"));
    enregistrement.bindValue(":fin", fin.toString("yyyy-MM-dd"));
    enregistrement.bindValue(":montant", montant);

    if (!enregistrement.exec()) {
        QMessageBox::critical(
            this, "Erreur SQL",
            "Impossible d'enregistrer la location :\n"
                + enregistrement.lastError().text());
        return;
    }

    if (m_idLocation == -1) {
        m_locationIdEnregistree = enregistrement.lastInsertId().toInt();
    } else {
        m_locationIdEnregistree = m_idLocation;
    }


    auto synchroniserStatutVoiture = [this](int id) {
        if (id <= 0)
            return true;

        QSqlQuery majVoiture;
        majVoiture.prepare(
            "UPDATE voitures "
            "SET statut_disponibilite = CASE "
            "    WHEN EXISTS ("
            "        SELECT 1 FROM locations "
            "        WHERE locations.id_voiture = voitures.id_voiture "
            "          AND locations.statut_location = 'En cours'"
            "    ) THEN 'Louée' "
            "    ELSE 'Disponible' "
            "END "

            "WHERE id_voiture = :id"
            );
        majVoiture.bindValue(":id", id);

        if (!majVoiture.exec()) {
            QMessageBox::critical(
                this,
                "Erreur SQL",
                "La location est enregistrée, mais le statut de la voiture "
                "n'a pas pu être synchronisé :\n"
                    + majVoiture.lastError().text());
            return false;
        }

        return true;
    };

    if (!synchroniserStatutVoiture(idVoiture))
        return;

    if (m_idLocation != -1 && m_ancienneVoitureId != idVoiture) {
        if (!synchroniserStatutVoiture(m_ancienneVoitureId))
            return;
    }

    QMessageBox::information(
        this, "Succès",
        m_idLocation == -1
            ? "La location a été créée."
            : "La location a été modifiée.");


    accept(); //ferme le dialog en indiquant oevalidé
}

int locationsForm::locationIdEnregistree() const
{
    return m_locationIdEnregistree;
}



