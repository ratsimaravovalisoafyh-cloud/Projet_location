#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFrame>
#include <QPixmap>
#include <QIcon>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QCoreApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

// Fonction pour initialiser la base de données SQLite
bool initialiserBase(QSqlDatabase &db)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString chemin = QCoreApplication::applicationDirPath() + "/location.db";
    db.setDatabaseName(chemin);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Erreur de connexion", "Impossible d'ouvrir la base de données :\n" + db.lastError().text());
        return false;
    }

    QSqlQuery query;
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS Clients (
            id_client INTEGER PRIMARY KEY AUTOINCREMENT,
            nom TEXT NOT NULL,
            telephone TEXT NOT NULL,
            email TEXT,
            adresse TEXT,
            numero_permis TEXT NOT NULL
        )
    )";

    if (!query.exec(sql)) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSqlDatabase db;
    if (!initialiserBase(db)) {
        return 1;
    }

    // =========================
    // FENÊTRE PRINCIPALE
    // =========================
    QWidget fenetre;
    fenetre.setWindowTitle("Rent & Go - Gestion de location de voitures");
    fenetre.setWindowIcon(QIcon(":/logo_clientlocation.png"));
    fenetre.resize(1280, 850);
    fenetre.setMinimumSize(1050, 750);

    // =========================================================================
    // STYLE GÉNÉRAL (DESIGN DASHBOARD EXACTEMENT COMME SUR LA CAPTURE D'ÉCRAN)
    // =========================================================================
    fenetre.setStyleSheet(R"(
        QWidget {
            background-color: #F1F5F9;
            color: #263F5C;
            font-family: "Segoe UI";
            font-size: 13px;
        }
        QFrame#carte {
            background-color: #FFFFFF;
            border: 1px solid #D8E2EF;
            border-radius: 10px;
        }
        QFrame#menuLateral {
            background-color: #1E293B;
            border-right: 1px solid #334155;
        }
        QFrame#barreSuperieure {
            background-color: #FFFFFF;
            border-bottom: 1px solid #E2E8F0;
        }
        QLabel#titreSection {
            color: #173F68;
            font-size: 15px;
            font-weight: bold;
            background: transparent;
            border: none;
        }
        QLabel#labelChamp {
            color: #263F5C;
            font-size: 12px;
            font-weight: bold;
            background: transparent;
            border: none;
        }
        QLineEdit {
            background-color: #FFFFFF;
            color: #263F5C;
            border: 1px solid #D8E2EF;
            border-radius: 6px;
            padding: 8px 12px;
            selection-background-color: #173F68;
            selection-color: #FFFFFF;
        }
        QLineEdit:focus {
            border: 1px solid #173F68;
        }
        QPushButton#boutonMenu {
            background-color: transparent;
            color: #94A3B8;
            border: none;
            border-radius: 6px;
            text-align: left;
            padding: 10px 15px;
            font-size: 13px;
        }
        QPushButton#boutonMenu:hover {
            background-color: #334155;
            color: #FFFFFF;
        }
        QPushButton#boutonMenuActif {
            background-color: #2563EB;
            color: #FFFFFF;
            border-left: 4px solid #93C5FD;
            border-radius: 4px;
            text-align: left;
            padding: 10px 15px;
            font-size: 13px;
            font-weight: bold;
        }
        QLabel#lienAction {
            color: #173F68;
            font-weight: bold;
            font-size: 13px;
            background: transparent;
            border: none;
        }
        QLabel#lienAction:hover {
            color: #2563EB;
            text-decoration: underline;
        }
        QTableWidget {
            background-color: #FFFFFF;
            alternate-background-color: #F8FAFC;
            color: #263F5C;
            border: 1px solid #D8E2EF;
            border-radius: 8px;
            gridline-color: #D8E2EF;
            selection-background-color: #D8E2EF;
            selection-color: #173F68;
        }
        QTableWidget::item {
            padding: 10px;
            color: #263F5C;
            background-color: #FFFFFF;
        }
        QTableWidget::item:alternate {
            background-color: #F8FAFC;
        }
        QHeaderView::section {
            background-color: #173F68;
            color: #FFFFFF;
            border: none;
            border-right: 1px solid #D8E2EF;
            padding: 10px 6px;
            font-weight: bold;
            font-size: 13px;
        }
        QTableCornerButton::section {
            background-color: #173F68;
            border: none;
        }
        QScrollBar:vertical {
            background-color: #F1F5F9;
            width: 8px;
            margin: 0;
        }
        QScrollBar::handle:vertical {
            background-color: #94A3B8;
            border-radius: 4px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0;
        }
    )");

    // =========================
    // LAYOUT GLOBAL PRINCIPAL (VERTICAL)
    // =========================
    QVBoxLayout *layoutPrincipalGlobal = new QVBoxLayout(&fenetre);
    layoutPrincipalGlobal->setContentsMargins(0, 0, 0, 0);
    layoutPrincipalGlobal->setSpacing(0);

    // =========================================================================
    // 1. BANDEAU SUPÉRIEUR GLOBAL (IDENTIQUE À LA CAPTURE D'ÉCRAN)
    // =========================================================================
    QFrame *barreSuperieure = new QFrame;
    barreSuperieure->setObjectName("barreSuperieure");
    barreSuperieure->setFixedHeight(70);

    QHBoxLayout *layoutBandeauTop = new QHBoxLayout(barreSuperieure);
    layoutBandeauTop->setContentsMargins(20, 0, 20, 0);

    // A. Logo (Gauche)
    QHBoxLayout *layoutLogoHaut = new QHBoxLayout();
    QLabel *iconeLogoHaut = new QLabel();
    QPixmap pixmapLogo(":/logo_clientlocation.png");
    if (!pixmapLogo.isNull()) {
        iconeLogoHaut->setPixmap(pixmapLogo.scaled(130, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        iconeLogoHaut->setText("🚗 Rent a Car");
        iconeLogoHaut->setStyleSheet("color: #173F68; font-weight: bold; font-size: 16px; background: transparent;");
    }
    layoutLogoHaut->addWidget(iconeLogoHaut);
    layoutLogoHaut->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    // B. Titre central épuré (Exactement comme sur l'image)
    QHBoxLayout *layoutTitreCentral = new QHBoxLayout();
    layoutTitreCentral->setAlignment(Qt::AlignCenter);
    QLabel *titreCentralHaut = new QLabel("GESTION DE LOCATION DE VOITURES");
    titreCentralHaut->setStyleSheet("color: #173F68; font-size: 14px; font-weight: bold; background: transparent; border: none;");
    layoutTitreCentral->addWidget(titreCentralHaut);

    // C. Date et icônes à droite (Style Dashboard)
    QHBoxLayout *layoutDroiteHaut = new QHBoxLayout();
    QLabel *sloganHaut = new QLabel("27 October 2026");
    sloganHaut->setStyleSheet("color: #64748B; font-size: 12px; background: transparent; border: none;");

    QLabel *iconeNotifHaut = new QLabel("🔔");
    iconeNotifHaut->setStyleSheet("font-size: 16px; background: transparent; border: none;");

    QLabel *iconeProfilHaut = new QLabel("👤");
    iconeProfilHaut->setStyleSheet("font-size: 16px; background: transparent; border: none;");

    layoutDroiteHaut->addWidget(sloganHaut);
    layoutDroiteHaut->addSpacing(15);
    layoutDroiteHaut->addWidget(iconeNotifHaut);
    layoutDroiteHaut->addWidget(iconeProfilHaut);
    layoutDroiteHaut->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    layoutBandeauTop->addLayout(layoutLogoHaut, 1);
    layoutBandeauTop->addLayout(layoutTitreCentral, 2);
    layoutBandeauTop->addLayout(layoutDroiteHaut, 1);

    layoutPrincipalGlobal->addWidget(barreSuperieure);

    // =========================================
    // 2. CORPS DE LA FENÊTRE (MENU + CONTENU)
    // =========================================
    QHBoxLayout *layoutCorps = new QHBoxLayout();
    layoutCorps->setContentsMargins(0, 0, 0, 0);
    layoutCorps->setSpacing(0);

    // --- MENU LATÉRAL (BLEU NUIT DU DASHBOARD) ---
    QFrame *menuLateral = new QFrame;
    menuLateral->setObjectName("menuLateral");
    menuLateral->setFixedWidth(220);

    QVBoxLayout *layoutMenu = new QVBoxLayout(menuLateral);
    layoutMenu->setContentsMargins(12, 20, 12, 20);
    layoutMenu->setSpacing(8);

    QPushButton *btnMenuDashboard = new QPushButton("   Dashboard");
    btnMenuDashboard->setObjectName("boutonMenu");
    btnMenuDashboard->setIcon(QIcon(":/images/rapport.png"));
    btnMenuDashboard->setIconSize(QSize(20, 20));

    QPushButton *btnMenuVoitures = new QPushButton("   Véhicules");
    btnMenuVoitures->setObjectName("boutonMenu");
    btnMenuVoitures->setIcon(QIcon(":/images/voiture.png"));
    btnMenuVoitures->setIconSize(QSize(20, 20));

    QPushButton *btnMenuClients = new QPushButton("   Clients");
    btnMenuClients->setObjectName("boutonMenuActif"); // Actif sur la page clients
    btnMenuClients->setIcon(QIcon(":/images/client.png"));
    btnMenuClients->setIconSize(QSize(20, 20));

    QPushButton *btnMenuLocations = new QPushButton("   Locations");
    btnMenuLocations->setObjectName("boutonMenu");
    btnMenuLocations->setIcon(QIcon(":/images/localisation.png"));
    btnMenuLocations->setIconSize(QSize(20, 20));

    QPushButton *btnMenuParametres = new QPushButton("   Paramètres");
    btnMenuParametres->setObjectName("boutonMenu");
    btnMenuParametres->setIcon(QIcon(":/images/parametres.png"));
    btnMenuParametres->setIconSize(QSize(20, 20));

    layoutMenu->addWidget(btnMenuDashboard);
    layoutMenu->addWidget(btnMenuVoitures);
    layoutMenu->addWidget(btnMenuClients);
    layoutMenu->addWidget(btnMenuLocations);
    layoutMenu->addWidget(btnMenuParametres);
    layoutMenu->addStretch();

    layoutCorps->addWidget(menuLateral);

    // --- ZONE CENTRALE DE CONTENU (DROITE) ---
    QWidget *zoneDroite = new QWidget;
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(zoneDroite);
    layoutPrincipal->setContentsMargins(20, 15, 20, 15);
    layoutPrincipal->setSpacing(15);

    // CARTE DU FORMULAIRE (Fond Blanc pur, Bordure #D8E2EF)
    QFrame *carteClientGlobal = new QFrame;
    carteClientGlobal->setObjectName("carte");
    QVBoxLayout *layoutCarteClient = new QVBoxLayout(carteClientGlobal);
    layoutCarteClient->setContentsMargins(15, 15, 15, 15);
    layoutCarteClient->setSpacing(15);

    QLabel *titreCarteClient = new QLabel("<img src=':/images/client.png' width='18' height='18'> &nbsp; <b>Gestion des informations et coordonnées du client</b>");
    titreCarteClient->setObjectName("titreSection");

    QGridLayout *grilleFormulaire = new QGridLayout;
    grilleFormulaire->setSpacing(10);

    QLineEdit *champNom = new QLineEdit;
    QLineEdit *champPermis = new QLineEdit;
    QLineEdit *champEmail = new QLineEdit;
    QLineEdit *champTelephone = new QLineEdit;
    QLineEdit *champAdresse = new QLineEdit;

    champNom->setPlaceholderText("Nom et prénom du client");
    champPermis->setPlaceholderText("Numéro de permis");
    champEmail->setPlaceholderText("exemple@email.com");
    champTelephone->setPlaceholderText("Numéro de téléphone");
    champAdresse->setPlaceholderText("Adresse du client");

    QLabel *lblNom = new QLabel("👤 Nom et prénom *");
    lblNom->setObjectName("labelChamp");
    QLabel *lblPermis = new QLabel("🪪 Numéro de permis *");
    lblPermis->setObjectName("labelChamp");
    QLabel *lblEmail = new QLabel("✉️ Email *");
    lblEmail->setObjectName("labelChamp");
    QLabel *lblTelephone = new QLabel("📞 Téléphone *");
    lblTelephone->setObjectName("labelChamp");
    QLabel *lblAdresse = new QLabel("📍 Adresse");
    lblAdresse->setObjectName("labelChamp");

    grilleFormulaire->addWidget(lblNom, 0, 0);
    grilleFormulaire->addWidget(champNom, 1, 0);
    grilleFormulaire->addWidget(lblPermis, 0, 1);
    grilleFormulaire->addWidget(champPermis, 1, 1);

    grilleFormulaire->addWidget(lblTelephone, 2, 0);
    grilleFormulaire->addWidget(champTelephone, 3, 0);
    grilleFormulaire->addWidget(lblEmail, 2, 1);
    grilleFormulaire->addWidget(champEmail, 3, 1);

    grilleFormulaire->addWidget(lblAdresse, 4, 0);
    grilleFormulaire->addWidget(champAdresse, 5, 0);

    // Liens d'actions en bas du formulaire
    QHBoxLayout *layoutLiensForm = new QHBoxLayout();
    layoutLiensForm->setSpacing(20);

    QLabel *lienAjouter = new QLabel("✨ AJOUTER");
    lienAjouter->setObjectName("lienAction");
    lienAjouter->setCursor(Qt::PointingHandCursor);

    QLabel *lienModifier = new QLabel("✏️ MODIFIER");
    lienModifier->setObjectName("lienAction");
    lienModifier->setCursor(Qt::PointingHandCursor);

    QLabel *lienSupprimer = new QLabel("🗑️ SUPPRIMER");
    lienSupprimer->setObjectName("lienAction");
    lienSupprimer->setCursor(Qt::PointingHandCursor);

    layoutLiensForm->addStretch();
    layoutLiensForm->addWidget(lienAjouter);
    layoutLiensForm->addWidget(lienModifier);
    layoutLiensForm->addWidget(lienSupprimer);

    layoutCarteClient->addWidget(titreCarteClient);
    layoutCarteClient->addLayout(grilleFormulaire);
    layoutCarteClient->addLayout(layoutLiensForm);

    layoutPrincipal->addWidget(carteClientGlobal);

    // SECTION TABLEAU DE LA LISTE DES PERSONNES & RECHERCHE
    QFrame *carteTableau = new QFrame;
    carteTableau->setObjectName("carte");
    QVBoxLayout *layoutTableauBox = new QVBoxLayout(carteTableau);
    layoutTableauBox->setContentsMargins(15, 15, 15, 15);
    layoutTableauBox->setSpacing(10);

    QHBoxLayout *layoutTitreRecherche = new QHBoxLayout;
    QLabel *titreTableau = new QLabel("<img src=':/images/rapport.png' width='16' height='16'> &nbsp; <b>Liste des personnes enregistrées</b>");
    titreTableau->setObjectName("titreSection");

    QLineEdit *champRecherche = new QLineEdit;
    champRecherche->setPlaceholderText("🔍  Rechercher un client...");
    champRecherche->setFixedWidth(280);

    layoutTitreRecherche->addWidget(titreTableau);
    layoutTitreRecherche->addStretch();
    layoutTitreRecherche->addWidget(champRecherche);

    QTableWidget *tableau = new QTableWidget;
    tableau->setColumnCount(6);
    tableau->setHorizontalHeaderLabels({
        "ID", "👤 Nom & Prénom", "📞 Téléphone", "✉️ Email", "📍 Adresse", "🪪 N° permis"
    });
    tableau->setColumnHidden(0, true);
    tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableau->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableau->setSelectionMode(QAbstractItemView::SingleSelection);
    tableau->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableau->setAlternatingRowColors(true);
    tableau->verticalHeader()->setVisible(false);

    layoutTableauBox->addLayout(layoutTitreRecherche);
    layoutTableauBox->addWidget(tableau);

    layoutPrincipal->addWidget(carteTableau, 2);

    layoutCorps->addWidget(zoneDroite, 1);
    layoutPrincipalGlobal->addLayout(layoutCorps);

    // =========================
    // FONCTION D'ACTUALISATION
    // =========================
    auto actualiser = [tableau](const QString &filtre = "") {
        QSqlQuery query;
        if (filtre.isEmpty()) {
            query.prepare("SELECT id_client, nom, telephone, email, adresse, numero_permis FROM Clients ORDER BY id_client DESC");
        } else {
            query.prepare("SELECT id_client, nom, telephone, email, adresse, numero_permis FROM Clients WHERE nom LIKE ? OR telephone LIKE ? ORDER BY id_client DESC");
            QString wildcard = "%" + filtre + "%";
            query.addBindValue(wildcard);
            query.addBindValue(wildcard);
        }

        if (!query.exec()) {
            QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
            return;
        }

        tableau->setRowCount(0);
        while (query.next()) {
            int ligne = tableau->rowCount();
            tableau->insertRow(ligne);
            for (int colonne = 0; colonne < 6; colonne++) {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(colonne).toString());
                tableau->setItem(ligne, colonne, item);
            }
        }
        tableau->setColumnHidden(0, true);
    };

    // ====================================================
    // CONNEXIONS DES ACTIONS (CLICS SUR LES LIENS TEXTUELS)
    // ====================================================

    auto actionAjouterLambda = [&]() {
        QString nom = champNom->text().trimmed();
        QString telephone = champTelephone->text().trimmed();
        QString email = champEmail->text().trimmed();
        QString adresse = champAdresse->text().trimmed();
        QString permis = champPermis->text().trimmed();

        if (nom.isEmpty() || telephone.isEmpty() || permis.isEmpty()) {
            QMessageBox::warning(&fenetre, "Champs obligatoires", "Veuillez remplir tous les champs obligatoires (*).");
            return;
        }

        QSqlQuery query;
        query.prepare("INSERT INTO Clients (nom, telephone, email, adresse, numero_permis) VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(nom);
        query.addBindValue(telephone);
        query.addBindValue(email);
        query.addBindValue(adresse);
        query.addBindValue(permis);

        if (!query.exec()) {
            QMessageBox::critical(&fenetre, "Erreur d'ajout", query.lastError().text());
            return;
        }

        actualiser(champRecherche->text());

        champNom->clear();
        champTelephone->clear();
        champEmail->clear();
        champAdresse->clear();
        champPermis->clear();
        champNom->setFocus();
    };

    auto actionModifierLambda = [&]() {
        int ligne = tableau->currentRow();
        if (ligne < 0) {
            QMessageBox::warning(&fenetre, "Aucune sélection", "Veuillez sélectionner un client dans le tableau à modifier.");
            return;
        }

        QTableWidgetItem *itemID = tableau->item(ligne, 0);
        if (!itemID) return;
        int id = itemID->text().toInt();

        QString nom = champNom->text().trimmed();
        QString telephone = champTelephone->text().trimmed();
        QString email = champEmail->text().trimmed();
        QString adresse = champAdresse->text().trimmed();
        QString permis = champPermis->text().trimmed();

        if (nom.isEmpty() || telephone.isEmpty() || permis.isEmpty()) {
            QMessageBox::warning(&fenetre, "Champs obligatoires", "Veuillez remplir tous les champs obligatoires (*).");
            return;
        }

        QSqlQuery query;
        query.prepare("UPDATE Clients SET nom = ?, telephone = ?, email = ?, adresse = ?, numero_permis = ? WHERE id_client = ?");
        query.addBindValue(nom);
        query.addBindValue(telephone);
        query.addBindValue(email);
        query.addBindValue(adresse);
        query.addBindValue(permis);
        query.addBindValue(id);

        if (!query.exec()) {
            QMessageBox::critical(&fenetre, "Erreur de modification", query.lastError().text());
            return;
        }

        actualiser(champRecherche->text());
        QMessageBox::information(&fenetre, "Succès", "Les informations du client ont été modifiées avec succès.");
    };

    auto actionSupprimerLambda = [&]() {
        int ligne = tableau->currentRow();
        if (ligne < 0) {
            QMessageBox::warning(&fenetre, "Aucune sélection", "Veuillez sélectionner un client dans le tableau à supprimer.");
            return;
        }

        QTableWidgetItem *itemID = tableau->item(ligne, 0);
        if (!itemID) return;
        int id = itemID->text().toInt();

        QMessageBox::StandardButton reponse = QMessageBox::question(
            &fenetre, "Confirmation", "Voulez-vous vraiment supprimer ce client ?",
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

        actualiser(champRecherche->text());
        champNom->clear();
        champTelephone->clear();
        champEmail->clear();
        champAdresse->clear();
        champPermis->clear();
    };

    struct ClickableLabelFilter : public QObject {
        std::function<void()> onClick;
        ClickableLabelFilter(std::function<void()> cb, QObject *parent) : QObject(parent), onClick(cb) {}
        bool eventFilter(QObject *obj, QEvent *ev) override {
            if (ev->type() == QEvent::MouseButtonPress) {
                onClick();
                return true;
            }
            return QObject::eventFilter(obj, ev);
        }
    };

    lienAjouter->installEventFilter(new ClickableLabelFilter(actionAjouterLambda, lienAjouter));
    lienModifier->installEventFilter(new ClickableLabelFilter(actionModifierLambda, lienModifier));
    lienSupprimer->installEventFilter(new ClickableLabelFilter(actionSupprimerLambda, lienSupprimer));

    QObject::connect(tableau, &QTableWidget::cellClicked, [&](int ligne, int) {
        QTableWidgetItem *itemNom = tableau->item(ligne, 1);
        QTableWidgetItem *itemTel = tableau->item(ligne, 2);
        QTableWidgetItem *itemEmail = tableau->item(ligne, 3);
        QTableWidgetItem *itemAdresse = tableau->item(ligne, 4);
        QTableWidgetItem *itemPermis = tableau->item(ligne, 5);

        if (itemNom) champNom->setText(itemNom->text());
        if (itemTel) champTelephone->setText(itemTel->text());
        if (itemEmail) champEmail->setText(itemEmail->text());
        if (itemAdresse) champAdresse->setText(itemAdresse->text());
        if (itemPermis) champPermis->setText(itemPermis->text());
    });

    QObject::connect(champRecherche, &QLineEdit::textChanged, [&](const QString &texte) {
        actualiser(texte);
    });

    actualiser();

    fenetre.show();
    return app.exec();
}