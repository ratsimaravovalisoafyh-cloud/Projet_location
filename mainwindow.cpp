#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QScrollArea>
#include <QScrollBar>
#include <QMessageBox>
#include <QEvent>
#include <QList>
#include <algorithm>
#include <utility>
#include "carcard.h"
#include "voiture.h"
#include "toolbar.h"
#include "headerwidget.h"
#include "voituredialog.h"
#include "navbar.h"

MainWindow::MainWindow(Role role, QWidget *parent)   // on reçoit le rôle (admin ou employé)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_role = role;
    ui->setupUi(this);

    // la fenêtre principale
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    central->setObjectName("centrale");

    // à gauche la barre de navigation, à droite le contenu
    QHBoxLayout *racine = new QHBoxLayout(central);
    racine->setContentsMargins(0, 0, 0, 0);
    racine->setSpacing(0);

    NavBar *nav = new NavBar;
    nav->setDashboardVisible(m_role == Role::Admin);   // l'employé ne voit pas le Dashboard
    racine->addWidget(nav);

    QWidget *contenu = new QWidget;
    racine->addWidget(contenu, 1);

    QVBoxLayout *layout = new QVBoxLayout(contenu);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // le header (titre, bouton ajouter...)
    HeaderWidget *header = new HeaderWidget;
    header->setAttribute(Qt::WA_StyledBackground, true);
    header->setObjectName("header");
    header->setPeutAjouter(m_role == Role::Admin);   // seul l'admin peut ajouter
    layout->addWidget(header);

    // le bouton "Ajouter une voiture"
    connect(header, &HeaderWidget::ajouterDemande, this, [this](){
        VoitureDialog dlg(this);
        while (dlg.exec() == QDialog::Accepted) {
            Voiture v = dlg.voiture();
            // on redemande tant que l'immatriculation existe déjà
            if (m_repo.existenceimmatriculation(v.immatriculation)) {
                QMessageBox::warning(this, "Immatriculation déjà utilisée",
                                     "Une voiture porte déjà cette immatriculation.");
                continue;
            }
            m_repo.ajouter(v);
            mettreCartes();
            break;
        }
    });

    // la barre d'outils (recherche + tri)
    toolbar *barre = new toolbar;
    barre->setAttribute(Qt::WA_StyledBackground, true);
    barre->setObjectName("barre");
    layout->addWidget(barre);

    // quand on tape dans la recherche, on filtre
    connect(barre, &toolbar::rechercheChange, this, [this](const QString &texte){
        m_recherche = texte.trimmed();
        filtrer();
    });

    // quand on change le tri, on revient à la première page
    connect(barre, &toolbar::triChange, this, [this](int index){
        m_tri = index;
        m_page = 0;
        m_colonnes = 0;
        placerCartes();
    });

    // le corps : filtres à gauche, voitures à droite
    QHBoxLayout *body = new QHBoxLayout;
    body->setContentsMargins(28, 24, 28, 24);

    // la colonne des filtres
    QWidget *sidebar = new QWidget;
    QVBoxLayout *sidebarlayout = new QVBoxLayout(sidebar);
    sidebar->setFixedWidth(290);
    sidebar->setAttribute(Qt::WA_StyledBackground, true);   // pour que le fond du QSS s'affiche
    sidebar->setObjectName("sidebar");
    sidebarlayout->setContentsMargins(16, 20, 16, 20);
    sidebarlayout->setSpacing(14);

    // le catalogue : la grille qui contient les cartes des voitures
    QWidget *catalogue = new QWidget;
    m_catalogue = catalogue;
    m_cataloglayout = new QGridLayout(catalogue);
    m_cataloglayout->setContentsMargins(0, 0, 0, 0);
    m_cataloglayout->setSpacing(20);
    m_cataloglayout->setAlignment(Qt::AlignTop);

    body->addWidget(sidebar);
    body->setSpacing(24);
    layout->addLayout(body, 1);

    // titre "Filtres" + bouton pour tout réinitialiser
    QHBoxLayout *titrelayout = new QHBoxLayout;
    QLabel *Filtres = new QLabel("Filtres");
    Filtres->setObjectName("titreFiltres");
    QPushButton *Reinitialiser = new QPushButton("Reinitialiser");
    Reinitialiser->setObjectName("boutonReinit");
    Reinitialiser->setCursor(Qt::PointingHandCursor);   // la petite main au survol
    titrelayout->addWidget(Filtres);
    titrelayout->addStretch();
    titrelayout->addWidget(Reinitialiser);
    sidebarlayout->addLayout(titrelayout);

    // filtre par type : toutes / automatique / manuelle
    QLabel *labeltype = new QLabel("Type de voiture");
    sidebarlayout->addWidget(labeltype);

    QPushButton *boutonautomatique = new QPushButton("Automatique");
    QPushButton *boutonmanuelle = new QPushButton("Manuelle");
    QPushButton *boutontoutes = new QPushButton("Toutes");
    boutontoutes->setCheckable(true);
    boutonautomatique->setCheckable(true);
    boutonmanuelle->setCheckable(true);
    boutontoutes->setChecked(true);   // au début on montre tout

    // un seul bouton coché à la fois
    QButtonGroup *typegroupe = new QButtonGroup(this);
    typegroupe->addButton(boutontoutes);
    typegroupe->addButton(boutonautomatique);
    typegroupe->addButton(boutonmanuelle);

    QHBoxLayout *typelayout = new QHBoxLayout;
    typelayout->addWidget(boutontoutes);
    typelayout->addWidget(boutonautomatique);
    typelayout->addWidget(boutonmanuelle);
    typelayout->setSpacing(6);
    typelayout->setStretch(0, 2);   // toutes (plus petit)
    typelayout->setStretch(1, 3);   // automatique
    typelayout->setStretch(2, 3);   // manuelle
    sidebarlayout->addLayout(typelayout);

    boutontoutes->setObjectName("pastille");
    boutonautomatique->setObjectName("pastille");
    boutonmanuelle->setObjectName("pastille");

    connect(boutontoutes, &QPushButton::clicked, this, [this](){
        m_transmission = "";
        filtrer();
    });
    connect(boutonautomatique, &QPushButton::clicked, this, [this](){
        m_transmission = "Automatique";
        filtrer();
    });
    connect(boutonmanuelle, &QPushButton::clicked, this, [this](){
        m_transmission = "Manuelle";
        filtrer();
    });

    // filtre par statut : disponible / loué / en maintenance
    QLabel *labelstatut = new QLabel("Statut");
    sidebarlayout->addWidget(labelstatut);
    QComboBox *combostatut = new QComboBox;
    combostatut->addItem("Tous", -1);
    combostatut->addItem(texteStatut(Statut::Disponible),  static_cast<int>(Statut::Disponible));
    combostatut->addItem(texteStatut(Statut::Loue),        static_cast<int>(Statut::Loue));
    combostatut->addItem(texteStatut(Statut::Maintenance), static_cast<int>(Statut::Maintenance));
    sidebarlayout->addWidget(combostatut);
    connect(combostatut, &QComboBox::currentIndexChanged, this, [this, combostatut](int) {
        m_statut = combostatut->currentData().toInt();
        filtrer();
    });

    // filtre par marque (les cases sont ajoutées plus tard dans rafraichirMarques)
    QLabel *labelmarque = new QLabel("Marque");
    sidebarlayout->addWidget(labelmarque);
    m_totalmarque = new QCheckBox("Total des marques");
    m_totalmarque->setChecked(true);
    m_marquegroupe = new QButtonGroup(this);
    m_marquegroupe->addButton(m_totalmarque);
    m_marqueslayout = new QVBoxLayout;      // ici on mettra une case par marque
    m_marqueslayout->setSpacing(14);        // même écart que le reste de la colonne

    sidebarlayout->addWidget(m_totalmarque);
    sidebarlayout->addLayout(m_marqueslayout);

    connect(m_totalmarque, &QCheckBox::clicked, this, [this](){
        m_marques.clear();
        filtrer();
    });

    // filtre par prix : minimum et maximum
    QLabel *prix = new QLabel("Prix Journalier");
    sidebarlayout->addWidget(prix);
    QSpinBox *prixmin = new QSpinBox;
    QSpinBox *prixmax = new QSpinBox;
    prixmin->setRange(0, 500000);
    prixmin->setValue(0);
    prixmax->setRange(0, 500000);
    prixmax->setValue(500000);
    prixmin->setSingleStep(5000);
    prixmax->setSingleStep(5000);
    prixmin->setAccelerated(true);
    prixmax->setAccelerated(true);
    prixmin->setGroupSeparatorShown(true);
    prixmax->setGroupSeparatorShown(true);
    prixmin->setKeyboardTracking(false);   // on ne filtre pas à chaque chiffre tapé
    prixmax->setKeyboardTracking(false);

    sidebarlayout->addWidget(new QLabel("Minimum"));
    sidebarlayout->addWidget(prixmin);
    sidebarlayout->addWidget(new QLabel("Maximum"));
    sidebarlayout->addWidget(prixmax);

    // on lit les deux prix puis on filtre
    auto majprix = [this, prixmin, prixmax]() {
        prixmin->interpretText();
        prixmax->interpretText();
        m_prixmin = prixmin->value();
        m_prixmax = prixmax->value();
        filtrer();
    };

    // bouton Valider (la touche Entrée dans un des deux champs fait pareil)
    QPushButton *boutonvalider = new QPushButton("Valider");
    boutonvalider->setObjectName("boutonValider");
    sidebarlayout->addWidget(boutonvalider);
    connect(boutonvalider, &QPushButton::clicked, this, majprix);
    connect(prixmin->findChild<QLineEdit *>(), &QLineEdit::returnPressed, boutonvalider, &QPushButton::click);
    connect(prixmax->findChild<QLineEdit *>(), &QLineEdit::returnPressed, boutonvalider, &QPushButton::click);

    // bouton Réinitialiser : on remet tous les filtres comme au début
    connect(Reinitialiser, &QPushButton::clicked, this, [this, boutontoutes, prixmin, prixmax, combostatut]() {
        boutontoutes->setChecked(true);
        m_totalmarque->setChecked(true);
        prixmin->setValue(0);
        prixmax->setValue(500000);
        combostatut->setCurrentIndex(0);
        m_transmission = "";
        m_statut = -1;
        m_marques.clear();
        m_prixmin = 0;
        m_prixmax = 500000;
        filtrer();
    });
    sidebarlayout->addStretch();   // pousse tout vers le haut

    // la zone qui défile avec les cartes
    m_scroll = new QScrollArea;
    m_scroll->viewport()->installEventFilter(this);   // pour savoir quand la taille change
    m_scroll->setWidget(catalogue);
    m_scroll->setWidgetResizable(true);
    m_scroll->setFrameShape(QFrame::NoFrame);
    m_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // la pagination (les petits boutons 1, 2, 3 en bas)
    m_pagination = new QWidget;
    m_pagination->setObjectName("pagination");
    m_pagination->setAttribute(Qt::WA_StyledBackground, true);
    m_paginationLayout = new QHBoxLayout(m_pagination);
    m_paginationLayout->setContentsMargins(0, 0, 0, 0);
    m_paginationLayout->setSpacing(8);

    QVBoxLayout *droite = new QVBoxLayout;
    droite->setSpacing(12);
    droite->addWidget(m_scroll, 1);
    droite->addWidget(m_pagination);
    body->addLayout(droite, 1);

    mettreCartes();   // on affiche les voitures au démarrage
}

// on regarde chaque voiture et on cache celles qui ne passent pas les filtres
void MainWindow::filtrer()
{
    for (int i = 0; i < m_voitures.size(); ++i) {
        const Voiture &v = m_voitures[i];
        bool garder = true;

        if (!m_transmission.isEmpty() && v.transmission != m_transmission)
            garder = false;
        if (m_statut >= 0 && static_cast<int>(v.statut) != m_statut)
            garder = false;
        if (!m_marques.isEmpty() && !m_marques.contains(v.marque, Qt::CaseInsensitive))
            garder = false;
        if (v.prix < m_prixmin || v.prix > m_prixmax)
            garder = false;

        // la recherche regarde le nom, la marque, le type et l'immatriculation
        if (!m_recherche.isEmpty()) {
            bool trouve = v.nom.contains(m_recherche, Qt::CaseInsensitive)
            || v.marque.contains(m_recherche, Qt::CaseInsensitive)
                || v.type.contains(m_recherche, Qt::CaseInsensitive)
                || v.immatriculation.contains(m_recherche, Qt::CaseInsensitive);
            if (!trouve)
                garder = false;
        }
        m_cartes[i]->setProperty("masquee", !garder);
    }
    m_colonnes = 0;   // on force le placement à se refaire
    placerCartes();
}

// on range les cartes dans la grille (tri, page, nombre de colonnes)
void MainWindow::placerCartes()
{
    // combien de colonnes rentrent dans la largeur (une carte = 260 px + 20 d'écart)
    int largeur = m_scroll->viewport()->width();
    int colonnes = qMax(1, (largeur + 20) / (260 + 20));

    // rien n'a changé, on ne refait pas tout
    if (colonnes == m_colonnes)
        return;
    m_colonnes = colonnes;

    for (int c = 0; c < 10; ++c)
        m_cataloglayout->setColumnStretch(c, c < colonnes ? 1 : 0);
    for (CarCard *carte : m_cartes)
        m_cataloglayout->removeWidget(carte);

    // l'ordre d'affichage selon le tri choisi (1 = prix croissant, 2 = prix décroissant)
    QList<int> ordre;
    for (int i = 0; i < m_cartes.size(); ++i)
        ordre.append(i);
    if (m_tri == 1)
        std::stable_sort(ordre.begin(), ordre.end(), [this](int a, int b){
            return m_voitures[a].prix < m_voitures[b].prix;
        });
    else if (m_tri == 2)
        std::stable_sort(ordre.begin(), ordre.end(), [this](int a, int b){
            return m_voitures[a].prix > m_voitures[b].prix;
        });

    // on garde seulement les cartes qui passent les filtres, dans l'ordre du tri
    QList<CarCard *> visibles;
    for (int idx : ordre) {
        CarCard *carte = m_cartes[idx];
        if (carte->property("masquee").toBool())
            carte->hide();
        else
            visibles.append(carte);
    }

    // nombre de pages, et on s'assure que la page actuelle existe
    int pages = qMax(1, (int(visibles.size()) + m_parPage - 1) / m_parPage);
    m_page = qBound(0, m_page, pages - 1);
    int debut = m_page * m_parPage;

    // on place seulement les cartes de la page actuelle
    for (int i = 0; i < visibles.size(); ++i) {
        CarCard *carte = visibles[i];
        if (i < debut || i >= debut + m_parPage) {
            carte->hide();   // elle est sur une autre page
            continue;
        }
        int n = i - debut;
        m_cataloglayout->addWidget(carte, n / colonnes, n % colonnes);
        carte->show();
    }
    majPagination(pages);
}

// on supprime toutes les cartes et on les recrée à partir du dépôt
void MainWindow::mettreCartes()
{
    m_scroll->setUpdatesEnabled(false);   // on gèle l'affichage pour éviter le clignotement

    // on enlève les anciennes cartes
    for (CarCard *carte : std::as_const(m_cartes)) {
        m_cataloglayout->removeWidget(carte);
        carte->hide();
        carte->deleteLater();
    }
    m_cartes.clear();

    m_voitures = m_repo.toutes();

    // on crée une carte par voiture
    for (const Voiture &v : std::as_const(m_voitures)) {
        // le prix s'affiche comme "180 000 Ar"
        const QString prixTexte = QLocale(QLocale::English).toString(qlonglong(v.prix)).replace(',', ' ') + " Ar";
        CarCard *carte = new CarCard(v.statut, v.nom, v.type, prixTexte, v.immatriculation,
                                     v.id, v.photo, m_catalogue, m_role == Role::Admin);
        m_cartes.append(carte);

        // clic sur Supprimer : on demande confirmation
        connect(carte, &CarCard::supprimerDemande, this, [this](int id){
            if (m_role != Role::Admin) return;
            auto reponse = QMessageBox::question(this, "Supprimer la voiture",
                                                 "Voulez-vous vraiment supprimer la voiture ?");
            if (reponse == QMessageBox::Yes) {
                m_repo.supprimer(id);
                mettreCartes();
            }
        });

        // clic sur le badge de statut : on change le statut
        connect(carte, &CarCard::statutDemande, this, [this](int id, Statut nouveau) {
            if (m_role != Role::Admin) return;
            m_repo.changerStatut(id, nouveau);
            mettreCartes();
        });

        // clic sur Modifier : on ouvre le dialogue déjà rempli
        connect(carte, &CarCard::modifierDemande, this, [this](int id) {
            // on retrouve la voiture avec son id
            Voiture courante;
            bool trouve = false;
            for (const Voiture &candidate : std::as_const(m_voitures)) {
                if (candidate.id == id) {
                    courante = candidate;
                    trouve = true;
                    break;
                }
            }
            if (!trouve)
                return;

            VoitureDialog dlg(this);
            dlg.remplir(courante);
            while (dlg.exec() == QDialog::Accepted) {
                Voiture modifiee = dlg.voiture();
                // l'immatriculation ne doit pas être celle d'une autre voiture
                if (m_repo.existenceimmatriculation(modifiee.immatriculation, modifiee.id)) {
                    QMessageBox::warning(this, "Immatriculation déjà utilisée",
                                         "Une autre voiture porte déjà cette immatriculation.");
                    continue;
                }
                m_repo.modifier(modifiee);
                mettreCartes();
                break;
            }
        });
    }

    int pageAvant = m_page;   // on retient la page où on était
    rafraichirMarques();
    filtrer();
    if (pageAvant > 0) {
        // on revient sur la même page (placerCartes la ramène à la dernière si elle n'existe plus)
        m_page = pageAvant;
        m_colonnes = 0;
        placerCartes();
    }
    m_scroll->setUpdatesEnabled(true);   // on réaffiche tout d'un coup
}

// quand la zone de défilement change de taille, on replace les cartes
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_scroll->viewport() && event->type() == QEvent::Resize)
        placerCartes();
    return QMainWindow::eventFilter(obj, event);
}

// on refait la liste des marques à partir des voitures qui existent
void MainWindow::rafraichirMarques()
{
    // on retient la marque cochée pour la recocher après
    QString selection = m_marques.isEmpty() ? QString() : m_marques.first();

    // on supprime les anciennes cases (sauf "Total des marques")
    for (QAbstractButton *b : m_marquegroupe->buttons()) {
        if (b == m_totalmarque)
            continue;
        m_marquegroupe->removeButton(b);
        m_marqueslayout->removeWidget(b);
        b->deleteLater();
    }

    // la liste des marques, sans doublon, triée sans tenir compte des majuscules
    QStringList marques;
    for (const Voiture &v : m_voitures) {
        if (!marques.contains(v.marque, Qt::CaseInsensitive))
            marques << v.marque;
    }
    marques.sort(Qt::CaseInsensitive);

    // une case par marque
    bool retrouvee = false;
    for (const QString &m : marques) {
        QCheckBox *c = new QCheckBox(m);
        m_marquegroupe->addButton(c);
        m_marqueslayout->addWidget(c);
        if (m == selection) {
            c->setChecked(true);
            retrouvee = true;
        }
        connect(c, &QCheckBox::clicked, this, [this, m](){
            m_marques.clear();
            m_marques << m;
            filtrer();
        });
    }

    // si la marque cochée n'existe plus, on revient sur "Total des marques"
    if (!retrouvee) {
        m_totalmarque->setChecked(true);
        m_marques.clear();
    }
}

// on change de page et on remonte en haut de la liste
void MainWindow::allerPage(int page)
{
    m_page = page;
    m_colonnes = 0;
    placerCartes();
    m_scroll->verticalScrollBar()->setValue(0);
}

// on refait les boutons de la pagination : < 1 2 3 >
void MainWindow::majPagination(int pages)
{
    if (!m_paginationLayout)
        return;

    // on vide la barre
    while (QLayoutItem *item = m_paginationLayout->takeAt(0)) {
        if (item->widget())
            item->widget()->deleteLater();
        delete item;
    }
    m_pagination->setVisible(pages > 1);   // pas besoin de pagination s'il n'y a qu'une page
    if (pages <= 1)
        return;

    // petite fonction qui crée un bouton de la barre
    auto bouton = [this](const QString &texte, int page, bool actif, bool fleche) {
        QPushButton *b = new QPushButton(texte);
        b->setObjectName(fleche ? "pageFleche" : "pageBouton");
        b->setFixedSize(32, 32);
        b->setCursor(Qt::PointingHandCursor);
        if (!fleche) {
            b->setCheckable(true);
            b->setChecked(actif);
        }
        connect(b, &QPushButton::clicked, this, [this, page]() { allerPage(page); });
        m_paginationLayout->addWidget(b);
        return b;
    };

    m_paginationLayout->addStretch();

    // flèche "page précédente" (grisée si on est sur la première)
    QPushButton *prec = bouton("‹", qMax(0, m_page - 1), false, true);
    prec->setEnabled(m_page > 0);

    // on montre la première page, la dernière, la page actuelle et ses voisines
    QList<int> liste;
    for (int p = 0; p < pages; ++p)
        if (p == 0 || p == pages - 1 || qAbs(p - m_page) <= 1)
            liste << p;

    int precedent = -1;
    for (int p : liste) {
        // s'il manque des pages entre deux boutons, on met "…"
        if (precedent != -1 && p - precedent > 1) {
            QLabel *points = new QLabel("…");
            m_paginationLayout->addWidget(points);
        }
        bouton(QString::number(p + 1), p, p == m_page, false);
        precedent = p;
    }

    // flèche "page suivante" (grisée si on est sur la dernière)
    QPushButton *suiv = bouton("›", qMin(pages - 1, m_page + 1), false, true);
    suiv->setEnabled(m_page < pages - 1);

    m_paginationLayout->addStretch();
}

MainWindow::~MainWindow()
{
    delete ui;
}