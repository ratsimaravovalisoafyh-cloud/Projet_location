#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "locationsForm.h"
#include <QPushButton>
#include <QResizeEvent>
#include <QHeaderView>
#include <QMenu>
#include <QAction>
#include <QItemSelectionModel>
#include <QSqlRecord>
#include <QAbstractItemView>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QDateEdit>
#include <utility>
#include <QLabel>
#include "factureform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    interfacePrete = true;
    ajusterInterface();



    connect(ui->btnNouvelleLocation, &QPushButton::clicked, this, [this]() {
        locationsForm dialog(this);

        if (dialog.exec() == QDialog::Accepted) {
            chargerLocations();

            const int idLocation = dialog.locationIdEnregistree();

            if (idLocation > 0) {
                factureForm facture(this, idLocation);
                facture.exec();
            } else {
                QMessageBox::warning(
                    this,
                    "Facture",
                    "La location a été enregistrée, mais son numéro "
                    "n'a pas pu être récupéré.");
            }
        }
    });



    //pour les filtres

    ui->status->setEditable(false);
    ui->status->insertItem(0, "Tous");
    ui->status->setCurrentIndex(0);

    ui->dateDebut->setEnabled(false);
    ui->dateFin->setEnabled(false);
    ui->Dulabel->setEnabled(false);
    ui->AuLabel->setEnabled(false);

    timerRecherche = new QTimer(this);
    timerRecherche->setSingleShot(true);
    timerRecherche->setInterval(300);

    connect(timerRecherche, &QTimer::timeout,
            this, [this]() {
                chargerLocations();
            });

    connect(ui->barreSearch, &QLineEdit::textChanged,
            this, [this]() {
                timerRecherche->start();
            });

    connect(ui->status,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int) {
                chargerLocations();
            });


    connect(ui->checkBox, &QCheckBox::toggled,
            this, [this](bool actif) {
                ui->dateDebut->setEnabled(actif);
                ui->dateFin->setEnabled(actif);
                ui->Dulabel->setEnabled(actif);
                ui->AuLabel->setEnabled(actif);
                chargerLocations();
            });


    connect(ui->dateDebut, &QDateEdit::dateChanged,
            this, [this](const QDate &) {
                if (ui->checkBox->isChecked())
                    chargerLocations();
            });

    connect(ui->dateFin, &QDateEdit::dateChanged,
            this, [this](const QDate &) {
                if (ui->checkBox->isChecked())
                    chargerLocations();
            });

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("location_voitures");
    db.setUserName("root");
    db.setPassword("looserwhoiam&0011");

    if (!db.open()) {
        QMessageBox::critical(this, "Erreur MySQL", db.lastError().text());
    } else {
        QSqlQuery query(db);
        auto *model = new QSqlQueryModel(this);
        model->setQuery(
            "SELECT l.id_location, "
            "c.nom, "
            "CONCAT(v.marque, ' ', v.modele), "
            "l.date_debut, "
            "l.date_fin, "
            "l.montant_total, "
            "l.statut_location "
            "FROM locations l "
            "JOIN clients c ON c.id_client = l.id_client "
            "JOIN voitures v ON v.id_voiture = l.id_voiture "
            "ORDER BY l.date_debut DESC",
            db);

        if (model->lastError().isValid()) {
            QMessageBox::critical(this, "Erreur SQL", model->lastError().text());
        } else {
            ui->tableView->setModel(model);

            model->setHeaderData(0, Qt::Horizontal, "N°");
            model->setHeaderData(1, Qt::Horizontal, "Client");
            model->setHeaderData(2, Qt::Horizontal, "Voiture");
            model->setHeaderData(3, Qt::Horizontal, "Date de début");
            model->setHeaderData(4, Qt::Horizontal, "Retour prévu");
            model->setHeaderData(5, Qt::Horizontal, "Montant (Ar)");
            model->setHeaderData(6, Qt::Horizontal, "Statut");


            ui->tableView->verticalHeader()->hide();
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

            ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

            // clic droit sur une location
            connect(ui->tableView, &QTableView::customContextMenuRequested,
                    this, [this](const QPoint &position) {
                        const QModelIndex index = ui->tableView->indexAt(position);
                        if (!index.isValid())
                            return;

                        ui->tableView->selectRow(index.row());

                        const int idLocation =
                            ui->tableView->model()->index(index.row(), 0).data().toInt();

                        QSqlQuery voitureQuery;
                        voitureQuery.prepare(
                            "SELECT id_voiture "
                            "FROM locations "
                            "WHERE id_location = :id");
                        voitureQuery.bindValue(":id", idLocation);

                        if (!voitureQuery.exec() || !voitureQuery.next()) {
                            QMessageBox::critical(
                                this,
                                "Erreur SQL",
                                "Impossible de récupérer la voiture de cette location :\n"
                                    + voitureQuery.lastError().text());
                            return;
                        }

                        const int idVoiture = voitureQuery.value(0).toInt();

                        auto synchroniserStatutVoiture = [this](int id) {
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
                                "WHERE id_voiture = :id");
                            majVoiture.bindValue(":id", id);

                            if (!majVoiture.exec()) {
                                QMessageBox::critical(
                                    this,
                                    "Erreur SQL",
                                    "Impossible de synchroniser le statut de la voiture :\n"
                                        + majVoiture.lastError().text());
                                return false;
                            }

                            return true;
                        };

                        QMenu menu(this);
                        QAction *modifier = menu.addAction("Modifier");
                        QAction *annuler = menu.addAction("Annuler la location");
                        QAction *terminer = menu.addAction("Marquer comme terminée");

                        QAction *choix = menu.exec(
                            ui->tableView->viewport()->mapToGlobal(position));

                        if (choix == modifier) {
                            locationsForm dialog(this, idLocation);
                            if (dialog.exec() == QDialog::Accepted)
                                chargerLocations();

                        } else if (choix == annuler) {
                            const auto reponse = QMessageBox::question(
                                this,
                                "Annuler la location",
                                "Confirmer l’annulation de cette location ?");

                            if (reponse != QMessageBox::Yes)
                                return;

                            QSqlQuery query;
                            query.prepare(
                                "UPDATE locations "
                                "SET statut_location = 'Annulée' "
                                "WHERE id_location = :id "
                                "AND statut_location = 'En cours'");
                            query.bindValue(":id", idLocation);

                            if (!query.exec()) {
                                QMessageBox::critical(
                                    this,
                                    "Erreur SQL",
                                    "Impossible d’annuler cette location :\n"
                                        + query.lastError().text());
                                return;
                            }

                            if (!synchroniserStatutVoiture(idVoiture))
                                return;

                            chargerLocations();

                        } else if (choix == terminer) {
                            QSqlQuery query;
                            query.prepare(
                                "UPDATE locations "
                                "SET statut_location = 'Terminée' "
                                "WHERE id_location = :id "
                                "AND statut_location = 'En cours'");
                            query.bindValue(":id", idLocation);

                            if (!query.exec()) {
                                QMessageBox::critical(
                                    this,
                                    "Erreur SQL",
                                    "Impossible de terminer la location :\n"
                                        + query.lastError().text());
                                return;
                            }

                            if (!synchroniserStatutVoiture(idVoiture))
                                return;

                            chargerLocations();
                        }
                    });
        }
    };
}

void MainWindow::chargerLocations()
{
    if (!m_locationsModel)
        m_locationsModel = new QSqlQueryModel(this);

    const QString texte = ui->barreSearch->text().trimmed();
    const QString statut = ui->status->currentText();
    const bool periodeActive = ui->checkBox->isChecked();

    QString sql =
        "SELECT l.id_location, c.nom, "
        "CONCAT(v.marque, ' ', v.modele), "
        "l.date_debut, l.date_fin, "
        "l.montant_total, l.statut_location "
        "FROM locations l "
        "JOIN clients c ON c.id_client = l.id_client "
        "JOIN voitures v ON v.id_voiture = l.id_voiture "
        "WHERE 1 = 1 ";

    if (!texte.isEmpty()) {
        sql +=
            "AND (c.nom LIKE :rechercheClient "
            "OR CONCAT(v.marque, ' ', v.modele) LIKE :rechercheVoiture) ";
    }

    if (statut != "Tous")
        sql += "AND l.statut_location = :statut ";

    QDate debut = ui->dateDebut->date();
    QDate fin = ui->dateFin->date();

    if (debut > fin)
        std::swap(debut, fin);

    if (periodeActive) {
        sql +=
            "AND l.date_debut <= :dateFin "
            "AND l.date_fin >= :dateDebut ";
    }

    sql += "ORDER BY l.date_debut DESC";

    QSqlQuery query;
    query.prepare(sql);

    if (!texte.isEmpty()) {
        query.bindValue(":rechercheClient", "%" + texte + "%");
        query.bindValue(":rechercheVoiture", "%" + texte + "%");
    }

    if (statut != "Tous")
        query.bindValue(":statut", statut);

    if (periodeActive) {
        query.bindValue(":dateDebut", debut.toString("yyyy-MM-dd"));
        query.bindValue(":dateFin", fin.toString("yyyy-MM-dd"));
    }

    if (!query.exec()) {
        QMessageBox::critical(
            this,
            "Erreur SQL",
            "Impossible de filtrer les locations :\n"
                + query.lastError().text());
        return;
    }

    m_locationsModel->setQuery(std::move(query));

    if (m_locationsModel->lastError().isValid()) {
        QMessageBox::critical(
            this,
            "Erreur SQL",
            m_locationsModel->lastError().text());
        return;
    }

    m_locationsModel->setHeaderData(0, Qt::Horizontal, "N°");
    m_locationsModel->setHeaderData(1, Qt::Horizontal, "Client");
    m_locationsModel->setHeaderData(2, Qt::Horizontal, "Voiture");
    m_locationsModel->setHeaderData(3, Qt::Horizontal, "Date de début");
    m_locationsModel->setHeaderData(4, Qt::Horizontal, "Retour prévu");
    m_locationsModel->setHeaderData(5, Qt::Horizontal, "Montant (Ar)");
    m_locationsModel->setHeaderData(6, Qt::Horizontal, "Statut");

    ui->tableView->setModel(m_locationsModel);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);
}



void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // setupUi doit avoir terminé de créer les widgets.
    if (interfacePrete)
        ajusterInterface();
}

void MainWindow::ajusterInterface()
{
    const int largeur = ui->centralwidget->width();
    const int hauteur = ui->centralwidget->height();

    const int hauteurHeader = 76;
    const int largeurMenu = qBound(220, largeur / 7, 285);

    // Barre supérieure : logo, notifications et profil.
    ui->appHeader->setGeometry(0, 0, largeur, hauteurHeader);
    ui->logoLabel->setGeometry(16, 8, 48, 48);
    ui->btnNotif->setGeometry(largeur - 104, 18, 40, 40);
    ui->btnUser->setGeometry(largeur - 54, 18, 40, 40);
    ui->btnNotif->setIconSize(QSize(22, 22));
    ui->btnUser->setIconSize(QSize(22, 22));

    // Menu latéral et contenu, sous la barre supérieure.
    const int hauteurCorps = hauteur - hauteurHeader;
    const int largeurContenu = largeur - largeurMenu;

    ui->sidebar->setGeometry(
        0, hauteurHeader,
        largeurMenu, hauteurCorps);

    ui->pageContent->setGeometry(
        largeurMenu, hauteurHeader,
        largeurContenu, hauteurCorps);

    // Titre de page et bouton Nouvelle location.
    ui->headerWidget->setGeometry(0, 0, largeurContenu, 70);
    ui->titre->setGeometry(20, 14, largeurContenu - 250, 42);
    ui->btnNouvelleLocation->setGeometry(
        largeurContenu - 220, 14, 195, 42);

    // Sous-titre.
    ui->historique->setGeometry(18, 80, largeurContenu - 36, 32);

    // Recherche et filtres : une ligne si l’espace est suffisant,
    // deux lignes si la fenêtre est plus étroite.
    const bool filtresSurDeuxLignes = largeurContenu < 1100;
    const int hauteurFiltres = filtresSurDeuxLignes ? 100 : 52;
    ui->filtreWidget->setGeometry(
        0, 120, largeurContenu, hauteurFiltres);

    const int marge = 20;
    const int espace = 10;

    if (!filtresSurDeuxLignes) {
        const int largeurRecherche = qBound(260, largeurContenu * 30 / 100, 410);
        int x = marge;

        ui->barreSearch->setGeometry(x, 5, largeurRecherche, 40);
        x += largeurRecherche + espace;

        ui->status->setGeometry(x, 5, 140, 40);
        x += 140 + espace;

        ui->checkBox->setGeometry(x, 10, 90, 30);
        x += 90 + espace;

        ui->Dulabel->setGeometry(x, 15, 25, 25);
        x += 25 + 5;

        ui->dateDebut->setGeometry(x, 5, 125, 40);
        x += 125 + espace;

        ui->AuLabel->setGeometry(x, 15, 30, 25);
        x += 30 + 5;

        ui->dateFin->setGeometry(x, 5, 125, 40);
    } else {
        // Première ligne : recherche.
        ui->barreSearch->setGeometry(
            marge, 4, largeurContenu - 2 * marge, 40);

        // Deuxième ligne : statut et période.
        ui->status->setGeometry(marge, 54, 135, 40);
        ui->checkBox->setGeometry(marge + 145, 59, 90, 30);
        ui->Dulabel->setGeometry(marge + 245, 62, 25, 25);
        ui->dateDebut->setGeometry(marge + 275, 54, 125, 40);
        ui->AuLabel->setGeometry(marge + 410, 62, 30, 25);
        ui->dateFin->setGeometry(marge + 445, 54, 125, 40);
    }

    // Tableau : il occupe le reste de la page.
    const int hautTableau = 120 + hauteurFiltres + 14;
    ui->tableView->setGeometry(
        marge, hautTableau,
        largeurContenu - 2 * marge,
        hauteurCorps - hautTableau - 18);
}



MainWindow::~MainWindow()
{
    delete ui;
}
