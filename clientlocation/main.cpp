#include <QGridLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFrame>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QCoreApplication>
#include <QDir>
#include <qapplication.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>


// Fonction pour créer la base de données
bool initialiserBase(QSqlDatabase &db)
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString chemin = QCoreApplication::applicationDirPath()
                     + "/location.db";

    db.setDatabaseName(chemin);

    if (!db.open()) {
        QMessageBox::critical(
            nullptr,
            "Erreur de connexion",
            "Impossible d'ouvrir la base de données :\n"
                + db.lastError().text()
            );

        return false;
    }

    QSqlQuery query;

    QString sql = R"(
        CREATE TABLE IF NOT EXISTS Clients (
            id_client INTEGER PRIMARY KEY AUTOINCREMENT,
            nom TEXT NOT NULL,
            prenom TEXT NOT NULL,
            telephone TEXT NOT NULL,
            email TEXT,
            adresse TEXT,
            numero_permis TEXT NOT NULL
        )
    )";

    if (!query.exec(sql)) {
        QMessageBox::critical(
            nullptr,
            "Erreur SQL",
            query.lastError().text()
            );

        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Connexion à SQLite
    QSqlDatabase db;

    if (!initialiserBase(db)) {
        return 1;
    }

    // =========================
    // FENÊTRE PRINCIPALE
    // =========================

    QWidget fenetre;
    fenetre.setWindowTitle("Gestion de location de voitures - Clients");

    fenetre.setWindowIcon(QIcon(":/logo_clientlocation.png"));

    fenetre.setWindowTitle(
        "Gestion de location de voitures - Clients"
        );

    fenetre.resize(1150, 850);
    fenetre.setMinimumSize(950, 700);

    // =========================
    // STYLE GÉNÉRAL (NOIR DOMINANT & VERT SAUGE DISCRET)
    // =========================

    fenetre.setStyleSheet(R"(

        QWidget {
            background-color: #0B0E0C;
            color: #E2EAE0;
            font-family: "Segoe UI";
            font-size: 14px;
        }

        QFrame#carte {
            background-color: #121714;
            border: 1px solid #243029;
            border-radius: 12px;
        }

        QLabel#titreSection {
            color: #98B590;
            font-size: 18px;
            font-weight: bold;
            background: transparent;
            border: none;
        }

        QLabel#labelChamp {
            color: #B8C8B4;
            font-size: 13px;
            font-weight: bold;
            background: transparent;
            border: none;
        }

        QLineEdit {
            background-color: #080B09;
            color: #FFFFFF;
            border: 1px solid #243029;
            border-radius: 6px;
            padding: 9px 12px;
            selection-background-color: #6C8566;
            selection-color: #080B09;
        }

        QLineEdit:focus {
            border: 1px solid #8FA889;
        }

        QPushButton {
            background-color: #556E51;
            color: #FFFFFF;
            border: 1px solid #728F6C;
            border-radius: 8px;
            padding: 11px 18px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #627D5E;
        }

        QPushButton:pressed {
            background-color: #445840;
        }

        /* Bouton Supprimer aux tons sombres/verts sans rouge */
        QPushButton#boutonSupprimer {
            background-color: #364235;
            border: 1px solid #4F5E4C;
        }

        QPushButton#boutonSupprimer:hover {
            background-color: #425041;
        }

        QTableWidget {
            background-color: #080B09;
            alternate-background-color: #0E1310;
            color: #E2EAE0;
            border: 1px solid #243029;
            border-radius: 8px;
            gridline-color: #1A241F;
            selection-background-color: #445840;
            selection-color: white;
            font-size: 14px;
        }

        QTableWidget::item {
            padding: 12px 10px;
        }

        QHeaderView::section {
            background-color: #18221D;
            color: #98B590;
            border: none;
            border-right: 1px solid #243029;
            padding: 12px 6px;
            font-weight: bold;
            font-size: 14px;
        }

        QTableCornerButton::section {
            background-color: #18221D;
            border: none;
        }

        QScrollBar:vertical {
            background-color: #0B0E0C;
            width: 10px;
            margin: 0;
        }

        QScrollBar::handle:vertical {
            background-color: #556E51;
            border-radius: 5px;
            min-height: 25px;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0;
        }

    )");

    // =========================
    // LAYOUT PRINCIPAL
    // =========================

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(&fenetre);

    layoutPrincipal->setContentsMargins(20, 15, 20, 15);
    layoutPrincipal->setSpacing(12);

    // =========================
    // BANDEAU SUPÉRIEUR (LOGO + TITRE + SLOGAN)
    // =========================

    QFrame *bandeau = new QFrame;
    bandeau->setObjectName("carte");

    QHBoxLayout *layoutBandeau = new QHBoxLayout(bandeau);
    layoutBandeau->setContentsMargins(20, 15, 20, 15);

    // 1. Logo voiture (Gauche)
    QLabel *logoGauche = new QLabel;
    logoGauche->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QPixmap imageLogo(":/logo_clientlocation.png");
    if (!imageLogo.isNull()) {
        logoGauche->setPixmap(imageLogo.scaled(110, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        logoGauche->setText("🚗");
        logoGauche->setStyleSheet("font-size: 36px; background: transparent; color: #98B590;");
    }

    // 2. Titre central stylisé
    QVBoxLayout *layoutTitreCentre = new QVBoxLayout();
    layoutTitreCentre->setSpacing(2);
    layoutTitreCentre->setAlignment(Qt::AlignCenter);

    QLabel *titrePrincipal = new QLabel("GESTION DE LOCATION DE VOITURES");
    titrePrincipal->setAlignment(Qt::AlignCenter);
    titrePrincipal->setStyleSheet("color: #FFFFFF; font-size: 22px; font-weight: bold; background: transparent; border: none;");

    QLabel *sousTitreClients = new QLabel("Clients");
    sousTitreClients->setAlignment(Qt::AlignCenter);
    sousTitreClients->setStyleSheet("color: #98B590; font-style: italic; font-size: 15px; background: transparent; border: none;");

    layoutTitreCentre->addWidget(titrePrincipal);
    layoutTitreCentre->addWidget(sousTitreClients);

    // 3. Slogan (Droite)
    QLabel *sloganDroite = new QLabel("Votre mobilité, notre priorité");
    sloganDroite->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sloganDroite->setStyleSheet("color: #98B590; font-style: italic; font-size: 14px; background: transparent; border: none;");

    layoutBandeau->addWidget(logoGauche, 1);
    layoutBandeau->addLayout(layoutTitreCentre, 3);
    layoutBandeau->addWidget(sloganDroite, 1);

    layoutPrincipal->addWidget(bandeau);

    // =========================
    // CARTE FORMULAIRE
    // =========================

    QFrame *carteFormulaire = new QFrame;
    carteFormulaire->setObjectName("carte");

    QVBoxLayout *layoutFormulaire = new QVBoxLayout(carteFormulaire);
    layoutFormulaire->setContentsMargins(20, 15, 20, 15);
    layoutFormulaire->setSpacing(12);

    QGridLayout *grille = new QGridLayout;
    grille->setHorizontalSpacing(20);
    grille->setVerticalSpacing(10);

    // Champs du formulaire
    QLineEdit *champNom = new QLineEdit;
    QLineEdit *champPrenom = new QLineEdit;
    QLineEdit *champTelephone = new QLineEdit;
    QLineEdit *champEmail = new QLineEdit;
    QLineEdit *champAdresse = new QLineEdit;
    QLineEdit *champPermis = new QLineEdit;

    champNom->setPlaceholderText("Nom du client");
    champPrenom->setPlaceholderText("Prénom du client");
    champTelephone->setPlaceholderText("Téléphone");
    champEmail->setPlaceholderText("exemple@email.com");
    champAdresse->setPlaceholderText("Adresse du client");
    champPermis->setPlaceholderText("Numéro du permis");

    // Libellés avec icônes textuelles intégrées (Émojis)
    QLabel *labelNom = new QLabel("👤   Nom :");
    QLabel *labelPrenom = new QLabel("👤   Prénom :");
    QLabel *labelTelephone = new QLabel("📞   Téléphone :");
    QLabel *labelEmail = new QLabel("✉️   Email :");
    QLabel *labelAdresse = new QLabel("📍   Adresse :");
    QLabel *labelPermis = new QLabel("📄   Numéro de permis :");

    QList<QLabel*> labels = {labelNom, labelPrenom, labelTelephone, labelEmail, labelAdresse, labelPermis};
    for (QLabel *label : labels) {
        label->setObjectName("labelChamp");
    }

    // Organisation sur deux colonnes de la grille
    grille->addWidget(labelNom, 0, 0);
    grille->addWidget(champNom, 1, 0);

    grille->addWidget(labelPrenom, 0, 1);
    grille->addWidget(champPrenom, 1, 1);

    grille->addWidget(labelTelephone, 2, 0);
    grille->addWidget(champTelephone, 3, 0);

    grille->addWidget(labelEmail, 2, 1);
    grille->addWidget(champEmail, 3, 1);

    grille->addWidget(labelAdresse, 4, 0);
    grille->addWidget(champAdresse, 5, 0);

    grille->addWidget(labelPermis, 4, 1);
    grille->addWidget(champPermis, 5, 1);

    grille->setColumnStretch(0, 1);
    grille->setColumnStretch(1, 1);

    layoutFormulaire->addLayout(grille);

    // =========================
    // BOUTONS D'ACTION
    // =========================

    QHBoxLayout *layoutBoutons = new QHBoxLayout;
    layoutBoutons->setSpacing(15);

    QPushButton *boutonAjouter = new QPushButton("➕   Ajouter le client");
    QPushButton *boutonSupprimer = new QPushButton("🗑️   Supprimer le client");
    boutonSupprimer->setObjectName("boutonSupprimer");

    layoutBoutons->addWidget(boutonAjouter);
    layoutBoutons->addWidget(boutonSupprimer);

    layoutFormulaire->addLayout(layoutBoutons);
    layoutPrincipal->addWidget(carteFormulaire);

    // =========================
    // TABLEAU DES CLIENTS
    // =========================

    QFrame *carteTableau = new QFrame;
    carteTableau->setObjectName("carte");

    QVBoxLayout *layoutTableau = new QVBoxLayout(carteTableau);
    layoutTableau->setContentsMargins(15, 15, 15, 15);
    layoutTableau->setSpacing(10);

    // En-tête de section tableau avec icône voiture à droite
    QHBoxLayout *layoutTitreTableauBox = new QHBoxLayout();
    QLabel *titreTableau = new QLabel("👥  LISTE DES CLIENTS");
    titreTableau->setObjectName("titreSection");

    QLabel *iconeVoitureTableau = new QLabel("🚗");
    iconeVoitureTableau->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    iconeVoitureTableau->setStyleSheet("font-size: 22px; background: transparent; color: #98B590;");

    layoutTitreTableauBox->addWidget(titreTableau);
    layoutTitreTableauBox->addStretch();
    layoutTitreTableauBox->addWidget(iconeVoitureTableau);

    QTableWidget *tableau = new QTableWidget;
    tableau->setColumnCount(7);

    // En-têtes de colonnes accompagnés de leurs icônes respectives
    tableau->setHorizontalHeaderLabels({
        "ID",
        "👤  Nom",
        "👤  Prénom",
        "📞  Téléphone",
        "✉️  Email",
        "📍  Adresse",
        "📄  N° permis"
    });

    tableau->setColumnHidden(0, true);
    tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableau->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableau->setSelectionMode(QAbstractItemView::SingleSelection);
    tableau->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableau->setAlternatingRowColors(true);
    tableau->verticalHeader()->setVisible(false);

    layoutTableau->addLayout(layoutTitreTableauBox);
    layoutTableau->addWidget(tableau);

    layoutPrincipal->addWidget(carteTableau, 2);

    // =========================
    // FONCTION D'ACTUALISATION
    // =========================

    auto actualiser = [tableau]() {
        QSqlQuery query;
        query.prepare(R"(
            SELECT
                id_client,
                nom,
                prenom,
                telephone,
                email,
                adresse,
                numero_permis
            FROM Clients
            ORDER BY id_client DESC
        )");

        if (!query.exec()) {
            QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
            return;
        }

        tableau->setRowCount(0);

        while (query.next()) {
            int ligne = tableau->rowCount();
            tableau->insertRow(ligne);

            for (int colonne = 0; colonne < 7; colonne++) {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(colonne).toString());
                tableau->setItem(ligne, colonne, item);
            }
        }
        tableau->setColumnHidden(0, true);
    };

    // =========================
    // CONNEXIONS / SLOTS
    // =========================

    QObject::connect(boutonAjouter, &QPushButton::clicked, [&]() {
        QString nom = champNom->text().trimmed();
        QString prenom = champPrenom->text().trimmed();
        QString telephone = champTelephone->text().trimmed();
        QString email = champEmail->text().trimmed();
        QString adresse = champAdresse->text().trimmed();
        QString permis = champPermis->text().trimmed();

        if (nom.isEmpty() || prenom.isEmpty() || telephone.isEmpty() || permis.isEmpty()) {
            QMessageBox::warning(&fenetre, "Champs obligatoires", "Remplis le nom, le prénom, le téléphone et le numéro de permis.");
            return;
        }

        QSqlQuery query;
        query.prepare(R"(
            INSERT INTO Clients (nom, prenom, telephone, email, adresse, numero_permis)
            VALUES (?, ?, ?, ?, ?, ?)
        )");

        query.addBindValue(nom);
        query.addBindValue(prenom);
        query.addBindValue(telephone);
        query.addBindValue(email);
        query.addBindValue(adresse);
        query.addBindValue(permis);

        if (!query.exec()) {
            QMessageBox::critical(&fenetre, "Erreur d'ajout", query.lastError().text());
            return;
        }

        actualiser();

        champNom->clear();
        champPrenom->clear();
        champTelephone->clear();
        champEmail->clear();
        champAdresse->clear();
        champPermis->clear();
        champNom->setFocus();

        QMessageBox::information(&fenetre, "Succès", "Le client a été ajouté avec succès !");
    });

    QObject::connect(boutonSupprimer, &QPushButton::clicked, [&]() {
        int ligne = tableau->currentRow();
        if (ligne < 0) {
            QMessageBox::warning(&fenetre, "Aucune sélection", "Sélectionne un client dans le tableau.");
            return;
        }

        QTableWidgetItem *itemID = tableau->item(ligne, 0);
        if (!itemID) return;

        int id = itemID->text().toInt();

        QMessageBox::StandardButton reponse = QMessageBox::question(
            &fenetre, "Confirmation", "Veux-tu vraiment supprimer ce client ?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reponse != QMessageBox::Yes) return;

        QSqlQuery query;
        query.prepare("DELETE FROM Clients WHERE id_client = ?");
        query.addBindValue(id);

        if (!query.exec()) {
            QMessageBox::critical(&fenetre, "Erreur de suppression", query.lastError().text());
            return;
        }

        actualiser();
        QMessageBox::information(&fenetre, "Succès", "Le client a été supprimé.");
    });

    // Initialisation du tableau au démarrage
    actualiser();

    fenetre.show();

    return app.exec();
}
